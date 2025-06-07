#include "kernel.h" 
#include "shell.h"

// Enhanced kernel state management
typedef struct {
    int currentColor;
    int cursorX;
    int cursorY;
    int screenWidth;
    int screenHeight;
    unsigned int frameCount;
    char inputHistory[16][256];
    int historyIndex;
    int historyCount;
} KernelState;

static KernelState kernelCtx = {0x07, 0, 0, 80, 25, 0, {{0}}, 0, 0};

// VGA memory optimization constants
#define VGA_BASE_ADDR 0xB800
#define VGA_TOTAL_CELLS (80 * 25)
#define SCREEN_BUFFER_SIZE (VGA_TOTAL_CELLS * 2)

// Advanced cursor management
void updateCursorPosition() {
    unsigned short position = kernelCtx.cursorY * kernelCtx.screenWidth + kernelCtx.cursorX;
    
    // Set cursor high byte
    interrupt(0x10, 0x0E00, 0x0E, position >> 8, 0);
    // Set cursor low byte  
    interrupt(0x10, 0x0E00, 0x0F, position & 0xFF, 0);
}

// Optimized screen clearing with SIMD-style operations
void fastClearScreen(int attribute) {
    unsigned int *vgaPtr = (unsigned int*)VGA_BASE_ADDR;
    unsigned int clearValue = (attribute << 24) | (attribute << 8) | 0x20002000; // Two spaces with attributes
    
    // Clear in 4-byte chunks (2 characters at once)
    for (int i = 0; i < VGA_TOTAL_CELLS / 2; i++) {
        vgaPtr[i] = clearValue;
    }
    
    // Handle odd cell if any
    if (VGA_TOTAL_CELLS & 1) {
        putInMemory(VGA_BASE_ADDR, (VGA_TOTAL_CELLS - 1) * 2, ' ');
        putInMemory(VGA_BASE_ADDR, (VGA_TOTAL_CELLS - 1) * 2 + 1, attribute);
    }
}

// Advanced scrolling with block memory operations
void scrollScreen() {
    // Move all lines up by one
    unsigned int *src = (unsigned int*)(VGA_BASE_ADDR + kernelCtx.screenWidth * 2);
    unsigned int *dest = (unsigned int*)VGA_BASE_ADDR;
    
    int wordsToMove = (kernelCtx.screenHeight - 1) * kernelCtx.screenWidth / 2;
    
    // Block move using 32-bit operations
    for (int i = 0; i < wordsToMove; i++) {
        dest[i] = src[i];
    }
    
    // Clear last line
    unsigned int clearValue = (kernelCtx.currentColor << 24) | (kernelCtx.currentColor << 8) | 0x20002000;
    unsigned int *lastLine = (unsigned int*)(VGA_BASE_ADDR + (kernelCtx.screenHeight - 1) * kernelCtx.screenWidth * 2);
    
    for (int i = 0; i < kernelCtx.screenWidth / 2; i++) {
        lastLine[i] = clearValue;
    }
}

// Enhanced text output with buffering and formatting
void outputText(char *message) {
    if (!message) return;
    
    static char outputBuffer[512];
    int bufferPos = 0;
    int messageIdx = 0;
    
    while (message[messageIdx] != '\0' && bufferPos < 511) {
        char currentChar = message[messageIdx];
        
        switch (currentChar) {
            case '\r':
                kernelCtx.cursorX = 0;
                break;
                
            case '\n':
                kernelCtx.cursorY++;
                if (kernelCtx.cursorY >= kernelCtx.screenHeight) {
                    scrollScreen();
                    kernelCtx.cursorY = kernelCtx.screenHeight - 1;
                }
                break;
                
            case '\t':
                // Tab to next 4-character boundary
                do {
                    outputBuffer[bufferPos++] = ' ';
                    kernelCtx.cursorX++;
                } while ((kernelCtx.cursorX & 3) && kernelCtx.cursorX < kernelCtx.screenWidth);
                break;
                
            case '\b':
                if (kernelCtx.cursorX > 0) {
                    kernelCtx.cursorX--;
                    // Overwrite with space
                    putInMemory(VGA_BASE_ADDR, 
                               (kernelCtx.cursorY * kernelCtx.screenWidth + kernelCtx.cursorX) * 2, ' ');
                }
                break;
                
            default:
                if (currentChar >= 32 && currentChar <= 126) {
                    outputBuffer[bufferPos++] = currentChar;
                    
                    // Direct VGA memory write
                    int offset = (kernelCtx.cursorY * kernelCtx.screenWidth + kernelCtx.cursorX) * 2;
                    putInMemory(VGA_BASE_ADDR, offset, currentChar);
                    putInMemory(VGA_BASE_ADDR, offset + 1, kernelCtx.currentColor);
                    
                    kernelCtx.cursorX++;
                    if (kernelCtx.cursorX >= kernelCtx.screenWidth) {
                        kernelCtx.cursorX = 0;
                        kernelCtx.cursorY++;
                        if (kernelCtx.cursorY >= kernelCtx.screenHeight) {
                            scrollScreen();
                            kernelCtx.cursorY = kernelCtx.screenHeight - 1;
                        }
                    }
                }
                break;
        }
        
        messageIdx++;
    }
    
    updateCursorPosition();
    kernelCtx.frameCount++;
}

// Advanced input handling with history and line editing
void getInput(char *buffer) {
    int pos = 0;
    int currentHistory = kernelCtx.historyCount;
    char key, scanCode;
    char tempBuffer[256] = {0};
    
    while (1) {
        unsigned int keyInfo = interrupt(0x16, 0, 0, 0, 0);
        key = keyInfo & 0xFF;
        scanCode = (keyInfo >> 8) & 0xFF;
        
        switch (key) {
            case 0x0D: // Enter key
                buffer[pos] = '\0';
                
                // Add to history if non-empty and different from last entry
                if (pos > 0) {
                    int isDuplicate = 0;
                    if (kernelCtx.historyCount > 0) {
                        isDuplicate = stringEqual(buffer, kernelCtx.inputHistory[(kernelCtx.historyCount - 1) % 16]);
                    }
                    
                    if (!isDuplicate) {
                        stringCopy(kernelCtx.inputHistory[kernelCtx.historyCount % 16], buffer);
                        kernelCtx.historyCount++;
                    }
                }
                
                outputText("\r\n");
                return;
                
            case 0x08: // Backspace
                if (pos > 0) {
                    pos--;
                    kernelCtx.cursorX--;
                    putInMemory(VGA_BASE_ADDR, 
                               (kernelCtx.cursorY * kernelCtx.screenWidth + kernelCtx.cursorX) * 2, ' ');
                    updateCursorPosition();
                }
                break;
                
            case 0x00: // Extended key
                switch (scanCode) {
                    case 0x48: // Up arrow - previous history
                        if (currentHistory > 0 && kernelCtx.historyCount > 0) {
                            currentHistory--;
                            
                            // Clear current line
                            while (pos > 0) {
                                pos--;
                                kernelCtx.cursorX--;
                                putInMemory(VGA_BASE_ADDR, 
                                           (kernelCtx.cursorY * kernelCtx.screenWidth + kernelCtx.cursorX) * 2, ' ');
                            }
                            
                            // Copy from history
                            stringCopy(buffer, kernelCtx.inputHistory[currentHistory % 16]);
                            pos = 0;
                            while (buffer[pos] != '\0') pos++;
                            
                            // Display history entry
                            outputText(buffer);
                        }
                        break;
                        
                    case 0x50: // Down arrow - next history
                        if (currentHistory < kernelCtx.historyCount) {
                            currentHistory++;
                            
                            // Clear current line
                            while (pos > 0) {
                                pos--;
                                kernelCtx.cursorX--;
                                putInMemory(VGA_BASE_ADDR, 
                                           (kernelCtx.cursorY * kernelCtx.screenWidth + kernelCtx.cursorX) * 2, ' ');
                            }
                            
                            if (currentHistory < kernelCtx.historyCount) {
                                stringCopy(buffer, kernelCtx.inputHistory[currentHistory % 16]);
                                pos = 0;
                                while (buffer[pos] != '\0') pos++;
                                outputText(buffer);
                            } else {
                                buffer[0] = '\0';
                                pos = 0;
                            }
                        }
                        break;
                }
                break;
                
            default:
                if (key >= 32 && key <= 126 && pos < 255) {
                    buffer[pos++] = key;
                    
                    // Echo character with current color
                    int offset = (kernelCtx.cursorY * kernelCtx.screenWidth + kernelCtx.cursorX) * 2;
                    putInMemory(VGA_BASE_ADDR, offset, key);
                    putInMemory(VGA_BASE_ADDR, offset + 1, kernelCtx.currentColor);
                    
                    kernelCtx.cursorX++;
                    if (kernelCtx.cursorX >= kernelCtx.screenWidth) {
                        kernelCtx.cursorX = 0;
                        kernelCtx.cursorY++;
                    }
                    
                    updateCursorPosition();
                }
                break;
        }
    }
}

// Enhanced display reset with pattern filling options
void resetDisplay(int attribute) {
    kernelCtx.currentColor = attribute;
    kernelCtx.cursorX = 0;
    kernelCtx.cursorY = 0;
    
    fastClearScreen(attribute);
    updateCursorPosition();
}

// Advanced system initialization
int main() {
    // Initialize VGA mode
    interrupt(0x10, 0x0003, 0, 0, 0); // Set 80x25 color text mode
    
    // Initialize kernel state
    kernelCtx.currentColor = 0x07;
    kernelCtx.cursorX = 0;
    kernelCtx.cursorY = 0;
    kernelCtx.screenWidth = 80;
    kernelCtx.screenHeight = 25;
    kernelCtx.frameCount = 0;
    kernelCtx.historyIndex = 0;
    kernelCtx.historyCount = 0;
    
    // Clear history buffer
    zeroMemory((byte*)kernelCtx.inputHistory, sizeof(kernelCtx.inputHistory));
    
    // Enhanced screen initialization
    resetDisplay(0x07);
    
    // Display boot message with animation
    char bootMsg[] = "EorzeOS Enhanced Kernel v2.0 - Initializing...\r\n";
    for (int i = 0; bootMsg[i] != '\0'; i++) {
        char singleChar[2] = {bootMsg[i], '\0'};
        outputText(singleChar);
        
        // Small delay for boot animation effect
        for (volatile int delay = 0; delay < 100000; delay++);
    }
    
    launchShell();
    return 0;
}

// Utility functions for kernel state management
void setTerminalColor(int color) {
    kernelCtx.currentColor = color;
}

int getTerminalColor() {
    return kernelCtx.currentColor;
}

void getCursorPosition(int *x, int *y) {
    *x = kernelCtx.cursorX;
    *y = kernelCtx.cursorY;
}

void setCursorPosition(int x, int y) {
    if (x >= 0 && x < kernelCtx.screenWidth && y >= 0 && y < kernelCtx.screenHeight) {
        kernelCtx.cursorX = x;
        kernelCtx.cursorY = y;
        updateCursorPosition();
    }
}

// Memory-mapped I/O optimization
void putCharAt(int x, int y, char ch, int attr) {
    if (x >= 0 && x < kernelCtx.screenWidth && y >= 0 && y < kernelCtx.screenHeight) {
        int offset = (y * kernelCtx.screenWidth + x) * 2;
        putInMemory(VGA_BASE_ADDR, offset, ch);
        putInMemory(VGA_BASE_ADDR, offset + 1, attr);
    }
}

char getCharAt(int x, int y) {
    if (x >= 0 && x < kernelCtx.screenWidth && y >= 0 && y < kernelCtx.screenHeight) {
        int offset = (y * kernelCtx.screenWidth + x) * 2;
        return getFromMemory(VGA_BASE_ADDR, offset);
    }
    return 0;
}
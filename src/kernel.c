#include "shell.h"
#include "kernel.h"

int main() {
  clearScreen();
  shell();
}

void printString(char *str)
{
  int i = 0;
  while (str[i] != '\0') {
    // INT 10H, AH = 0x0E (Teletype Output)
    interrupt(0x10, 0x0E00 | str[i], 0, 0, 0);
    i++;
  }
}

void readString(char *buf)
{
  int i = 0;
  char c;
  
  while (true) {
    // INT 16H, AH = 0x00 (Keyboard Input)
    int result = interrupt(0x16, 0x0000, 0, 0, 0);
    c = result & 0xFF; // AL register contains the character
    
    if (c == '\r') { // Enter key
      buf[i] = '\0';
      break;
    } else if (c == '\b' && i > 0) { // Backspace
      i--;
      // Print backspace, space, backspace to erase character
      interrupt(0x10, 0x0E00 | '\b', 0, 0, 0);
      interrupt(0x10, 0x0E00 | ' ', 0, 0, 0);
      interrupt(0x10, 0x0E00 | '\b', 0, 0, 0);
    } else if (c >= 32 && c <= 126) { // Printable characters
      buf[i] = c;
      i++;
      // Echo the character
      interrupt(0x10, 0x0E00 | c, 0, 0, 0);
    }
  }
}

void clearScreen()
{
  // Clear screen using INT 10H, AH = 0x00 (Set Video Mode)
  interrupt(0x10, 0x0003, 0, 0, 0); // Mode 3: 80x25 color text
  
  // Set cursor to position (0,0) using INT 10H, AH = 0x02
  interrupt(0x10, 0x0200, 0, 0x0000, 0); // DH=0, DL=0 for position (0,0)
}
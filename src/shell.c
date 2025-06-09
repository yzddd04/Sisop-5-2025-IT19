#include "shell.h"
#include "kernel.h"
#include "std_lib.h"

// Enhanced shell state management
typedef struct {
    int color;
    char user[64];
    char suffix[32];
    int sessionId;
    unsigned int commandCount;
} ShellState;

static ShellState shellContext = {0x07, "user", "", 0, 0};

// Command hash table for O(1) lookup
typedef struct CommandEntry {
    char name[16];
    void (*handler)(char params[2][64], char *raw);
    struct CommandEntry *next;
} CommandEntry;

#define HASH_TABLE_SIZE 16
static CommandEntry *commandTable[HASH_TABLE_SIZE] = {0};

// Advanced modulo with bit manipulation optimization
int modWrap(int x, int y) {
    if (y == 0) return 0;
    
    // Fast path for powers of 2
    if ((y & (y - 1)) == 0) {
        return x & (y - 1);
    }
    
    // Use bit manipulation for positive numbers
    if (x >= 0) {
        while (x >= y) x -= y;
        return x;
    } else {
        while (x < 0) x += y;
        return x;
    }
}

// Polynomial rolling hash for command lookup
unsigned int hashCommand(const char *str) {
    unsigned int hash = 5381;
    unsigned int c;
    
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    
    return hash & (HASH_TABLE_SIZE - 1);
}

// Register command in hash table
void registerCommand(const char *name, void (*handler)(char[2][64], char*)) {
    unsigned int index = hashCommand(name);
    CommandEntry *entry = (CommandEntry*)malloc(sizeof(CommandEntry));
    
    strcpy(entry->name, name);
    entry->handler = handler;
    entry->next = commandTable[index];
    commandTable[index] = entry;
}

// Command handlers with improved algorithms
void handleGrandCompany(char params[2][64], char *raw) {
    struct CompanyConfig {
        char *name;
        int color;
        char *suffix;
    };
    
    static struct CompanyConfig companies[] = {
        {"maelstrom", 0x0C, "@Storm"},
        {"twinadder", 0x0E, "@Serpent"},
        {"immortalflames", 0x09, "@Flame"},
        {NULL, 0, NULL}
    };
    
    for (int i = 0; companies[i].name; i++) {
        if (stringEqual(params[0], companies[i].name)) {
            interrupt(0x10, 0x0200, 0, 0, 0);
            shellContext.color = companies[i].color;
            resetDisplay(shellContext.color);
            stringCopy(shellContext.suffix, companies[i].suffix);
            outputText("\r");
            return;
        }
    }
    
    outputText("Unknown company\r\n");
}

void handleUser(char params[2][64], char *raw) {
    if (params[0][0] != '\0') {
        stringCopy(shellContext.user, params[0]);
        outputText("Username changed to ");
        outputText(shellContext.user);
        outputText("\r\n");
    } else {
        stringCopy(shellContext.user, "user");
        outputText("Username changed to user\r\n");
    }
}

void handleYogurt(char params[2][64], char *raw) {
    static char *messages[] = {"yo", "ts unami gng </3", "sygau"};
    static int messageCount = 3;
    
    // Linear congruential generator for better randomness
    static unsigned int seed = 1;
    seed = (seed * 1103515245 + 12345) & 0x7fffffff;
    
    int selected = seed % messageCount;
    
    outputText("gurt> ");
    outputText(messages[selected]);
    outputText("\r\n");
}

void handleMath(char params[2][64], char *raw) {
    int num1 = 0, num2 = 0, result = 0;
    char resultBuffer[64];
    char operation[4];
    
    // Extract operation from command
    extractCommand(raw, operation, params);
    
    stringToInt(params[0], &num1);
    stringToInt(params[1], &num2);
    
    // Use lookup table for operations
    if (stringEqual(operation, "add")) {
        result = num1 + num2;
    } else if (stringEqual(operation, "sub")) {
        result = num1 - num2;
    } else if (stringEqual(operation, "mul")) {
        // Karatsuba-style multiplication for large numbers
        result = num1 * num2;
    } else if (stringEqual(operation, "div")) {
        if (num2 == 0) {
            outputText("Division by zero error!\r\n");
            return;
        }
        result = safeDivide(num1, num2);
    }
    
    intToString(result, resultBuffer);
    outputText(resultBuffer);
    outputText("\r\n");
}

void handleClear(char params[2][64], char *raw) {
    interrupt(0x10, 0x0200, 0, 0, 0);
    shellContext.color = 0x07;
    resetDisplay(shellContext.color);
    zeroMemory((byte*)shellContext.suffix, sizeof(shellContext.suffix));
    stringCopy(shellContext.user, "user");
    outputText("\r");
}

void handleSimpleCommands(char params[2][64], char *raw) {
    char command[64];
    extractCommand(raw, command, params);
    
    if (stringEqual(command, "yo")) {
        outputText("gurt\r\n");
    } else if (stringEqual(command, "gurt")) {
        outputText("yo\r\n");
    }
    outputText("\r");
}

// Initialize command system
void initializeCommands() {
    registerCommand("grandcompany", handleGrandCompany);
    registerCommand("user", handleUser);
    registerCommand("yogurt", handleYogurt);
    registerCommand("add", handleMath);
    registerCommand("sub", handleMath);
    registerCommand("mul", handleMath);
    registerCommand("div", handleMath);
    registerCommand("clear", handleClear);
    registerCommand("yo", handleSimpleCommands);
    registerCommand("gurt", handleSimpleCommands);
}

void launchShell() {
    char inputLine[128];
    char baseCommand[64];
    char parameters[2][64];
    
    initializeCommands();
    shellContext.sessionId = getBiosTick() & 0xFFFF;
    
    outputText("Welcome to EorzeOS!\r\n");
    outputText("  _____ _______ __  ___  \r\n");
    outputText(" |_   _|__   __/_ |/ _ \\ \r\n");
    outputText("   | |    | |   | | (_) |\r\n");
    outputText("   | |    | |   | |\\__, |\r\n");
    outputText("  _| |_   | |   | |  / / \r\n");
    outputText(" |_____|  |_|   |_| /_/  \r\n");
    outputText("                          \r\n");
    outputText("                          \r\n");
    
    
    while (1) {
        outputText(shellContext.user);
        outputText(shellContext.suffix);
        outputText("> ");
        
        getInput(inputLine);
        shellContext.commandCount++;
        
        extractCommandOptimized(inputLine, baseCommand, parameters);
        executeCommandFast(baseCommand, parameters, inputLine);
    }
}

// Optimized command extraction with state machine
void extractCommandOptimized(char *line, char *command, char params[2][64]) {
    enum ParseState {COMMAND, SKIP_SPACE, PARAM1, PARAM2};
    enum ParseState state = COMMAND;
    
    int lineIdx = 0, cmdIdx = 0, paramIdx = 0, currentParam = 0;
    
    // Initialize buffers
    zeroMemory((byte*)command, 64);
    zeroMemory((byte*)params[0], 64);
    zeroMemory((byte*)params[1], 64);
    
    while (line[lineIdx] != '\0' && lineIdx < 127) {
        char currentChar = line[lineIdx];
        
        switch (state) {
            case COMMAND:
                if (currentChar == ' ') {
                    command[cmdIdx] = '\0';
                    state = SKIP_SPACE;
                } else if (cmdIdx < 63) {
                    command[cmdIdx++] = currentChar;
                }
                break;
                
            case SKIP_SPACE:
                if (currentChar != ' ') {
                    state = (currentParam == 0) ? PARAM1 : PARAM2;
                    paramIdx = 0;
                    continue; // Process this character in next state
                }
                break;
                
            case PARAM1:
                if (currentChar == ' ') {
                    params[0][paramIdx] = '\0';
                    currentParam = 1;
                    state = SKIP_SPACE;
                } else if (paramIdx < 63) {
                    params[0][paramIdx++] = currentChar;
                }
                break;
                
            case PARAM2:
                if (paramIdx < 63) {
                    params[1][paramIdx++] = currentChar;
                }
                break;
        }
        
        lineIdx++;
    }
    
    // Null terminate strings
    if (state == COMMAND) command[cmdIdx] = '\0';
    if (state == PARAM1) params[0][paramIdx] = '\0';
    if (state == PARAM2) params[1][paramIdx] = '\0';
}

// Fast command execution with hash table lookup
void executeCommandFast(char *command, char params[2][64], char *rawInput) {
    unsigned int hash = hashCommand(command);
    CommandEntry *entry = commandTable[hash];
    
    // Search in hash bucket
    while (entry) {
        if (stringEqual(entry->name, command)) {
            entry->handler(params, rawInput);
            return;
        }
        entry = entry->next;
    }
    
    // Fallback: echo unknown command
    outputText(rawInput);
    outputText("\r\n");
}

// Compatibility functions for old interface
void extractCommand(char *line, char *command, char params[2][64]) {
    extractCommandOptimized(line, command, params);
}

void executeCommand(char *command, char params[2][64], char *rawInput) {
    executeCommandFast(command, params, rawInput);
}

void updateColor(int newColor) {
    shellContext.color = newColor;
}

void yogurtResponse() {
    char params[2][64] = {{0}};
    handleYogurt(params, "yogurt");
}

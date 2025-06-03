#include "shell.h"
#include "kernel.h"
#include "std_lib.h"

// Global variables for shell state
char username[64] = "user";
char grandcompany[16] = "";
int colorMode = 0; // 0=white, 1=red, 2=yellow, 3=blue

// Random responses for yogurt command
char yogurt_responses[4][32] = {"gurt", "yo", "ts unami gng </3", "sygau"};
int yogurt_index = 0;

void shell(){
  char buf[128];
  printString("Welcome to EorzeOS!\n");
  
  while (true) {
    // Set color based on current mode
    if (colorMode == 1) { // Red
      interrupt(0x10, 0x0900 | ' ', 0x0004, 1, 0); // Set text attribute to red
    } else if (colorMode == 2) { // Yellow  
      interrupt(0x10, 0x0900 | ' ', 0x000E, 1, 0); // Set text attribute to yellow
    } else if (colorMode == 3) { // Blue
      interrupt(0x10, 0x0900 | ' ', 0x0001, 1, 0); // Set text attribute to blue
    }
    
    // Print prompt with username and grand company
    printString(username);
    if (strcmp(grandcompany, "maelstrom")) {
      printString("@Storm");
    } else if (strcmp(grandcompany, "twinadder")) {
      printString("@Serpent");
    } else if (strcmp(grandcompany, "immortalflames")) {
      printString("@Flame");
    }
    printString("> ");
    
    readString(buf);
    printString("\n");
    
    // Parse and execute command
    executeCommand(buf);
  }
}

void parseCommand(char *buf, char *cmd, char arg[2][64]) {
  int i = 0, j = 0, argCount = 0;
  
  // Clear command and arguments
  cmd[0] = '\0';
  arg[0][0] = '\0';
  arg[1][0] = '\0';
  
  // Skip leading spaces
  while (buf[i] == ' ') i++;
  
  // Extract command
  while (buf[i] != ' ' && buf[i] != '\0') {
    cmd[j] = buf[i];
    i++;
    j++;
  }
  cmd[j] = '\0';
  
  // Extract arguments
  while (buf[i] != '\0' && argCount < 2) {
    // Skip spaces
    while (buf[i] == ' ') i++;
    
    if (buf[i] == '\0') break;
    
    // Extract argument
    j = 0;
    while (buf[i] != ' ' && buf[i] != '\0') {
      arg[argCount][j] = buf[i];
      i++;
      j++;
    }
    arg[argCount][j] = '\0';
    argCount++;
  }
}

void executeCommand(char *buf) {
  char cmd[64];
  char arg[2][64];
  
  parseCommand(buf, cmd, arg);
  
  // Handle empty command
  if (cmd[0] == '\0') {
    return;
  }
  
  // User command
  if (strcmp(cmd, "user")) {
    if (arg[0][0] == '\0') {
      strcpy(username, "user");
      printString("Username changed to user\n");
    } else {
      strcpy(username, arg[0]);
      printString("Username changed to ");
      printString(username);
      printString("\n");
    }
    return;
  }
  
  // Grand Company commands
  if (strcmp(cmd, "grandcompany")) {
    if (strcmp(arg[0], "maelstrom")) {
      clearScreen();
      strcpy(grandcompany, "maelstrom");
      colorMode = 1; // Red
    } else if (strcmp(arg[0], "twinadder")) {
      clearScreen();
      strcpy(grandcompany, "twinadder");
      colorMode = 2; // Yellow
    } else if (strcmp(arg[0], "immortalflames")) {
      clearScreen();
      strcpy(grandcompany, "immortalflames");
      colorMode = 3; // Blue
    } else {
      printString("Error: Invalid grand company\n");
    }
    return;
  }
  
  // Clear command
  if (strcmp(cmd, "clear")) {
    clearScreen();
    grandcompany[0] = '\0';
    colorMode = 0;
    return;
  }
  
  // Calculator commands
  if (strcmp(cmd, "add")) {
    int num1, num2;
    atoi(arg[0], &num1);
    atoi(arg[1], &num2);
    int result = num1 + num2;
    char resultStr[32];
    itoa(result, resultStr);
    printString(resultStr);
    printString("\n");
    return;
  }
  
  if (strcmp(cmd, "sub")) {
    int num1, num2;
    atoi(arg[0], &num1);
    atoi(arg[1], &num2);
    int result = num1 - num2;
    char resultStr[32];
    itoa(result, resultStr);
    printString(resultStr);
    printString("\n");
    return;
  }
  
  if (strcmp(cmd, "mul")) {
    int num1, num2;
    atoi(arg[0], &num1);
    atoi(arg[1], &num2);
    int result = num1 * num2;
    char resultStr[32];
    itoa(result, resultStr);
    printString(resultStr);
    printString("\n");
    return;
  }
  
  if (strcmp(cmd, "div")) {
    int num1, num2;
    atoi(arg[0], &num1);
    atoi(arg[1], &num2);
    int result = div(num1, num2);
    char resultStr[32];
    itoa(result, resultStr);
    printString(resultStr);
    printString("\n");
    return;
  }
  
  // Yogurt command
  if (strcmp(cmd, "yogurt")) {
    printString(yogurt_responses[yogurt_index]);
    printString("\n");
    yogurt_index = (yogurt_index + 1) % 4;
    return;
  }
  
  // Echo command (default behavior)
  printString(buf);
  printString("\n");
}
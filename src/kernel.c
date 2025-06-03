#include "shell.h"
#include "kernel.h"
#include "std_lib.h"

int textColor = 0x07;
char currentUsername[64] = "user";
char host[32] = "";

int mod_safe(int a, int b) {
    while (a >= b) a = a - b;
    while (a < 0) a = a + b;
    return a;
}

void setTextColor(int color) {
  // ganti semua attribute karakter di video memory (warna)
  int i;
  for (int i = 0; i < 80 * 25; i++) {
    putInMemory(0xB000, i * 2 + 1, color);
  }
}

int main() {
  clearScreen();
  shell();
}

void printString(char *str)
{
  // Implementasi fungsi untuk mencetak string
  int i = 0;
  while (str[i] != '\0') {
    if (str[i] == '\n') {
      // newline: pindah baris
      _interrupt(0x10, 0x0E00 + '\r', 0, 0, 0);
      _interrupt(0x10, 0x0E00 + '\n', 0, 0, 0);
    } else {
      _interrupt(0x10, 0x0E00 + str[i], 0, 0, 0);
    }
    i++;
  }
}

void readString(char *buf)
{
  // Implementasi fungsi untuk membaca string
  int i = 0;
  char c;

  while (1) {
    c = _interrupt(0x16, 0, 0, 0, 0); // baca keyboard

    if (c == 0x0D) { // ENTER
      buf[i] = '\0';
      printString("\n");
      break;
    } else if (c == 0x08) { // BACKSPACE
      if (i > 0) {
        i--;
        printString("\b \b");
      }
    } else {
      buf[i++] = c;
      _interrupt(0x10, 0x0E00 + c, 0, 0, 0); // tampilkan char
    }
  }
}

void clearScreen()
{
  // Implementasi fungsi untuk membersihkan layar
  int i;
  for (i = 0; i < 25 * 80; i++) {
    putInMemory(0xB800, i * 2, ' ');
    putInMemory(0xB800, i * 2 + 1, 0x07); // Warna putih
  }
  _interrupt(0x10, 0x0200, 0, 0, 0); // Set cursor to top-left
}

void handleYogurt() {
    char *responses[3];
    int count, index;

    responses[0] = "yo";
    responses[1] = "ts unami gng </3";
    responses[2] = "sygau";
    count = 3;

    index = mod_safe(getBiosTick(), count);

    printString("gurt> ");
    printString(responses[index]);
    printString("\r\n");
}

void shell() {
    char buf[128];
    char cmd[64];
    char arg[2][64];

    printString("Welcome to EorzeOS!\r\n");

    while (true) {
        printString(currentUsername);
        printString(host);
        printString("> ");

        readString(buf);
        parseCommand(buf, cmd, arg);
        handleCommand(cmd, arg, buf);
    }
}

void parseCommand(char *buf, char *cmd, char arg[2][64]) {
    // Implementasi fungsi untuk mem-parsing perintah
    int i = 0, j = 0;

    cmd[0] = '\0';
    arg[0][0] = '\0';
    arg[1][0] = '\0';

    // Parse command
    while (buf[i] != ' ' && buf[i] != '\0' && i < 63) {
        cmd[i] = buf[i];
        i++;
    }
    cmd[i] = '\0';

    // Skip spaces after command
    while (buf[i] == ' ') i++;

    // Parse first argument
    j = 0;
    while (buf[i] != ' ' && buf[i] != '\0' && j < 63) {
        arg[0][j++] = buf[i++];
    }
    arg[0][j] = '\0';

    // Skip spaces after first argument
    while (buf[i] == ' ') i++;

    // Parse second argument
    j = 0;
    while (buf[i] != '\0' && j < 63) {
        arg[1][j++] = buf[i++];
    }
    arg[1][j] = '\0';
}

void handleCommand(char *cmd, char arg[2][64], char *buf) {
    if (strcmp(cmd, "grandcompany")) {
        if (strcmp(arg[0], "maelstrom")) {
            _interrupt(0x10, 0x0200, 0, 0, 0);
            setTextColor(0x0C);  // merah
            clearScreen(textColor);
            strcpy(host, "@Storm");
            printString("\r");
        } else if (strcmp(arg[0], "twinadder")) {
            _interrupt(0x10, 0x0200, 0, 0, 0);
            setTextColor(0x0E);  // kuning
            clearScreen(textColor);
            strcpy(host, "@Serpent");
            printString("\r");
        } else if (strcmp(arg[0], "immortalflames")) {
            _interrupt(0x10, 0x0200, 0, 0, 0);
            setTextColor(0x09);  // biru
            clearScreen(textColor);
            strcpy(host, "@Flame");
            printString("\r");
        } else {
            printString("Unknown company\r\n");
            printString("\r");
        }

    } else if (strcmp(cmd, "user")) {
      if (arg[0][0] != '\0') {
        strcpy(currentUsername, arg[0]);
        printString("Username changed to ");
        printString(currentUsername);
        printString("\r\n");
    } else {
        strcpy(currentUsername, "user");
        printString("Username changed to user\r\n");
    }

    } else if (strcmp(cmd, "yo")) {
        printString("gurt\r\n");
        printString("\r");
    } else if (strcmp(cmd, "gurt")) {
        printString("yo\n");
        printString("\r");
    } else if (strcmp(cmd, "clear")) {
        _interrupt(0x10, 0x0200, 0, 0, 0);
        setTextColor(0x07);  // putih
        clearScreen(textColor);
        strcpy(host, "");
        strcpy(currentUsername, "user");
        printString("\r");

    } else if (strcmp(cmd, "add") || strcmp(cmd, "sub") || strcmp(cmd, "mul") || strcmp(cmd, "div")) {
        int a = 0, b = 0, res = 0;
        char resultStr[64];

        atoi(arg[0], &a);
        atoi(arg[1], &b);

        if (strcmp(cmd, "add")) res = a + b;
        else if (strcmp(cmd, "sub")) res = a - b;
        else if (strcmp(cmd, "mul")) res = a * b;
        else if (strcmp(cmd, "div")) {
            if (b == 0) {
                printString("Division by zero error!\r\n");
                return;
            }
            res = div(a, b);
        }

        itoa(res, resultStr);
        printString(resultStr);
        printString("\r\n");


    } else if (strcmp(cmd, "yogurt")) {
        handleYogurt();
    } else {
        printString(buf);
        printString("\r\n");
    }
}
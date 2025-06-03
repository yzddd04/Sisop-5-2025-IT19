#include "shell.h"
#include "kernel.h"

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
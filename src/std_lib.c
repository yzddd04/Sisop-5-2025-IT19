#include "std_lib.h"

int div(int a, int b)
{
  // Implementasi pembagian
  // NOTE: BISA ANGKA NEGATIF
  int res = 0;
  int sign = 1;

  if (a < 0) {
    a = -a;
    sign = -sign;
  }
  if (b < 0) {
    b = -b;
    sign = -sign;
  }

  while (a >= b) {
    a -= b;
    res++;
  }

  return res * sign;
}

int mod(int a, int b)
{
  // Implementasi modulus
  // NOTE: BISA ANGKA NEGATIF
  int sign = 1;
  if (a < 0) {
    a = -a;
    sign = -sign;
  }
  if (b < 0) {
    b = -b;
  }

  while (a >= b) {
    a -= b;
  }

  return a * sign;
}

bool strcmp(char *str1, char *str2)
{
  // Implementasi perbandingan string
  int i = 0;
  while (str1[i] != '\0' && str2[i] != '\0') {
    if (str1[i] != str2[i]) {
      return false;
    }
    i++;
  }
  return str1[i] == '\0' && str2[i] == '\0';
}

void strcpy(char *dst, char *src)
{
  // Implementasi penyalinan string
  int i = 0;
  while (src[i] != '\0') {
    dst[i] = src[i];
    i++;
  }
  dst[i] = '\0';
}

void clear(byte *buf, unsigned int size)
{
  // Implementasi pembersihan buffer
  unsigned int i;
  for (i = 0; i < size; i++) {
    buf[i] = 0;
  }
}

void atoi(char *str, int *num)
{
  // Implementasi konversi string ke integer
  // NOTE: BISA ANGKA NEGATIF
  *num = 0;
  int sign = 1;
  int i = 0;

  if (str[0] == '-') {
    sign = -1;
    i++;
  }

  while (str[i] != '\0') {
    *num = *num * 10 + (str[i] - '0');
    i++;
  }

  *num *= sign;
}

void itoa(int num, char *str)
{
  // Implementasi konversi integer ke string
  // NOTE: BISA ANGKA NEGATIF
  int i = 0;
  int sign = 0;
  int temp;

  if (num == 0) {
    str[0] = '0';
    str[1] = '\0';
    return;
  }

  if (num < 0) {
    sign = 1;
    num = -num;
  }

  while (num != 0) {
    temp = num % 10;
    str[i++] = temp + '0';
    num /= 10;
  }

  if (sign) {
    str[i++] = '-';
  }

  str[i] = '\0';

  // Reverse the string
  int start = 0;
  int end = i - 1;
  char swap;
  while (start < end) {
    swap = str[start];
    str[start] = str[end];
    str[end] = swap;
    start++;
    end--;
  }
}
#include "std_lib.h"

int div(int a, int b)
{
  if (b == 0) return 0; 
  
  bool negative = false;
  if ((a < 0 && b > 0) || (a > 0 && b < 0)) {
    negative = true;
  }
  
  // Make both numbers positive
  if (a < 0) a = -a;
  if (b < 0) b = -b;
  
  int result = 0;
  while (a >= b) {
    a -= b;
    result++;
  }
  
  return negative ? -result : result;
}

int mod(int a, int b)
{
  if (b == 0) return 0; // Handle modulo by zero
  
  bool negative = (a < 0);
  
  // Make both numbers positive for calculation
  if (a < 0) a = -a;
  if (b < 0) b = -b;
  
  while (a >= b) {
    a -= b;
  }
  
  return negative ? -a : a;
}

bool strcmp(char *str1, char *str2)
{
  int i = 0;
  while (str1[i] != '\0' && str2[i] != '\0') {
    if (str1[i] != str2[i]) {
      return false;
    }
    i++;
  }
  return str1[i] == str2[i]; // Both should be '\0' if equal
}

void strcpy(char *dst, char *src)
{
  int i = 0;
  while (src[i] != '\0') {
    dst[i] = src[i];
    i++;
  }
  dst[i] = '\0';
}

void clear(byte *buf, unsigned int size)
{
  unsigned int i;
  for (i = 0; i < size; i++) {
    buf[i] = 0;
  }
}

void atoi(char *str, int *num)
{
  *num = 0;
  int i = 0;
  bool negative = false;
  
  // Check for negative sign
  if (str[0] == '-') {
    negative = true;
    i = 1;
  } else if (str[0] == '+') {
    i = 1;
  }
  
  // Convert digits
  while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9') {
    *num = *num * 10 + (str[i] - '0');
    i++;
  }
  
  if (negative) {
    *num = -*num;
  }
}

void itoa(int num, char *str)
{
  int i = 0;
  bool negative = false;
  
  // Handle negative numbers
  if (num < 0) {
    negative = true;
    num = -num;
  }
  
  // Handle zero case
  if (num == 0) {
    str[0] = '0';
    str[1] = '\0';
    return;
  }
  
  // Convert digits (in reverse order)
  while (num > 0) {
    str[i] = (num % 10) + '0';
    num = num / 10;
    i++;
  }
  
  // Add negative sign if needed
  if (negative) {
    str[i] = '-';
    i++;
  }
  
  str[i] = '\0';
  
  // Reverse the string
  int start = 0;
  int end = i - 1;
  while (start < end) {
    char temp = str[start];
    str[start] = str[end];
    str[end] = temp;
    start++;
    end--;
  }
}
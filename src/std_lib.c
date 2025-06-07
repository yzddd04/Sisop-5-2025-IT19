#include "std_lib.h"

// Binary search based division - O(log n) complexity
int safeDivide(int numerator, int denominator) {
    if (denominator == 0) return 0;
    
    bool negResult = (numerator < 0) ^ (denominator < 0);
    
    // Convert to positive using bit manipulation
    unsigned int num = (numerator < 0) ? (~numerator + 1) : numerator;
    unsigned int den = (denominator < 0) ? (~denominator + 1) : denominator;
    
    if (num < den) return 0;
    
    unsigned int quotient = 0;
    unsigned int temp = 0;
    
    // Binary search approach
    for (int i = 31; i >= 0; i--) {
        if (temp + (den << i) <= num) {
            temp += (den << i);
            quotient |= (1U << i);
        }
    }
    
    return negResult ? (~quotient + 1) : quotient;
}

// Optimized modulo using fast division
int safeMod(int num, int base) {
    if (base == 0) return 0;
    
    int quotient = safeDivide(num, base);
    return num - (quotient * base);
}

// SIMD-style comparison (comparing 4 bytes at once when possible)
bool stringEqual(char *a, char *b) {
    if (!a || !b) return a == b;
    
    // Fast path: compare words when aligned
    while (((uintptr_t)a & 3) == 0 && ((uintptr_t)b & 3) == 0) {
        uint32_t word_a = *(uint32_t*)a;
        uint32_t word_b = *(uint32_t*)b;
        
        if (word_a != word_b) break;
        
        // Check for null terminator in the word
        uint32_t null_check = word_a ^ 0x00000000;
        if (((null_check - 0x01010101) & ~null_check & 0x80808080) != 0) {
            return true; // Found null, strings are equal
        }
        
        a += 4;
        b += 4;
    }
    
    // Fallback to byte comparison
    while (*a && *b && *a == *b) {
        a++;
        b++;
    }
    
    return *a == *b;
}

// Block copy optimization
void stringCopy(char *dest, char *src) {
    if (!dest || !src) return;
    
    // Copy in blocks of 8 bytes when possible
    while (((uintptr_t)src & 7) == 0 && ((uintptr_t)dest & 7) == 0) {
        uint64_t block = *(uint64_t*)src;
        
        // Check for null byte in the block
        if (((block - 0x0101010101010101ULL) & ~block & 0x8080808080808080ULL) != 0) {
            break;
        }
        
        *(uint64_t*)dest = block;
        src += 8;
        dest += 8;
    }
    
    // Copy remaining bytes
    while ((*dest++ = *src++) != '\0');
}

// Vectorized memory zeroing
void zeroMemory(byte *buffer, unsigned int len) {
    if (!buffer || len == 0) return;
    
    // Zero in 8-byte chunks
    while (len >= 8 && ((uintptr_t)buffer & 7) == 0) {
        *(uint64_t*)buffer = 0;
        buffer += 8;
        len -= 8;
    }
    
    // Zero in 4-byte chunks
    while (len >= 4 && ((uintptr_t)buffer & 3) == 0) {
        *(uint32_t*)buffer = 0;
        buffer += 4;
        len -= 4;
    }
    
    // Zero remaining bytes
    while (len-- > 0) {
        *buffer++ = 0;
    }
}

// Horner's method for string to integer conversion - O(n)
void stringToInt(char *text, int *value) {
    if (!text || !value) return;
    
    *value = 0;
    bool isNegative = false;
    int index = 0;
    
    // Skip whitespace
    while (text[index] == ' ' || text[index] == '\t') index++;
    
    // Handle sign
    if (text[index] == '-') {
        isNegative = true;
        index++;
    } else if (text[index] == '+') {
        index++;
    }
    
    // Convert using Horner's method: result = result * 10 + digit
    while (text[index] >= '0' && text[index] <= '9') {
        int digit = text[index] - '0';
        
        // Overflow check
        if (*value > (INT_MAX - digit) / 10) {
            *value = isNegative ? INT_MIN : INT_MAX;
            return;
        }
        
        *value = (*value << 3) + (*value << 1) + digit; // *value * 10 + digit
        index++;
    }
    
    if (isNegative) {
        *value = -*value;
    }
}

// Lookup table optimization for integer to string conversion
void intToString(int value, char *buffer) {
    if (!buffer) return;
    
    static const char digits[200] = {
        '0','0','0','1','0','2','0','3','0','4','0','5','0','6','0','7','0','8','0','9',
        '1','0','1','1','1','2','1','3','1','4','1','5','1','6','1','7','1','8','1','9',
        '2','0','2','1','2','2','2','3','2','4','2','5','2','6','2','7','2','8','2','9',
        '3','0','3','1','3','2','3','3','3','4','3','5','3','6','3','7','3','8','3','9',
        '4','0','4','1','4','2','4','3','4','4','4','5','4','6','4','7','4','8','4','9',
        '5','0','5','1','5','2','5','3','5','4','5','5','5','6','5','7','5','8','5','9',
        '6','0','6','1','6','2','6','3','6','4','6','5','6','6','6','7','6','8','6','9',
        '7','0','7','1','7','2','7','3','7','4','7','5','7','6','7','7','7','8','7','9',
        '8','0','8','1','8','2','8','3','8','4','8','5','8','6','8','7','8','8','8','9',
        '9','0','9','1','9','2','9','3','9','4','9','5','9','6','9','7','9','8','9','9'
    };
    
    if (value == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }
    
    bool isNegative = value < 0;
    unsigned int num = isNegative ? (~value + 1) : value;
    char temp[12]; // Max digits for 32-bit int
    int pos = 0;
    
    // Process two digits at a time
    while (num >= 100) {
        unsigned int remainder = num % 100;
        num /= 100;
        temp[pos++] = digits[remainder * 2 + 1];
        temp[pos++] = digits[remainder * 2];
    }
    
    // Handle remaining digits
    if (num >= 10) {
        temp[pos++] = digits[num * 2 + 1];
        temp[pos++] = digits[num * 2];
    } else {
        temp[pos++] = '0' + num;
    }
    
    // Add negative sign
    if (isNegative) {
        temp[pos++] = '-';
    }
    
    // Reverse string
    for (int i = 0; i < pos; i++) {
        buffer[i] = temp[pos - 1 - i];
    }
    buffer[pos] = '\0';
}
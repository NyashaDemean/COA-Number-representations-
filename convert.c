#include <stdio.h>
#include <stdint.h>
#include <string.h>


// Convert number to string in base (2-16) using division algorithm
void div_convert(uint32_t n, int base, char *out) {
    char digits[] = "0123456789ABCDEF";
    char buffer[65];
    int pos = 0;

    // Handle the zero case
    if (n == 0) {
        strcpy(out, "0");
        return;
    }

    // Ectract digits from right to left
    while (n > 0){
        buffer[pos] = digits[n % base];
        pos++;
        n /= base;
    }

    // Reverse into out
    int j;
    for (j = 0; j < pos; j++){
        out[j] = buffer[pos - j - 1];
    }
    out[pos] = '\0';
}


// Convert number to string in base (2-16) using subtraction of powers
void sub_convert(uint32_t n, int base, char *out) {
    char digits[] = "0123456789ABCDEF";
    char buffer[65];
    int pos = 0;

    // Handle the zero case
    if (n == 0) {
        strcpy(out, "0");
        return;
    }

    //Find the largest power of the base <= n
    uint32_t power = 1;
    while (power <= n / base){
        power *= base;
    }

    while (power > 0){
        int digit = n / power;
        buffer[pos] = digits[digit];
        pos++;
        n -= digit * power;
        power /= base;
    }

    buffer[pos] = '\0';
    strcpy(out, buffer);
}


void print_tables(uint32_t n){
    char bin[65], oct[65], dec[65], hex[65];

    // Original
    div_convert(n, 2, bin);
    div_convert(n, 8, oct);
    sprintf(dec, "%u", n);
    div_convert(n, 16, hex);
    printf("Original: Binary=%s Octal=%s Decimal=%s Hex=%s\n", bin, oct, dec, hex);

    //Left shift by 3
    uint32_t shifted = n << 3;
    div_convert(shifted, 2, bin);
    div_convert(shifted, 8, oct);
    sprintf(dec, "%u", shifted);
    div_convert(shifted, 16, hex);
    printf("Left Shift by 3: Binary=%s Octal=%s Decimal=%s Hex=%s\n", bin, oct, dec, hex);

    // With 0xFF
    uint32_t masked = n & 0xFF;
    div_convert(masked, 2, bin);
    div_convert(masked, 8, oct);
    sprintf(dec, "%u", masked);
    div_convert(masked, 16, hex);
    printf("AND with 0xFF: Binary=%s Octal=%s Decimal=%s Hex=%s\n", bin, oct, dec, hex);

}

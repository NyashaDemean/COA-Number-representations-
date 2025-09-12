#include <stdio.h>
#include <stdint.h>
#include <string.h>


// convert number to string in base (2-16) using divsion algorithm
void div_convert(uint32_t n, int base, char *out){
    char digits[] = "0123456789ABCDEF";
    char temp[65];
    int pos = 0;

    //handle case of zero
    if(n==0){
        strcpy(out, "0");
        return;
    }
    //get remainders from right to left
    while(n>0){
        temp[pos] = digits[n % base];
        n = n/base;
        pos++;
    }
    //reverse the remainders
    int j;
    for(j=0; j<pos; j++){
        out[j] = temp[pos - j - 1];
    }
    out[pos] = '\0';
}

void sub_convert(uint32_t n, int base, char *out){
    char digits[] = "0123456789ABCDEF";
    char temp[65];
    int pos = 0;

    if (n == 0) {
        strcpy(out, "0");
        return;
    }

    uint32_t power = 1;
    while(power <= n/base){
        power = power * base;
    }

    while(power > 0){
        temp[pos] = digits[n/power];
        n = n%power;
        pos++;
        power= power/base;
    }

    temp[pos] = '\0';
    strcpy(out,temp);
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
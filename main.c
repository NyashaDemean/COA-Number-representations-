#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>   // for isspace

void div_convert(uint32_t n, int base, char *out);
void sub_convert(uint32_t n, int base, char *out);
void print_tables(uint32_t n);

int main(void) {
    FILE *in = fopen("a1_test_file.txt", "r");
    if (!in) {
        perror("a1_test_file.txt");
        return 1;
    }

    char line[256];
    char out[65];

    while (fgets(line, sizeof line, in)) {
        // skip blanks and comments
        char *p = line;
        while (isspace((unsigned char)*p)) p++;
        if (*p == '\0' || *p == '\n' || *p == '#') continue;

        int option, base;
        uint32_t num;

        // read option first
        if (sscanf(p, "%d", &option) != 1) {
            fprintf(stderr, "Bad line (no option): %s", line);
            continue;
        }

        switch (option) {
            case 1: { // "1 <num> <base>"
                if (sscanf(p, "%*d %u %d", &num, &base) != 2) {
                    fprintf(stderr, "Bad line for option 1: %s", line);
                    break;
                }
                div_convert(num, base, out);
                printf("DIV  num=%u base=%d -> %s\n", num, base, out);
                break;
            }
            case 2: { // "2 <num> <base>"
                if (sscanf(p, "%*d %u %d", &num, &base) != 2) {
                    fprintf(stderr, "Bad line for option 2: %s", line);
                    break;
                }
                sub_convert(num, base, out);
                printf("SUB  num=%u base=%d -> %s\n", num, base, out);
                break;
            }
            case 3: { // "3 <num>"
                if (sscanf(p, "%*d %u", &num) != 1) {
                    fprintf(stderr, "Bad line for option 3: %s", line);
                    break;
                }
                print_tables(num);
                break;
            }
            case 4:   // "4"
                printf("Exit (from file)\n");
                fclose(in);
                return 0;

            default:
                fprintf(stderr, "Unknown option: %d (line: %s)", option, line);
        }
    }

    fclose(in);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int loc;
    printf("enter the location to relocate to: ");
    scanf("%x", &loc);

    FILE* fin = fopen("reloc_in.txt", "r");

    fseek(fin, 9, SEEK_SET);
    
    int start;
    fscanf(fin, "%x", &start);

    int offset = loc - start;

    fseek(fin, 24, SEEK_SET);

    char type;
    fscanf(fin, "%c", &type);

    while (type != 'E') {
        int tstart, tlen, tbits;
        fscanf(fin, "^%x^%x^%x^", &tstart, &tlen, &tbits);

        int i = 11;

        while (1) {
            int tbit = (1 << i) & tbits;
            char next;

            if (!tbit) {
                char hex[100];
                int hi = 0;

                while (1) {
                    next = fgetc(fin);
                    if (next == '^' || next == '\n') break;

                    hex[hi++] = next;
                }

                printf("%06x %s\n", tstart + offset, hex);
                tstart += strlen(hex) / 2;
            }

            else {
                int op;
                fscanf(fin, "%x", &op);
                printf("%06x %06x\n", tstart + offset, op + offset);
                tstart += 3;
                fscanf(fin, "%c", &next);
            }

            --i;

            if (next == '\n') break;
        }

        fscanf(fin, "%c", &type);
    }

    return 0;
}

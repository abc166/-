#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main() {
    FILE* fin = fopen("in.txt", "r");

    char result[1000];
    memset(result, 'x', sizeof(result));

    int start, len;

    fseek(fin, 9, SEEK_SET);
    fscanf(fin, "%x^%x", &start, &len);
    fgetc(fin);

    while (1) {
        char recType;
        int textStart, textLen;

        fscanf(fin, "%c", &recType);

        if (recType == 'E') 
            break;

        fscanf(fin, "^%x^%x", &textStart, &textLen);

        char ch;
        int i = 2 * (textStart - start);

        while (1) {
            ch = fgetc(fin);
            if (ch == '\0' || ch == '\n')
                 break;

            if (ch == '^') 
                continue;

            result[i++] = ch;
        }
    }

    for (int i = 0; i < len; ++i) {
        printf("%x\t%c%c\n", start + i, result[2 * i], result[2 * i + 1]);
    }
}
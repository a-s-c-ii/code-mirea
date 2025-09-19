#include <stdio.h>
#include <string.h>

int main() {
    FILE *in = fopen("input14.txt", "r");
    FILE *out = fopen("output14.txt", "w");
    char buffer[10000];
    int len = 0;
    int ch;

    if (!in || !out) {
        printf("Ошибка открытия файла\n");
        return 1;
    }

    while ((ch = fgetc(in)) != EOF) {
        if (ch != '\n' && ch != '\r') {
            buffer[len++] = (char)ch;
        }
    }
    buffer[len] = '\0';

    int count = 0;
    for (int i = 0; i < len; i++) {
        fputc(buffer[i], out);
        count++;

        if (buffer[i] == '.') {
            fputc('\n', out);
            count = 0;
        }
        else if (count == 60) {
            fputc('\n', out);
            count = 0;
        }
    }

    if (count > 0) {
        fputc('\n', out);
    }

    fclose(in);
    fclose(out);
    return 0;
}
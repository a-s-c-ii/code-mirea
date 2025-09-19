#include <stdio.h>
#include <string.h>

int main() {
    FILE *in = fopen("input13.txt", "r");
    FILE *out = fopen("output13.txt", "w");
    char line[256];

    if (!in || !out) {
        printf("Ошибка открытия файла\n");
        return 1;
    }

    while (fgets(line, sizeof(line), in)) {
        size_t len = strlen(line);

        while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r')) {
            line[len - 1] = '\0';
            len--;
        }

        fputs(line, out);

        for (size_t i = len; i < 50; i++) {
            fputc(' ', out);
        }

        fputc('\n', out);
    }

    fclose(in);
    fclose(out);
    return 0;
}
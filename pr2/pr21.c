#include <stdio.h>
#include <string.h>

int main() {
    FILE *f = fopen("input12.txt", "r");
    if (!f) {
        perror("Ошибка открытия файла");
        return 1;
    }

    char line[256];
    int count = 0;

    while (fgets(line, sizeof(line), f)) {
        int len = strlen(line);

        if (len > 0 && line[len - 1] == '\n') {
            line[--len] = '\0';
        }

        if (len > 0 && line[0] == line[len - 1]) {
            count++;
        }
    }

    fclose(f);

    printf("Количество строк: %d\n", count);
    return 0;
}
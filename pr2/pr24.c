#include <stdio.h>

int main() {
    FILE *in = fopen("input15.txt", "r");
    FILE *out = fopen("output15.txt", "w");
    if (!in || !out) {
        perror("Ошибка открытия файла");
        return 1;
    }

    double prev, curr;
    int len = 1;

    if (fscanf(in, "%lf", &prev) == 1) {
        while (fscanf(in, "%lf", &curr) == 1) {
            if (curr < prev) {
                len++;
            } else {
                if (len > 1) fprintf(out, "%d ", len);
                len = 1;
            }
            prev = curr;
        }
        if (len > 1) fprintf(out, "%d ", len);
    }

    fclose(in);
    fclose(out);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

long file_size(const char *filename) {
    FILE *f = fopen(filename, "rb");
    if (!f) return -1;
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fclose(f);
    return size;
}

int copy_file(const char *src, const char *dst) {
    FILE *in = fopen(src, "rb");
    FILE *out = fopen(dst, "wb");
    if (!in || !out) return 1;

    char buffer[1024];
    size_t n;
    while ((n = fread(buffer, 1, sizeof(buffer), in)) > 0) {
        fwrite(buffer, 1, n, out);
    }

    fclose(in);
    fclose(out);
    return 0;
}

int main() {
    char f1[100], f2[100], f3[100];
    printf("Введите имена 3 файлов: ");
    scanf("%s %s %s", f1, f2, f3);

    long s1 = file_size(f1);
    long s2 = file_size(f2);
    long s3 = file_size(f3);

    if (s1 < 0 || s2 < 0 || s3 < 0) {
        printf("Ошибка открытия файлов\n");
        return 1;
    }

    // найти минимальный и максимальный
    char *minFile, *maxFile;
    long minSize = s1, maxSize = s1;
    minFile = maxFile = f1;

    if (s2 < minSize) minSize = s2, minFile = f2;
    if (s3 < minSize) minSize = s3, minFile = f3;

    if (s2 > maxSize) maxSize = s2, maxFile = f2;
    if (s3 > maxSize) maxSize = s3, maxFile = f3;

    if (copy_file(minFile, maxFile) == 0)
        printf("Файл %s заменён содержимым %s\n", maxFile, minFile);
    else
        printf("Ошибка копирования\n");

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFFER_SIZE 4096
#define MAX_FILENAME_LENGTH 256 

int main() {
    int fd; 
    ssize_t bytes_read;
    char buffer[BUFFER_SIZE];
    int freq[256] = {0};
    int i;
    int max_freq = 0;
    unsigned char max_char = 0;
    
    char filename[MAX_FILENAME_LENGTH];

    printf("Введите имя файла: ");
    
    if (fgets(filename, MAX_FILENAME_LENGTH, stdin) == NULL) {
        fprintf(stderr, "Ошибка при чтении ввода.\n");
        return 1;
    }
    
    for (i = 0; i < MAX_FILENAME_LENGTH; i++) {
        if (filename[i] == '\n') {
            filename[i] = '\0';
            break;
        }
    }

    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Ошибка при открытии файла");
        fprintf(stderr, "Не удалось открыть файл: %s\n", filename); 
        return 2;
    }

    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
        for (i = 0; i < bytes_read; i++) {
            freq[(unsigned char)buffer[i]]++;
        }
    }

    if (bytes_read == -1) {
        perror("Ошибка при чтении файла");
        close(fd);
        return 3;
    }

    if (close(fd) == -1) {
        perror("Ошибка при закрытии файла");
        return 4;
    }
    
    for (i = 0; i < 256; i++) {
        if (freq[i] > max_freq) {
            max_freq = freq[i];
            max_char = (unsigned char)i;
        }
    }

    printf("Символ, который встречается чаще всего:\n");
    
    if (max_char == '\n') {
        printf("  Символ: \\n (перевод строки)\n");
    } else if (max_char == '\t') {
        printf("  Символ: \\t (табуляция)\n");
    } else if (max_char == ' ') {
        printf("  Символ: ' ' (пробел)\n");
    } else if (max_char >= 32 && max_char <= 126) {
        printf("  Символ: '%c'\n", max_char);
    } else {
        printf("  Символ (ASCII/Dec): %d\n", max_char);
    }
    
    printf("  Количество вхождений: %d\n", max_freq);

    return 0;
}
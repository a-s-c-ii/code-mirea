#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#define LOG_FILE "system.log"

void log_time() {
    FILE *file;
    time_t rawtime;
    struct tm *info;
    char timestamp_buffer[80];
    char log_entry[100];

    time(&rawtime);
    info = localtime(&rawtime);

    strftime(timestamp_buffer, 80, "%Y-%m-%d %H:%M:%S", info);

    file = fopen(LOG_FILE, "a");
    if (file == NULL) {
        perror("Ошибка открытия лог-файла");
        return;
    }

    snprintf(log_entry, sizeof(log_entry), "%s - Log entry\n", timestamp_buffer);

    if (fputs(log_entry, file) == EOF) {
        perror("Ошибка записи в лог-файл");
    }

    fclose(file);
}

int main() {
    printf("Программа логирования запущена. Запись в '%s'...\n", LOG_FILE);

    while (1) {
        log_time();
        sleep(1); 
    }

    return 0;
}
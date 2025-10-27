#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

#define SOURCE_LOG_FILE "system.log"
#define ARCHIVE_DIR "log_archive"
#define INTERVAL_SECONDS 5

int create_zip_archive(const char *source_file, const char *archive_path, const char *archive_name) {
    char command[512];
    
    snprintf(command, sizeof(command), "zip -j -m %s/%s %s", 
             ARCHIVE_DIR, archive_name, source_file);

    printf("Выполнение команды архивирования: %s\n", command);
    
    int status = system(command);

    if (status == -1) {
        perror("Ошибка выполнения команды system()");
        return -1;
    }
    
    if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
        return 0; 
    } else {
        fprintf(stderr, "Ошибка архивирования. Код завершения: %d\n", WEXITSTATUS(status));
        if (access(source_file, F_OK) == 0) {
            if (remove(source_file) == 0) {
                printf("Исходный файл '%s' удален после неудачной архивации.\n", source_file);
            } else {
                perror("Не удалось удалить исходный файл после неудачной архивации");
            }
        }
        return -1;
    }
}

void archive_log() {
    time_t rawtime;
    struct tm *info;
    char timestamp_buffer[20];
    char archive_file_name[100];

    if (access(SOURCE_LOG_FILE, F_OK) != 0) {
        printf("Файл '%s' не найден. Пропуск архивации.\n", SOURCE_LOG_FILE);
        return;
    }
    
    if (mkdir(ARCHIVE_DIR, S_IRWXU | S_IRWXG | S_IRWXO) == -1 && errno != EEXIST) {
        perror("Ошибка создания директории архива");
        return;
    }

    time(&rawtime);
    info = localtime(&rawtime);
    strftime(timestamp_buffer, 20, "%Y%m%d_%H%M%S", info);
    snprintf(archive_file_name, sizeof(archive_file_name), "log_%s.zip", timestamp_buffer);

    if (create_zip_archive(SOURCE_LOG_FILE, ARCHIVE_DIR, archive_file_name) == 0) {
        printf("Успешно заархивирован: %s/%s\n", ARCHIVE_DIR, archive_file_name);
    } else {
        fprintf(stderr, "Архивация не удалась.\n");
    }
}

int main() {
    printf("Программа архивирования запущена. Интервал: %d секунд.\n", INTERVAL_SECONDS);

    while (1) {
        archive_log();
        sleep(INTERVAL_SECONDS); 
    }

    return 0;
}
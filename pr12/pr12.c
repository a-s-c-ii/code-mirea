#define _DEFAULT_SOURCE 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>

#define PATH_MAX_SIZE 1024

int is_txt_file(const char *filename) {
    const char *dot = strrchr(filename, '.'); 
    if (!dot || dot == filename) {
        return 0; 
    }
    return (strcmp(dot, ".txt") == 0); 
}

void count_txt_in_directory(const char *dir_path) {
    DIR *dir;
    struct dirent *entry;
    int txt_count = 0;

    dir = opendir(dir_path);
    if (dir == NULL) {
        perror("opendir error");
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) { 
            if (is_txt_file(entry->d_name)) {
                txt_count++;
            }
        }
    }

    closedir(dir);
    
    printf("[PID %d] В каталоге %s найдено %d .txt файлов.\n", getpid(), dir_path, txt_count);
    
    exit(txt_count); 
}

int main(int argc, char *argv[]) {
    DIR *dir;
    struct dirent *entry;
    char base_path[PATH_MAX_SIZE];
    int total_txt_files = 0;
    int child_status;
    pid_t pid;
    
    if (argc != 2) {
        fprintf(stderr, "Использование: %s <путь_к_каталогу>\n", argv[0]);
        return 1;
    }
    strncpy(base_path, argv[1], PATH_MAX_SIZE - 1);
    base_path[PATH_MAX_SIZE - 1] = '\0';

    dir = opendir(base_path);
    if (dir == NULL) {
        perror("opendir error");
        return 1;
    }

    printf("Главный процесс [PID %d] начал обход каталога %s...\n", getpid(), base_path);

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            
            char full_path[PATH_MAX_SIZE];
            
            strncpy(full_path, base_path, PATH_MAX_SIZE - 1);
            full_path[PATH_MAX_SIZE - 1] = '\0';

            strncat(full_path, "/", PATH_MAX_SIZE - strlen(full_path) - 1);
            
            strncat(full_path, entry->d_name, PATH_MAX_SIZE - strlen(full_path) - 1);

            pid = fork(); 

            if (pid == -1) {
                perror("fork error");
                continue; 
            } 
            else if (pid == 0) {
                count_txt_in_directory(full_path); 
            } 
        }
    }
    
    closedir(dir);

    printf("\nГлавный процесс ожидает завершения дочерних процессов...\n");
    
    while ((pid = wait(&child_status)) > 0) {
        if (WIFEXITED(child_status)) {
            int count = WEXITSTATUS(child_status);
            total_txt_files += count; 
            printf("[PID %d] Дочерний процесс завершился (нашел %d файлов).\n", pid, count);
        } else {
             printf("[PID %d] Дочерний процесс завершился ненормально.\n", pid);
        }
    }

    printf("Общий итог: Во всех подкаталогах найдено %d .txt файлов.\n", total_txt_files);

    return 0;
}

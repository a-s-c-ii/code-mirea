#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define FILENAME "/home/zzz/C/pr7/text.txt"

void read_file() {
    FILE *file = fopen(FILENAME, "r");
    char buffer[256];
    
    if (file == NULL) {
        perror("Ошибка при открытии файла для ЧТЕНИЯ");
        return;
    }

    if (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("Успешно прочитано. Содержимое: %s", buffer);
    } else {
        printf("Файл пуст или ошибка чтения.\n");
    }
    
    fclose(file);
}

void write_file() {
    FILE *file = fopen(FILENAME, "a"); 
    
    if (file == NULL) {
        perror("Ошибка при открытии файла для ЗАПИСИ (Ожидается для User3!)");
        return;
    }

    fprintf(file, "\nДобавлено User/Group: %d.", getuid()); 
    printf("Успешно записано в файл.\n");

    fclose(file);
}

int main() {
    printf("Проверка доступа к файлу: %s\n", FILENAME);
    
    printf("\nПопытка ЧТЕНИЯ:\n");
    read_file();
    
    printf("\nПопытка ЗАПИСИ:\n");
    write_file();
    
    printf("\nПроверка завершена.\n");
    return 0;
}
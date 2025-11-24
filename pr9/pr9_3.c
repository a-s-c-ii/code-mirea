#include <stdio.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1024

int main() {
    char line[MAX_LINE_LENGTH];
    long total_digit_count = 0;
    
    while (fgets(line, MAX_LINE_LENGTH, stdin) != NULL) {
        for (int i = 0; line[i] != '\0'; i++) {
            if (isdigit(line[i])) {
                total_digit_count++;
            }
        }
    }
    
    printf("Общее количество цифр в файле: %ld\n", total_digit_count);
    
    return 0;
}
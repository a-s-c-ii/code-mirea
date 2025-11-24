#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1024

int count_words(const char *str) {
    int count = 0;
    int in_word = 0; 

    while (*str) {
        if (isalnum(*str)) { 
            if (!in_word) {
                in_word = 1;
                count++;
            }
        } else {
            in_word = 0;
        }
        str++;
    }
    return count;
}

int main() {
    char line[MAX_LINE_LENGTH];
    
    while (fgets(line, MAX_LINE_LENGTH, stdin) != NULL) {
        int word_count = count_words(line);
        
        line[strcspn(line, "\n")] = 0; 
        
        printf("%s (Слов: %d)\n", line, word_count);
    }
    
    return 0;
}
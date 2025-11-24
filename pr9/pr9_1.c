#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024 
#define PREFIX "03.05.2024" 
#define PREFIX_LEN 10 

int main() {
    char line[MAX_LINE_LENGTH];
    
    while (fgets(line, MAX_LINE_LENGTH, stdin) != NULL) {
        if (strncmp(line, PREFIX, PREFIX_LEN) == 0) {
            fputs(line, stdout);
        }
    }
    
    return 0;
}
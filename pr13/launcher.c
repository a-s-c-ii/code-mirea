#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    printf("[Launcher] Запуск основного процесса...\n");

    pid_t pid = fork(); 

    if (pid < 0) {
        perror("Ошибка fork");
        return 1;
    }

    if (pid == 0) {
        char *args[] = {"./worker", "test.txt", NULL};
        execvp(args[0], args);

        perror("Ошибка exec");
        exit(1);
    } else {
        int status;
        waitpid(pid, &status, 0); 

        if (WIFEXITED(status)) {
            printf("[Launcher] Основной процесс завершился успешно с кодом %d.\n", WEXITSTATUS(status));
        } else {
            printf("[Launcher] Процесс завершился с ошибкой.\n");
        }
    }

    return 0;
}
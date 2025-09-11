
#include <stdio.h>

void task1() {
    printf("Числа от 1 до 10: ");
    for (int i = 1; i <= 10; i++) {
        printf("%d ", i);
    }
    printf("\n");
}

void task2() {
    int n = 5;
    printf("Таблица умножения для %d:\n", n);
    for (int i = 1; i <= 10; i++) {
        printf("%d * %d = %d\n", n, i, n * i);
    }
}

void task3() {
    int sum = 0;
    for (int i = 1; i <= 100; i++) {
        sum += i;
    }
    printf("Сумма чисел от 1 до 100: %d\n", sum);
}

void task4() {
    printf("Числа от 1 до 100, кратные 3 или 5:\n");
    for (int i = 1; i <= 100; i++) {
        if (i % 3 == 0 || i % 5 == 0) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

void task5() {
    int num;
    printf("Введите число: ");
    scanf("%d", &num);

    printf("Делители числа %d: ", num);
    for (int i = 1; i <= num; i++) {
        if (num % i == 0) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int main() {
    int choice;

    while (1) {
        printf("1. Вывести числа от 1 до 10\n");
        printf("2. Таблица умножения для 5\n");
        printf("3. Сумма чисел от 1 до 100\n");
        printf("4. Числа, кратные 3 или 5 (до 100)\n");
        printf("5. Найти все делители числа\n");
        printf("0. Выход\n");
        printf("Выберите задачу (0-5): ");

        scanf("%d", &choice);

        if (choice == 0) {
            printf("Выход из программы.\n");
            break;
        }

        switch (choice) {
            case 1: task1(); break;
            case 2: task2(); break;
            case 3: task3(); break;
            case 4: task4(); break;
            case 5: task5(); break;
            default:
                printf("Неверный номер задачи. Попробуйте снова.\n");
        }
    }

    return 0;
}
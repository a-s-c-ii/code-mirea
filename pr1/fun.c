
#include <stdio.h>

void task1() {
    int n, i;
    long long fact = 1;

    printf("Введите число для вычисления факториала: ");
    scanf("%d", &n);

    if (n < 0) {
        printf("Факториал отрицательного числа не определён.\n");
        return;
    }

    for (i = 1; i <= n; i++) {
        fact *= i;
    }

    printf("Факториал %d = %lld\n", n, fact);
}

void task2() {
    int n, i;

    printf("Введите число для проверки на простоту: ");
    scanf("%d", &n);

    if (n < 2) {
        printf("%d не является простым числом.\n", n);
        return;
    }

    for (i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            printf("%d не является простым числом.\n", n);
            return;
        }
    }

    printf("%d является простым числом.\n", n);
}

void task3() {
    int n, i;

    printf("Введите число для поиска делителей: ");
    scanf("%d", &n);

    if (n == 0) {
        printf("У нуля бесконечно много делителей.\n");
        return;
    }

    printf("Делители числа %d: ", n);

    if (n < 0) n = -n;

    for (i = 1; i <= n; i++) {
        if (n % i == 0) {
            printf("%d ", i);
        }
    }

    printf("\n");
}

void task4() {
    int a, b, i;

    printf("Введите два числа: ");
    scanf("%d %d", &a, &b);

    printf("Числа между %d и %d: ", a, b);

    if (a <= b) {
        for (i = a + 1; i < b; i++) {
            printf("%d ", i);
        }
    } else {
        for (i = a - 1; i > b; i--) {
            printf("%d ", i);
        }
    }

    printf("\n");
}

void task5() {
    int a, b, sumA = 0, sumB = 0, i;

    printf("Введите два числа для проверки на дружественность: ");
    scanf("%d %d", &a, &b);

    for (i = 1; i < a; i++) {
        if (a % i == 0) {
            sumA += i;
        }
    }

    for (i = 1; i < b; i++) {
        if (b % i == 0) {
            sumB += i;
        }
    }

    if (sumA == b && sumB == a) {
        printf("%d и %d — дружественные числа!\n", a, b);
    } else {
        printf("%d и %d — не дружественные числа.\n", a, b);
    }
}

int main() {
    int choice;

    while (1) {
        printf("1. Вычислить факториал\n");
        printf("2. Проверить на простоту\n");
        printf("3. Найти все делители\n");
        printf("4. Вывести числа между двумя числами\n");
        printf("5. Проверить дружественность\n");
        printf("0. Выход\n");
        printf("Выберите задачу: ");
        scanf("%d", &choice);

        if (choice == 0) break;

        switch (choice) {
            case 1: task1(); break;
            case 2: task2(); break;
            case 3: task3(); break;
            case 4: task4(); break;
            case 5: task5(); break;
            default: printf("Неверный выбор.\n");
        }
    }

    return 0;
}
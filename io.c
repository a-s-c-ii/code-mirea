#include <stdio.h>

void task1() {
    int num;
    printf("Введите число: ");
    scanf("%d", &num);
    printf("Вы ввели: %d\n", num);
}

void task2() {
    double a, b;
    printf("Введите первое число: ");
    scanf("%lf", &a);
    printf("Введите второе число: ");
    scanf("%lf", &b);

    printf("Сумма: %.2lf\n", a + b);
    printf("Разность: %.2lf\n", a - b);
    printf("Произведение: %.2lf\n", a * b);
    if (b != 0) {
        printf("Частное: %.2lf\n", a / b);
    } else {
        printf("Частное: деление на ноль невозможно!\n");
    }
}

void task3() {
    double a, b, c;
    printf("Введите первое число: ");
    scanf("%lf", &a);
    printf("Введите второе число: ");
    scanf("%lf", &b);
    printf("Введите третье число: ");
    scanf("%lf", &c);

    double avg = (a + b + c) / 3.0;
    printf("Среднее арифметическое: %.2lf\n", avg);
}

void task4() {
    char name[15];
    printf("Введите ваше имя: ");
    scanf("%s", name);
    printf("Привет, %s!\n", name);
}

void task5() {
    int birth_year;
    const int current_year = 2025;
    printf("Введите год рождения: ");
    scanf("%d", &birth_year);
    int age = current_year - birth_year;
    printf("Ваш возраст: %d лет\n", age);
}

void task6() {
    int num;
    printf("Введите число: ");
    scanf("%d", &num);
    if (num % 2 == 0) {
        printf("Число чётное\n");
    } else {
        printf("Число нечётное\n");
    }
}

void task7() {
    int num;
    printf("Введите число: ");
    scanf("%d", &num);
    if (num > 0) {
        printf("Число положительное\n");
    } else if (num < 0) {
        printf("Число отрицательное\n");
    } else {
        printf("Число равно нулю\n");
    }
}

void task8() {
    int num;
    printf("Введите число: ");
    scanf("%d", &num);
    if (num % 3 == 0) {
        printf("Число кратно 3\n");
    } else {
        printf("Число не кратно 3\n");
    }
}

void task9() {
    double a, b;
    printf("Введите первое число: ");
    scanf("%lf", &a);
    printf("Введите второе число: ");
    scanf("%lf", &b);

    if (a > b) {
        printf("Большее число: %.2lf\n", a);
    } else if (b > a) {
        printf("Большее число: %.2lf\n", b);
    } else {
        printf("Числа равны\n");
    }
}

void task10() {
    double a, b;
    printf("Введите первое число: ");
    scanf("%lf", &a);
    printf("Введите второе число: ");
    scanf("%lf", &b);

    if (a == b) {
        printf("Числа равны\n");
    } else {
        printf("Числа не равны\n");
    }
}

int main() {
    int choice;

    while (1) {
        printf("1. Вывести введённое число\n");
        printf("2. Арифметические операции с двумя числами\n");
        printf("3. Среднее арифметическое трёх чисел\n");
        printf("4. Приветствие по имени\n");
        printf("5. Вычислить возраст\n");
        printf("6. Проверить чётность\n");
        printf("7. Определить знак числа\n");
        printf("8. Проверить кратность 3\n");
        printf("9. Найти большее из двух чисел\n");
        printf("10. Проверить равенство двух чисел\n");
        printf("0. Выход\n");
        printf("Выберите задачу (0-10): ");
        
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
            case 6: task6(); break;
            case 7: task7(); break;
            case 8: task8(); break;
            case 9: task9(); break;
            case 10: task10(); break;
            default:
                printf("Неверный номер задачи. Попробуйте снова.\n");
        }
    }

    return 0;
}
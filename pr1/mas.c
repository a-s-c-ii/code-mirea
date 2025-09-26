
#include <stdio.h>
#include <stdlib.h> 
#include <time.h>   

void task1() {
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    printf("Элементы массива: ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void task2() {
    int arr[10];
    printf("Случайные числа: ");
    for (int i = 0; i < 10; i++) {
        arr[i] = rand() % 100; 
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void task3() {
    int arr[10];

    printf("Введите 10 чисел:\n");
    for (int i = 0; i < 10; i++) {
        printf("Число %d: ", i + 1);
        scanf("%d", &arr[i]);
    }

    printf("Вы ввели: ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void task4() {
    int arr[10] = {5, 10, 15, 20, 25, 30, 35, 40, 45, 50};
    int sum = 0;

    for (int i = 0; i < 10; i++) {
        sum += arr[i];
    }

    printf("Сумма элементов массива: %d\n", sum);
}

void task5() {
    int arr1[10], arr2[10];
    int result = 0;

    printf("Введите 10 чисел для первого массива:\n");
    for (int i = 0; i < 10; i++) {
        printf("Число %d: ", i + 1);
        scanf("%d", &arr1[i]);
    }

    printf("Введите 10 чисел для второго массива:\n");
    for (int i = 0; i < 10; i++) {
        printf("Число %d: ", i + 1);
        scanf("%d", &arr2[i]);
    }

    for (int i = 0; i < 10; i++) {
        result += arr1[i] + arr2[i];
    }

    printf("Общая сумма всех элементов двух массивов: %d\n", result);
}

int main() {
    int choice;

    srand(time(NULL));

    while (1) {
        printf("1. Вывести заранее заданный массив\n");
        printf("2. Заполнить массив случайными числами\n");
        printf("3. Ввести 10 чисел с клавиатуры\n");
        printf("4. Сумма элементов фиксированного массива\n");
        printf("5. Сумма двух введённых массивов\n");
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
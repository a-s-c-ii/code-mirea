#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int row_index;
    int cols;
    int **A;
    int **B;
    int **C;
} ThreadData;

void* add_rows(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    
    for (int j = 0; j < data->cols; j++) {
        data->C[data->row_index][j] = data->A[data->row_index][j] + data->B[data->row_index][j];
    }

    pthread_exit(NULL);
}

int main() {
    int rows = 3;
    int cols = 3;

    int **matrixA = malloc(rows * sizeof(int*));
    int **matrixB = malloc(rows * sizeof(int*));
    int **matrixC = malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrixA[i] = malloc(cols * sizeof(int));
        matrixB[i] = malloc(cols * sizeof(int));
        matrixC[i] = malloc(cols * sizeof(int));
    }

    printf("Matrix A + Matrix B:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrixA[i][j] = i + j;
            matrixB[i][j] = (i + j) * 2;
            printf("%d ", matrixA[i][j]);
        }
        printf("\n");
    }

    pthread_t threads[rows];
    ThreadData thread_data[rows];

    for (int i = 0; i < rows; i++) {
        thread_data[i].row_index = i;
        thread_data[i].cols = cols;
        thread_data[i].A = matrixA;
        thread_data[i].B = matrixB;
        thread_data[i].C = matrixC;

        if (pthread_create(&threads[i], NULL, add_rows, &thread_data[i]) != 0) {
            perror("Fail create thread");
            return 1;
        }
    }

    for (int i = 0; i < rows; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\nMatrix C:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrixC[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < rows; i++) {
        free(matrixA[i]); free(matrixB[i]); free(matrixC[i]);
    }
    free(matrixA); free(matrixB); free(matrixC);

    return 0;
}
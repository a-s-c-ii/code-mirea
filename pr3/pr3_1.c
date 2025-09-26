#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char title[100];
    char author[50];
    int year;
} Book;

typedef struct DynamicBook {
    Book* book;  
    struct DynamicBook* next;
} DynamicBook;

DynamicBook* createDynamicBook(const char* title, const char* author, int year) {
    DynamicBook* db = (DynamicBook*)malloc(sizeof(DynamicBook));
    if (!db) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        exit(1);
    }

    db->book = (Book*)malloc(sizeof(Book));
    if (!db->book) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        free(db);
        exit(1);
    }

    strcpy(db->book->title, title);
    strcpy(db->book->author, author);
    db->book->year = year;
    db->next = NULL;

    return db;
}

void printBooksThroughFirst(DynamicBook* first) {
    printf("\nВывод информации через первую структуру\n");
    DynamicBook* current = first;
    int i = 1;
    while (current != NULL) {
        printf("Книга %d:\n", i++);
        printf("  Название: %s\n", current->book->title);
        printf("  Автор: %s\n", current->book->author);
        printf("  Год: %d\n", current->book->year);
        printf("\n");
        current = current->next;
    }
}

void freeDynamicBooks(DynamicBook* first) {
    DynamicBook* current = first;
    while (current != NULL) {
        DynamicBook* next = current->next;
        free(current->book);
        free(current);
        current = next;
    }
}

int main() {
    printf("\n");

    DynamicBook* book1 = createDynamicBook("1111", "kniga1", 2222);
    DynamicBook* book2 = createDynamicBook("3333", "kniga2", 9999);

    book1->next = book2;

    printBooksThroughFirst(book1);

    freeDynamicBooks(book1);

    printf("\nЗадача 1 все.\n");
    return 0;
}
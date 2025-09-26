#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

struct Node* head = NULL;
struct Node* tail = NULL;

struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Ошибка выделения памяти!\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void addElement(int value) {
    struct Node* newNode = createNode(value);

    if (head == NULL) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    printf("Элемент %d добавлен в список.\n", value);
}

void deleteFromBeginning() {
    if (head == NULL) {
        printf("Список пуст, удалять нечего.\n");
        return;
    }

    struct Node* temp = head;

    if (head == tail) {
        head = tail = NULL;
    } else {
        head = head->next;
        head->prev = NULL;
    }

    printf("Удалён элемент %d из начала.\n", temp->data);
    free(temp);
}

void deleteFromMiddle() {
    if (head == NULL || head->next == NULL || head->next->next == NULL) {
        printf("Недостаточно элементов для удаления из середины.\n");
        return;
    }

    struct Node* middle = head->next;

    middle->prev->next = middle->next;
    middle->next->prev = middle->prev;

    printf("Удалён элемент %d из середины.\n", middle->data);
    free(middle);
}

void printForward() {
    if (head == NULL) {
        printf("Список пуст.\n");
        return;
    }

    printf("Список (начало -> конец): ");
    struct Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void printBackward() {
    if (tail == NULL) {
        printf("Список пуст.\n");
        return;
    }

    printf("Список (конец -> начало): ");
    struct Node* current = tail;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->prev;
    }
    printf("\n");
}

int main() {
    printf("список\n");

    addElement(10);
    addElement(20);
    addElement(30);
    addElement(40);
    addElement(50);

    printForward();   
    printBackward();  

    deleteFromBeginning(); 
    printForward();

    deleteFromMiddle();
    printForward();

    deleteFromBeginning(); 
    printForward();        

    deleteFromMiddle();    

    deleteFromBeginning(); 
    deleteFromBeginning(); 
    deleteFromBeginning(); 

    printForward();        

    return 0;
}
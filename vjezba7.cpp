#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_PRIORITY 15
#define MIN 10
#define MAX 100

struct node;
typedef struct node* Position;

typedef struct node {
    int element;
    int priority;
    Position next;
} Node;

int PushCircularStack(Position, int, int*, int);
int PopCircularStack(Position, int*);
int PushPriorityQueue(Position, int, int);
int PopPriorityQueue(Position);
int Print(Position);
int DeleteAll(Position);
int GetRandom();

int main() {
    struct node headStack;
    struct node headQueue;
    int maxStackSize = 0, stackSize = 0;
    int result = 0, choice = 0;

    headStack.next = &headStack;  // Circular stack initialization
    headQueue.next = NULL;       // Priority queue initialization

    srand((unsigned)time(NULL)); // Initialize random seed

    printf("Unesite maksimalnu velicinu stoga: ");
    scanf("%d", &maxStackSize);

    do {
        printf("\nOdaberite opciju:\n");
        printf("1. Push na cirkularni stog\n");
        printf("2. Pop iz cirkularnog stoga\n");
        printf("3. Ispis cirkularnog stoga\n");
        printf("4. Push na red s prioritetom\n");
        printf("5. Pop iz reda s prioritetom\n");
        printf("6. Ispis reda s prioritetom\n");
        printf("7. Izlaz\n");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            result = PushCircularStack(&headStack, GetRandom(), &stackSize, maxStackSize);
            if (result == -1) printf("Stog je pun!\n");
            else printf("Element dodan u stog.\n");
            break;
        case 2:
            result = PopCircularStack(&headStack, &stackSize);
            if (result == -1) printf("Stog je prazan!\n");
            break;
        case 3:
            printf("Cirkularni stog: ");
            Print(headStack.next);
            break;
        case 4:
            result = PushPriorityQueue(&headQueue, GetRandom(), rand() % MAX_PRIORITY + 1);
            if (result == -1) printf("Greska pri dodavanju u red!\n");
            else printf("Element dodan u red.\n");
            break;
        case 5:
            result = PopPriorityQueue(&headQueue);
            if (result == -1) printf("Red je prazan!\n");
            break;
        case 6:
            printf("Red s prioritetom: ");
            Print(headQueue.next);
            break;
        case 7:
            printf("Izlaz iz programa.\n");
            break;
        default:
            printf("Pogresan unos, pokusajte ponovo.\n");
        }

    } while (choice != 7);

    DeleteAll(&headStack);
    DeleteAll(&headQueue);

    return 0;
}

int GetRandom() {
    return rand() % (MAX - MIN + 1) + MIN;
}

int PushCircularStack(Position P, int value, int* stackSize, int maxStackSize) {
    if (*stackSize >= maxStackSize) return -1; // Stack is full

    Position temp = (Position)malloc(sizeof(Node));
    if (!temp) {
        printf("Alokacija nije uspijela!\n");
        return -1;
    }

    temp->element = value;
    temp->next = P->next;
    P->next = temp;
    (*stackSize)++;

    return 0;
}

int PopCircularStack(Position P, int* stackSize) {
    if (*stackSize == 0) return -1; // Stack is empty

    Position temp = P->next;
    P->next = temp->next;
    printf("Izbacen element: %d\n", temp->element);
    free(temp);
    (*stackSize)--;

    return 0;
}

int PushPriorityQueue(Position P, int value, int priority) {
    Position temp = (Position)malloc(sizeof(Node));
    if (!temp) {
        printf("Alokacija nije uspijela!\n");
        return -1;
    }

    temp->element = value;
    temp->priority = priority;

    while (P->next != NULL && P->next->priority >= priority) {
        P = P->next;
    }

    temp->next = P->next;
    P->next = temp;

    return 0;
}

int PopPriorityQueue(Position P) {
    if (!P->next) return -1; // Queue is empty

    Position temp = P->next;
    P->next = temp->next;
    printf("Izbacen element: %d (prioritet: %d)\n", temp->element, temp->priority);
    free(temp);

    return 0;
}

int Print(Position P) {
    if (P == NULL) {
        printf("Prazna lista\n");
        return 0;
    }

    while (P != NULL) {
        printf("%d ", P->element);
        if (P->priority) {
            printf("(prioritet: %d) ", P->priority);
        }
        P = P->next;
    }

    printf("\n");
    return 0;
}

int DeleteAll(Position P) {
    Position temp;
    while (P->next) {
        temp = P->next;
        P->next = temp->next;
        free(temp);
    }
    return 0;
}
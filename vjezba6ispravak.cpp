#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define OK             0
#define ERR_ALLOC      1
#define ERR_EMPTY      2
#define ERR_INPUT      3

typedef struct Cvor {
    int elem;
    struct Cvor* next;
} Cvor;

int Push(Cvor** head) {
    int broj = rand() % 91 + 10;

    Cvor* novi = (Cvor*)malloc(sizeof(Cvor));
    if (novi == NULL) {
        printf("Greska u alokaciji\n");
        return ERR_ALLOC;
    }

    novi->elem = broj;
    novi->next = *head;
    *head = novi;

    printf("Dodan %d\n", broj);
    return OK;
}

int Pop(Cvor** head, int* outBroj) {
    if (*head == NULL) {
        printf("Stog je prazan\n");
        return ERR_EMPTY;
    }

    Cvor* temp = *head;
    *outBroj = temp->elem;
    *head = (*head)->next;
    free(temp);

    printf("Uklonjen %d\n", *outBroj);
    return OK;
}

int IspisStog(Cvor* head) {
    if (head == NULL) {
        printf("Stog prazan\n");
        return ERR_EMPTY;
    }

    printf("Stog: ");
    while (head) {
        printf("%d ", head->elem);
        head = head->next;
    }
    printf("\n");
    return OK;
}

int Enqueue(Cvor** head, Cvor** tail) {
    int broj = rand() % 91 + 10;

    Cvor* novi = (Cvor*)malloc(sizeof(Cvor));
    if (novi == NULL) {
        printf("Greska u alokaciji\n");
        return ERR_ALLOC;
    }

    novi->elem = broj;
    novi->next = NULL;

    if (*tail == NULL) {
        *head = novi;
        *tail = novi;
    }
    else {
        (*tail)->next = novi;
        *tail = novi;
    }

    printf("Dodan %d\n", broj);
    return OK;
}

int Dequeue(Cvor** head, Cvor** tail, int* outBroj) {
    if (*head == NULL) {
        printf("Red prazan\n");
        return ERR_EMPTY;
    }

    Cvor* temp = *head;
    *outBroj = temp->elem;
    *head = (*head)->next;

    if (*head == NULL) {
        *tail = NULL;
    }

    free(temp);

    printf("Uklonjen %d\n", *outBroj);
    return OK;
}

int IspisRed(Cvor* head) {
    if (head == NULL) {
        printf("Red prazan\n");
        return ERR_EMPTY;
    }

    printf("Red: ");
    while (head) {
        printf("%d ", head->elem);
        head = head->next;
    }
    printf("\n");
    return OK;
}

void freeMem(Cvor* head) {
    while (head) {
        Cvor* next = head->next;
        free(head);
        head = next;
    }
}

void MeniStog(void) {
    printf("1 push\n");
    printf("2 pop\n");
    printf("3 ispis\n");
    printf("0 povratak\n");
    printf("Izaberi: ");
}

void MeniRed(void) {
    printf("1 enqueue\n");
    printf("2 dequeue\n");
    printf("3 ispis\n");
    printf("0 povratak\n");
    printf("Izaberi: ");
}

int simStog(Cvor** stog) {
    int izbor = 0;
    int x = 0;

    printf("\nSimulacija stoga\n");

    do {
        MeniStog();
        if (scanf("%d", &izbor) != 1) {
            printf("Krivi unos\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }

        switch (izbor) {
        case 1: {
            int st = Push(stog);
            if (st != OK) {
                freeMem(*stog);
                *stog = NULL;
                return st;
            }
            break;
        }
        case 2:
            Pop(stog, &x);
            break;
        case 3:
            IspisStog(*stog);
            break;
        case 0:
            printf("Povratak\n");
            break;
        default:
            printf("Neispravan izbor\n");
        }
    } while (izbor != 0);

    return OK;
}

int simRed(Cvor** head, Cvor** tail) {
    int izbor = 0;
    int x = 0;

    printf("\nSimulacija reda\n");

    do {
        MeniRed();
        if (scanf("%d", &izbor) != 1) {
            printf("Krivi unos\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }

        switch (izbor) {
        case 1:
        {
            int st = Enqueue(head, tail);
            if (st != OK) {
                freeMem(*head);
                *head = NULL;
                *tail = NULL;
                return st;
            }
            break;
        }
        case 2:
            Dequeue(head, tail, &x);
            break;
        case 3:
            IspisRed(*head);
            break;
        case 0:
            printf("Povratak\n");
            break;
        default:
            printf("Neispravan izbor\n");
        }
    } while (izbor != 0);

    return OK;
}

int main(void) {
    srand((unsigned)time(NULL));

    Cvor* stog = NULL;
    Cvor* redHead = NULL;
    Cvor* redTail = NULL;

    int izbor = 0;
    int st = 0;

    do {
        printf("\n1 Simulacija stoga\n");
        printf("2 Simulacija reda\n");
        printf("0 Izlaz\n");
        printf("Izaberi: ");

        if (scanf("%d", &izbor) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }

        switch (izbor) {
        case 1:
            st = simStog(&stog);
            if (st != OK) {
                freeMem(stog);
                freeMem(redHead);
                return st;
            }
            break;
        case 2:
            st = simRed(&redHead, &redTail);
            if (st != OK) {
                freeMem(stog);
                freeMem(redHead);
                return st;
            }
            break;
        case 0:
            printf("Izlaz\n");
            break;
        default:
            printf("Neispravan izbor\n");
            break;
        }
    } while (izbor != 0);

    freeMem(stog);
    freeMem(redHead);

    return 0;
}

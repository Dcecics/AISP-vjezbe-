#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define OK             0
#define ERR_ALLOC      1
#define ERR_EMPTY      2
#define ERR_INPUT      3
#define ERR_FULL       4

typedef struct Stog {
    int elem;
    struct Stog* next;
} Stog;

typedef struct Red {
    int elem;
    int prioritet;
    struct Red* next;
} Red;

int velicinaStoga(Stog* head) {
    if (head == NULL) return 0;

    int brojac = 1;
    Stog* temp = head;
    while (temp->next != head) {
        brojac++;
        temp = temp->next;
    }
    return brojac;
}

int Push(Stog** head, int maxVelicina, int* outDodani, int* outObrisani, int* obrisanoFlag) {
    *obrisanoFlag = 0;
    if (maxVelicina <= 0) return ERR_INPUT;

    int slucBr = rand() % 91 + 10;

    Stog* novi = (Stog*)malloc(sizeof(Stog));
    if (novi == NULL) return ERR_ALLOC;

    novi->elem = slucBr;

    if (*head == NULL) {
        novi->next = novi;
        *head = novi;
        if (outDodani) *outDodani = slucBr;
        return OK;
    }

    int trenutnaVelicina = velicinaStoga(*head);

    if (trenutnaVelicina >= maxVelicina) {
        Stog* temp = *head;
        Stog* prev = NULL;

        while (temp->next != *head) {
            prev = temp;
            temp = temp->next;
        }

        if (outObrisani) *outObrisani = temp->elem;
        *obrisanoFlag = 1;

        if (temp == *head) {
            free(temp);
            novi->next = novi;
            *head = novi;
        }
        else {
            //izbaci zadnji ubaci novi ka heaad
            prev->next = *head;      //predzadnji sad pokazuje na head
            novi->next = *head;

            //zadnji pokazuje na novi
            prev->next = novi;

            //oslobadan stari zadnji
            free(temp);
            *head = novi;
        }
    }
    else {
        //novi postaje head zadnji pokazuje na novog
        Stog* zadnji = *head;
        while (zadnji->next != *head) {
            zadnji = zadnji->next;
        }
        novi->next = *head;
        zadnji->next = novi;
        *head = novi;
    }

    if (outDodani) *outDodani = slucBr;
    return OK;
}

int Pop(Stog** head, int* outVrijednost) {
    if (*head == NULL) return ERR_EMPTY;

    Stog* temp = *head;
    int vrijednost = temp->elem;

    if (temp->next == temp) {
        free(temp);
        *head = NULL;
        if (outVrijednost) *outVrijednost = vrijednost;
        return OK;
    }

    Stog* zadnji = *head;
    while (zadnji->next != *head) {
        zadnji = zadnji->next;
    }

    *head = temp->next;
    zadnji->next = *head;
    free(temp);

    if (outVrijednost) *outVrijednost = vrijednost;
    return OK;
}

int ispisStoga(Stog* head) {
    if (head == NULL) {
        printf("Stog je prazan\n");
        return ERR_EMPTY;
    }

    printf("Stog: ");
    Stog* temp = head;
    do {
        printf("%d ", temp->elem);
        temp = temp->next;
    } while (temp != head);
    printf("\n");
    return OK;
}

void obrisiStog(Stog* head) {
    if (head == NULL) return;

    Stog* temp = head->next;
    while (temp != head) {
        Stog* next = temp->next;
        free(temp);
        temp = next;
    }
    free(head);
}

int Enqueue(Red** head, int* outElem, int* outPrioritet) {
    int slucBr = rand() % 91 + 10;
    int slucPrioritet = rand() % 5 + 1;

    Red* novi = (Red*)malloc(sizeof(Red));
    if (novi == NULL) return ERR_ALLOC;

    novi->elem = slucBr;
    novi->prioritet = slucPrioritet;
    novi->next = NULL;

    if (*head == NULL || (*head)->prioritet < slucPrioritet) {
        novi->next = *head;
        *head = novi;
    }
    else {
        Red* temp = *head;
        while (temp->next != NULL && temp->next->prioritet >= slucPrioritet) {
            temp = temp->next;
        }
        novi->next = temp->next;
        temp->next = novi;
    }

    if (outElem) *outElem = slucBr;
    if (outPrioritet) *outPrioritet = slucPrioritet;
    return OK;
}

int Dequeue(Red** head, int* outElem, int* outPrioritet) {
    if (*head == NULL) return ERR_EMPTY;

    Red* temp = *head;
    *head = temp->next;

    if (outElem) *outElem = temp->elem;
    if (outPrioritet) *outPrioritet = temp->prioritet;

    free(temp);
    return OK;
}

int ispisReda(Red* head) {
    if (head == NULL) {
        printf("Red prazan\n");
        return ERR_EMPTY;
    }

    printf("Red: ");
    while (head) {
        printf("%d(P:%d) ", head->elem, head->prioritet);
        head = head->next;
    }
    printf("\n");
    return OK;
}

void obrisiRed(Red* head) {
    while (head) {
        Red* next = head->next;
        free(head);
        head = next;
    }
}

int main(void) {
    srand((unsigned)time(NULL));

    Stog* stog = NULL;
    Red* red = NULL;

    int unos = 0;
    int maxVelicina = 0;

    printf("Unesite max vel cirk stoga: ");
    if (scanf("%d", &maxVelicina) != 1) {
        printf("Krivi unos\n");
        return ERR_INPUT;
    }
    if (maxVelicina <= 0) {
        printf("Mora bit veca od 0\n");
        return ERR_INPUT;
    }

    do {
        printf("\nCIRKULARNI STOG:\n");
        printf("1 - PUSH\n");
        printf("2 - POP\n");
        printf("3 - Ispis stoga\n");
        printf("RED S PRIORITETOM:\n");
        printf("4 - ENQUEUE\n");
        printf("5 - DEQUEUE\n");
        printf("6 - Ispis reda\n");
        printf("0 - Izlaz\n");
        printf("Izbor: ");

        if (scanf("%d", &unos) != 1) {
            printf("Krivi unos\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }

        int st = OK;

        switch (unos) {
        case 0:
            printf("Izlaz\n");
            break;

        case 1: {
            int dodan = 0, obrisan = 0, obrisano = 0;
            st = Push(&stog, maxVelicina, &dodan, &obrisan, &obrisano);
            if (st == OK) {
                printf("PUSH: %d\n", dodan);
                if (obrisano) printf("Obrisan najstariji: %d\n", obrisan);
            }
            else if (st == ERR_ALLOC) {
                printf("Greska u alokaciji memorije\n");
                obrisiStog(stog);
                obrisiRed(red);
                return ERR_ALLOC;
            }
            break;
        }
        case 2: {
            int x = 0;
            st = Pop(&stog, &x);
            if (st == OK) printf("POP: %d\n", x);
            else printf("Stog prazan\n");
            break;
        }

        case 3:
            ispisStoga(stog);
            break;

        case 4: {
            int e = 0, p = 0;
            st = Enqueue(&red, &e, &p);
            if (st == OK) printf("ENQUEUE: %d (P:%d)\n", e, p);
            else if (st == ERR_ALLOC) {
                printf("Greska u alokaciji memorije\n");
                obrisiStog(stog);
                obrisiRed(red);
                return ERR_ALLOC;
            }
            break;
        }

        case 5: { 
            int e = 0, p = 0;
            st = Dequeue(&red, &e, &p);
            if (st == OK) printf("DEQUEUE: %d (P:%d)\n", e, p);
            else printf("Red je prazan\n");
            break;
        }

        case 6:
            ispisReda(red);
            break;

        default:
            printf("NE MOZE\n");
            break;
        }

    } while (unos != 0);

    obrisiStog(stog);
    obrisiRed(red);
    return 0;
}

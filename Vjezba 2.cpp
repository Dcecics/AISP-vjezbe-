#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK             0
#define ERR_ALLOC      1
#define ERR_INPUT      2
#define ERR_EMPTY      3
#define ERR_NOT_FOUND  4

typedef struct _osoba {
    char ime[50];
    char prez[50];
    int god_rod;
    struct _osoba* next;
} Osoba;

int novaOsoba(Osoba** outNova) {
    Osoba* nova = (Osoba*)malloc(sizeof(Osoba));
    if (!nova) {
        printf("GRESKA u alokaciji\n");
        *outNova = NULL;
        return ERR_ALLOC;
    }

    printf("Unesi ime: ");
    if (scanf("%49s", nova->ime) != 1) {
        free(nova);
        *outNova = NULL;
        return ERR_INPUT;
    }

    printf("Unesi prezime: ");
    if (scanf("%49s", nova->prez) != 1) {
        free(nova);
        *outNova = NULL;
        return ERR_INPUT;
    }

    printf("Unesi godinu rodenja: ");
    if (scanf("%d", &nova->god_rod) != 1) {
        free(nova);
        *outNova = NULL;
        return ERR_INPUT;
    }

    nova->next = NULL;
    *outNova = nova;
    return OK;
}

int dodajNaPoc(Osoba** head) {
    Osoba* nova = NULL;
    int st = novaOsoba(&nova);
    if (st != OK) return st;

    nova->next = *head;
    *head = nova;
    return OK;
}

int ispis(Osoba* head) {
    if (!head) {
        printf("Prazna lista\n");
        return ERR_EMPTY;
    }

    Osoba* temp = head;
    while (temp) {
        printf("%s %s %d\n", temp->ime, temp->prez, temp->god_rod);
        temp = temp->next;
    }
    return OK;
}

int dodajNaKraj(Osoba** head) {
    Osoba* nova = NULL;
    int st = novaOsoba(&nova);
    if (st != OK) return st;

    if (!(*head)) {
        *head = nova;
        return OK;
    }

    Osoba* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = nova;
    return OK;
}

int trazi(Osoba* head, const char* prezime, Osoba** found) {
    *found = NULL;

    Osoba* temp = head;
    while (temp) {
        if (strcmp(temp->prez, prezime) == 0) {
            *found = temp;
            return OK;
        }
        temp = temp->next;
    }
    return ERR_NOT_FOUND;
}

int brisi(Osoba** head, const char* prezime) {
    if (!(*head)) return ERR_EMPTY;

    Osoba* temp = *head;
    Osoba* prev = NULL;

    while (temp) {
        if (strcmp(temp->prez, prezime) == 0) {
            if (prev == NULL) *head = temp->next;
            else prev->next = temp->next;

            free(temp);
            return OK;
        }
        prev = temp;
        temp = temp->next;
    }
    return ERR_NOT_FOUND;
}

void freeListu(Osoba* head) {
    while (head) {
        Osoba* next = head->next;
        free(head);
        head = next;
    }
}

int main() {
    Osoba* head = NULL;
    int unos = 0;
    char prezime[50];
    Osoba* trazena = NULL;

    do {
        int st = OK;

        printf("\nIzaberi jedan broj:\n");
        printf("0 - izlaz, 1 - dodaj na pocetak, 2 - ispisi listu, 3 - dodaj na kraj, 4 - trazi po prezimenu, 5 - brisi po prezimenu\n");

        if (scanf("%d", &unos) != 1) {
            printf("Krivi unos opcije\n");
            freeListu(head);
            return ERR_INPUT;
        }

        switch (unos) {
        case 0:
            printf("Izlaz\n");
            break;

        case 1:
            st = dodajNaPoc(&head);
            if (st == OK) printf("Dodano na pocetak\n");
            break;

        case 2:
            st = ispis(head);
            break;

        case 3:
            st = dodajNaKraj(&head);
            if (st == OK) printf("Dodano na kraj\n");
            break;

        case 4:
            printf("Koga trazite? ");
            if (scanf("%49s", prezime) != 1) {
                printf("Krivi unos prezimena\n");
                freeListu(head);
                return ERR_INPUT;
            }
            st = trazi(head, prezime, &trazena);
            if (st == OK) {
                printf("Pronaden: %s %s %d\n", trazena->ime, trazena->prez, trazena->god_rod);
            }
            else {
                printf("Nije pronadena osoba s prezimenom %s\n", prezime);
            }
            break;

        case 5:
            printf("Koga brisete? ");
            if (scanf("%49s", prezime) != 1) {
                printf("Krivi unos prezimena\n");
                freeListu(head);
                return ERR_INPUT;
            }
            st = brisi(&head, prezime);
            if (st == OK) printf("Osoba %s obrisana\n", prezime);
            else if (st == ERR_NOT_FOUND) printf("Nije pronadena osoba s prezimenom %s\n", prezime);
            else if (st == ERR_EMPTY) printf("Lista je prazna\n");
            break;

        default:
            printf("NE MOZE!\n");
            break;
        }

        if (st != OK) {
            if (st == ERR_ALLOC) printf("Alokacija je pukla\n");
            else if (st == ERR_INPUT) printf("Krivi unos\n");
            else if (st == ERR_EMPTY) printf("Lista je prazna\n");
            else if (st == ERR_NOT_FOUND) printf("Nije pronadeno\n");
            else printf("Nepoznata greska\n");

            freeListu(head);
            return st;
        }

    } while (unos != 0);

    freeListu(head);
    return 0;
}

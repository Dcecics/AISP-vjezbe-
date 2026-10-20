#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK             0
#define ERR_ALLOC      1
#define ERR_INPUT      2
#define ERR_EMPTY      3
#define ERR_NOT_FOUND  4

typedef struct Osoba* Position;

typedef struct Osoba {
    char ime[50];
    char prez[50];
    int god_rod;
    Position next;
} Osoba;

int novaOsoba(Position* outNova);
int addBeginning(Position* head);
int addEnd(Position* head);
int ispis(Position head);
int trazi(Position head, const char* prezime, Position* found);
int brisi(Position* head, const char* prezime);
int ucitajIzDatoteke(Position* head);
void freeListu(Position head);

int main() {
    Position head = NULL;
    Position trazena = NULL;

    int unos = 0;
    int st = OK;
    int isRunning = 1;

    char prezime[50];

    st = ucitajIzDatoteke(&head);

    if (st != OK) {
        freeListu(head);
        return st;
    }

    do {
        st = OK;

        printf("\nIzaberi jedan broj:\n");
        printf("0 - izlaz\n");
        printf("1 - dodaj na pocetak\n");
        printf("2 - ispisi listu\n");
        printf("3 - dodaj na kraj\n");
        printf("4 - trazi po prezimenu\n");
        printf("5 - brisi po prezimenu\n");

        if (scanf("%d", &unos) != 1) {
            printf("Krivi unos opcije\n");
            freeListu(head);
            return ERR_INPUT;
        }

        switch (unos) {
        case 0:
            printf("Izlaz\n");
            isRunning = 0;
            break;

        case 1:
            st = addBeginning(&head);

            if (st == OK)
                printf("Dodano na pocetak\n");
            break;

        case 2:
            st = ispis(head);
            break;

        case 3:
            st = addEnd(&head);

            if (st == OK)
                printf("Dodano na kraj\n");
            break;

        case 4:
            printf("Koga trazite? ");

            if (scanf("%49s", prezime) != 1) {
                printf("Krivi unos prezimena\n");
                st = ERR_INPUT;
                break;
            }

            st = trazi(head, prezime, &trazena);

            if (st == OK) {
                printf("Pronaden: %s %s %d\n",
                    trazena->ime,
                    trazena->prez,
                    trazena->god_rod);
            }
            else if (st == ERR_NOT_FOUND) {
                printf("Nije pronadena osoba s prezimenom %s\n",
                    prezime);
                st = OK;
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

            if (st == OK)
                printf("Osoba %s obrisana\n", prezime);
            else if (st == ERR_NOT_FOUND) {
                printf("Nije pronadena osoba s prezimenom %s\n",
                    prezime);
                st = OK;
            }
            else if (st == ERR_EMPTY) {
                printf("Lista je prazna\n");
                st = OK;
            }
            break;

        default:
            printf("NE MOZE!\n");
            break;
        }

        if (st != OK) {
            if (st == ERR_ALLOC)
                printf("Alokacija je pukla\n");
            else if (st == ERR_INPUT)
                printf("Krivi unos\n");
            else if (st == ERR_EMPTY)
                printf("Lista je prazna\n");
            else if (st == ERR_NOT_FOUND)
                printf("Nije pronadeno\n");
            else
                printf("Nepoznata greska\n");

            if (st == ERR_ALLOC || st == ERR_INPUT) {
                freeListu(head);
                return st;
            }
        }

    } while (isRunning);

    freeListu(head);

    return 0;
}

int novaOsoba(Position* outNova) {
    Position nova = (Position)malloc(sizeof(Osoba));

    if (nova == NULL) {
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

int addBeginning(Position* head) {
    Position nova = NULL;

    int st = novaOsoba(&nova);
    if (st != OK)
        return st;

    nova->next = *head;
    *head = nova;

    return OK;
}

int addEnd(Position* head) {
    Position nova = NULL;

    int st = novaOsoba(&nova);
    if (st != OK)
        return st;

    if (*head == NULL) {
        *head = nova;
        return OK;
    }

    Position temp = *head;

    while (temp->next != NULL)
        temp = temp->next;

    temp->next = nova;

    return OK;
}

int ispis(Position head) {
    if (head == NULL) {
        printf("Prazna lista\n");
        return ERR_EMPTY;
    }

    Position temp = head;

    while (temp != NULL) {
        printf("%s %s %d\n",
            temp->ime, temp->prez, temp->god_rod);

        temp = temp->next;
    }

    return OK;
}

int trazi(Position head, const char* prezime, Position* found) {
    *found = NULL;

    Position temp = head;

    while (temp != NULL) {
        if (strcmp(temp->prez, prezime) == 0) {
            *found = temp;
            return OK;
        }

        temp = temp->next;
    }

    return ERR_NOT_FOUND;
}

int brisi(Position* head, const char* prezime) {
    if (*head == NULL)
        return ERR_EMPTY;

    Position temp = *head;
    Position prev = NULL;

    while (temp != NULL) {
        if (strcmp(temp->prez, prezime) == 0) {
            if (prev == NULL)
                *head = temp->next;
            else
                prev->next = temp->next;

            free(temp);
            return OK;
        }

        prev = temp;
        temp = temp->next;
    }

    return ERR_NOT_FOUND;
}

int ucitajIzDatoteke(Position* head) {
    FILE* dat = fopen("dat.txt", "r");

    if (dat == NULL) {
        printf("GRESKA: Datoteka dat.txt nije pronadena\n");
        return ERR_INPUT;
    }

    Position kraj = NULL;

    if (*head != NULL) {
        kraj = *head;

        while (kraj->next != NULL)
            kraj = kraj->next;
    }

    while (1) {
        Position nova = (Position)malloc(sizeof(Osoba));

        if (nova == NULL) {
            printf("GRESKA u alokaciji\n");
            fclose(dat);
            return ERR_ALLOC;
        }

        int rezultat = fscanf(dat, "%49s %49s %d",
            nova->ime,
            nova->prez,
            &nova->god_rod);

        if (rezultat == EOF) {
            free(nova);
            break;
        }

        if (rezultat != 3) {
            free(nova);
            printf("GRESKA pri citanju datoteke\n");
            fclose(dat);
            return ERR_INPUT;
        }

        nova->next = NULL;

        if (*head == NULL) {
            *head = nova;
            kraj = nova;
        }
        else {
            kraj->next = nova;
            kraj = nova;
        }
    }

    fclose(dat);
    return OK;
}

void freeListu(Position head) {
    while (head != NULL) {
        Position next = head->next;
        free(head);
        head = next;
    }
}

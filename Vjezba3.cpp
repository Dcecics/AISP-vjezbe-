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
#define ERR_FILE       5

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

int dodajNaKraj(Osoba** head) {
    Osoba* nova = NULL;
    int st = novaOsoba(&nova);
    if (st != OK) return st;

    if (!(*head)) {
        *head = nova;
        return OK;
    }

    Osoba* temp = *head;
    while (temp->next != NULL) temp = temp->next;
    temp->next = nova;
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

int dodajIzaOdredenog(Osoba** head, const char* prezime, Osoba** outNova) {
    *outNova = NULL;
    if (!(*head)) return ERR_EMPTY;

    Osoba* temp = *head;
    while (temp && strcmp(temp->prez, prezime) != 0) {
        temp = temp->next;
    }
    if (!temp) return ERR_NOT_FOUND;

    Osoba* nova = NULL;
    int st = novaOsoba(&nova);
    if (st != OK) return st;

    nova->next = temp->next;
    temp->next = nova;
    *outNova = nova;
    return OK;
}

int dodajIspredOdredenog(Osoba** head, const char* prezime, Osoba** outNova) {
    *outNova = NULL;
    if (!(*head)) return ERR_EMPTY;

    Osoba* temp = *head;
    Osoba* prev = NULL;

    while (temp && strcmp(temp->prez, prezime) != 0) {
        prev = temp;
        temp = temp->next;
    }
    if (!temp) return ERR_NOT_FOUND;

    Osoba* nova = NULL;
    int st = novaOsoba(&nova);
    if (st != OK) return st;

    if (prev == NULL) {
        nova->next = *head;
        *head = nova;
    }
    else {
        prev->next = nova;
        nova->next = temp;
    }

    *outNova = nova;
    return OK;
}

int SortirajPoPrezimenu(Osoba* head) {
    if (!head) return ERR_EMPTY;

    int swapped;
    Osoba* p;
    Osoba* q = NULL;

    do {
        swapped = 0;
        p = head;

        while (p->next != q) {
            if (strcmp(p->prez, p->next->prez) > 0) {
                char imeTmp[50], prezTmp[50];
                int godTmp;

                strcpy(imeTmp, p->ime);
                strcpy(prezTmp, p->prez);
                godTmp = p->god_rod;

                strcpy(p->ime, p->next->ime);
                strcpy(p->prez, p->next->prez);
                p->god_rod = p->next->god_rod;

                strcpy(p->next->ime, imeTmp);
                strcpy(p->next->prez, prezTmp);
                p->next->god_rod = godTmp;

                swapped = 1;
            }
            p = p->next;
        }
        q = p;
    } while (swapped);

    return OK;
}

int upisiListuUDat(const char* imeDat, Osoba* head) {
    FILE* fp = fopen(imeDat, "w");
    if (!fp) {
        printf("Ne mogu otvorit datoteku\n");
        return ERR_FILE;
    }

    Osoba* temp = head;
    while (temp) {
        fprintf(fp, "%s %s %d\n", temp->ime, temp->prez, temp->god_rod);
        temp = temp->next;
    }

    fclose(fp);
    return OK;
}

int citajListuIzDat(const char* imeDat, Osoba** head) {
    FILE* fp = fopen(imeDat, "r");
    if (!fp) {
        printf("Ne mogu otvoriti datoteku\n");
        return ERR_FILE;
    }

    *head = NULL;
    Osoba* zadnji = NULL;

    while (1) {
        Osoba* nova = (Osoba*)malloc(sizeof(Osoba));
        if (!nova) {
            fclose(fp);
            return ERR_ALLOC;
        }

        if (fscanf(fp, "%49s %49s %d", nova->ime, nova->prez, &nova->god_rod) != 3) {
            free(nova);
            break;
        }

        nova->next = NULL;

        if (*head == NULL) {
            *head = nova;
            zadnji = nova;
        }
        else {
            zadnji->next = nova;
            zadnji = nova;
        }
    }

    fclose(fp);
    return OK;
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
    Osoba* novaUbacena = NULL;

    do {
        int st = OK;

        //ovako je urednije
        printf("\nIzaberi jedan broj:\n");
        printf("0 - izlaz\n");
        printf("1 - dodaj na pocetak\n");
        printf("2 - ispisi listu\n");
        printf("3 - dodaj na kraj\n");
        printf("4 - trazi po prezimenu\n");
        printf("5 - brisi po prezimenu\n");
        printf("6 - dodaj iza odredenog prezimena\n");
        printf("7 - dodaj ispred odredenog prezimena\n");
        printf("8 - sortiraj po prezimenu\n");
        printf("9 - upisi listu u datoteku\n");
        printf("10 - citaj listu iz datoteke\n");

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
            if (st == OK) printf("Pronaden: %s %s %d\n", trazena->ime, trazena->prez, trazena->god_rod);
            else printf("Nije pronadena osoba s prezimenom %s\n", prezime);
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

        case 6:
            printf("Iza kojeg prezimena zelite dodati novu osobu? ");
            if (scanf("%49s", prezime) != 1) {
                printf("Krivi unos prezimena\n");
                freeListu(head);
                return ERR_INPUT;
            }
            st = dodajIzaOdredenog(&head, prezime, &novaUbacena);
            if (st == OK) printf("Dodana osoba iza %s: %s %s %d\n", prezime, novaUbacena->ime, novaUbacena->prez, novaUbacena->god_rod);
            else if (st == ERR_NOT_FOUND) printf("Nije pronadena osoba s prezimenom %s\n", prezime);
            else if (st == ERR_EMPTY) printf("Lista je prazna\n");
            break;

        case 7:
            printf("Ispred kojeg prezimena zelite dodati novu osobu? ");
            if (scanf("%49s", prezime) != 1) {
                printf("Krivi unos prezimena\n");
                freeListu(head);
                return ERR_INPUT;
            }
            st = dodajIspredOdredenog(&head, prezime, &novaUbacena);
            if (st == OK) printf("Dodana osoba ispred %s: %s %s %d\n", prezime, novaUbacena->ime, novaUbacena->prez, novaUbacena->god_rod);
            else if (st == ERR_NOT_FOUND) printf("Nije pronadena osoba s prezimenom %s\n", prezime);
            else if (st == ERR_EMPTY) printf("Lista je prazna\n");
            break;

        case 8:
            st = SortirajPoPrezimenu(head);
            if (st == OK) printf("Sortirano\n");
            break;

        case 9:
            st = upisiListuUDat("lista.txt", head);
            if (st == OK) printf("Lista upisana\n");
            break;

        case 10:
            freeListu(head);
            head = NULL;
            st = citajListuIzDat("lista.txt", &head);
            if (st == OK) printf("Lista procitana\n");
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
            else if (st == ERR_FILE) printf("Problem s datotekom\n");
            else printf("Nepoznata greska\n");

            freeListu(head);
            return st;
        }

    } while (unos != 0);

    freeListu(head);
    return 0;
}

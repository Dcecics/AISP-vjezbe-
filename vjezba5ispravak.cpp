#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define OK             0
#define ERR_ALLOC      1
#define ERR_INPUT      2
#define ERR_EMPTY      3

typedef struct Cvor {
    int elem;
    struct Cvor* next;
} Cvor;

void Ispis(Cvor* head) {
    if (head == NULL) {
        printf("Lista je prazna\n");
        return;
    }

    printf("Lista: ");
    while (head) {
        printf("%d ", head->elem);
        head = head->next;
    }
    printf("\n");
}

int DodajNaKraj(Cvor** head, Cvor** tail, int broj) {
    Cvor* novi = (Cvor*)malloc(sizeof(Cvor));
    if (!novi) return ERR_ALLOC;

    novi->elem = broj;
    novi->next = NULL;

    if (*head == NULL) {
        *head = novi;
        *tail = novi;
    }
    else {
        (*tail)->next = novi;
        *tail = novi;
    }
    return OK;
}

/* preskoci sve uzastopne iste vrijednosti */
Cvor* preskociJednake(Cvor* p) {
    if (!p) return NULL;
    int v = p->elem;
    while (p && p->elem == v) p = p->next;
    return p;
}

/* provjeravamo jel uneseno sortirano */
int unosListe(int brListe, Cvor** head) {
    *head = NULL;
    Cvor* tail = NULL;

    int n = 0;
    int broj = 0;
    int prev = 0;
    int prvi = 1;

    printf("\nUnos liste L%d\n", brListe);
    printf("Koliko elem zelite unijeti? ");

    if (scanf("%d", &n) != 1) return ERR_INPUT;

    if (n <= 0) {
        printf("Lista prazna\n");
        return ERR_EMPTY;
    }

    printf("Unesite %d sortiranih brojeva (od manjeg prema vecem):\n", n);

    for (int i = 0; i < n; i++) {
        printf("Elem %d: ", i + 1);
        if (scanf("%d", &broj) != 1) return ERR_INPUT;

        if (!prvi && broj < prev) {
            printf("Lista nije sortirana (%d nakon %d)\n", broj, prev);
            return ERR_INPUT;
        }
        prvi = 0;
        prev = broj;

        int st = DodajNaKraj(head, &tail, broj);
        if (st != OK) return st;
    }

    return OK;
}

int Unija(Cvor* L1, Cvor* L2, Cvor** rez) {
    *rez = NULL;
    Cvor* tail = NULL;

    while (L1 && L2) {
        if (L1->elem < L2->elem) {
            int st = DodajNaKraj(rez, &tail, L1->elem);
            if (st != OK) return st;
            L1 = preskociJednake(L1);
        }
        else if (L1->elem > L2->elem) {
            int st = DodajNaKraj(rez, &tail, L2->elem);
            if (st != OK) return st;
            L2 = preskociJednake(L2);
        }
        else {
            int st = DodajNaKraj(rez, &tail, L1->elem);
            if (st != OK) return st;
            L1 = preskociJednake(L1);
            L2 = preskociJednake(L2);
        }
    }

    while (L1) {
        int st = DodajNaKraj(rez, &tail, L1->elem);
        if (st != OK) return st;
        L1 = preskociJednake(L1);
    }

    while (L2) {
        int st = DodajNaKraj(rez, &tail, L2->elem);
        if (st != OK) return st;
        L2 = preskociJednake(L2);
    }

    return (*rez == NULL) ? ERR_EMPTY : OK;
}

int Presjek(Cvor* L1, Cvor* L2, Cvor** rez) {
    *rez = NULL;
    Cvor* tail = NULL;

    while (L1 && L2) {
        if (L1->elem < L2->elem) {
            L1 = preskociJednake(L1);
        }
        else if (L1->elem > L2->elem) {
            L2 = preskociJednake(L2);
        }
        else {
            int st = DodajNaKraj(rez, &tail, L1->elem);
            if (st != OK) return st;
            L1 = preskociJednake(L1);
            L2 = preskociJednake(L2);
        }
    }

    return (*rez == NULL) ? ERR_EMPTY : OK;
}

void freeMem(Cvor* head) {
    while (head) {
        Cvor* next = head->next;
        free(head);
        head = next;
    }
}

int main() {
    Cvor* L1 = NULL;
    Cvor* L2 = NULL;
    Cvor* unijaRez = NULL;
    Cvor* presjekRez = NULL;

    int st = unosListe(1, &L1);
    if (st != OK && st != ERR_EMPTY) {
        printf("Problem pri unosu L1\n");
        freeMem(L1);
        return 1;
    }
    printf("\nUnesena L1:\n");
    Ispis(L1);

    st = unosListe(2, &L2);
    if (st != OK && st != ERR_EMPTY) {
        printf("Problem pri unosu L2\n");
        freeMem(L1);
        freeMem(L2);
        return 1;
    }
    printf("\nUnesena L2:\n");
    Ispis(L2);

    st = Unija(L1, L2, &unijaRez);
    printf("\nL1 U L2:\n");
    if (st == OK) Ispis(unijaRez);
    else if (st == ERR_EMPTY) printf("Prazna\n");
    else {
        printf("Greska pri racunanju unije\n");
        freeMem(L1);
        freeMem(L2);
        freeMem(unijaRez);
        freeMem(presjekRez);
        return st;
    }

    st = Presjek(L1, L2, &presjekRez);
    printf("\nL1 n L2:\n");
    if (st == OK) Ispis(presjekRez);
    else if (st == ERR_EMPTY) printf("Prazna\n");
    else {
        printf("Greska pri racunanju presjeka\n");
        freeMem(L1);
        freeMem(L2);
        freeMem(unijaRez);
        freeMem(presjekRez);
        return st;
    }

    freeMem(L1);
    freeMem(L2);
    freeMem(unijaRez);
    freeMem(presjekRez);

    return 0;
}

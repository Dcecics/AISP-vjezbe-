#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN 10
#define MAX 100

struct cvor;
typedef struct cvor* Pozicija;

struct cvor {
    int element;
    int prioritet;
    Pozicija sljedeci;
};

int slucajniBroj(void);
int pushCirkularniStog(Pozicija glava, int vrijednost, int* velicina, int max);
int popCirkularniStog(Pozicija glava, int* velicina);
int pushRedPrioritet(Pozicija glava, int vrijednost, int prioritet);
int popRedPrioritet(Pozicija glava);
int ispisCirkularniStog(Pozicija glava);
int ispis(Pozicija prvi);
void obrisiCirkularniStog(Pozicija glava);
void obrisiSve(Pozicija glava);

int main() {
    struct cvor glavaStog;
    struct cvor glavaRed;
    int maxStog = 0, velicinaStog = 0;
    int izbor = 0;

    glavaStog.sljedeci = &glavaStog;
    glavaRed.sljedeci = NULL;

    srand((unsigned)time(NULL));

    printf("Unesite maksimalnu velicinu stoga: ");
    scanf("%d", &maxStog);

    do {
        printf("\n1 Push cirkularni stog\n2 Pop cirkularni stog\n3 Ispis cirkularni stog\n");
        printf("4 Push red s prioritetom\n5 Pop red s prioritetom\n6 Ispis red s prioritetom\n7 Izlaz\n");
        scanf("%d", &izbor);

        switch (izbor) {
        case 1:
            if (pushCirkularniStog(&glavaStog, slucajniBroj(), &velicinaStog, maxStog))
                printf("Stog je pun\n");
            break;
        case 2:
            if (popCirkularniStog(&glavaStog, &velicinaStog))
                printf("Stog je prazan\n");
            break;
        case 3:
            ispisCirkularniStog(&glavaStog);
            break;
        case 4:
            pushRedPrioritet(&glavaRed, slucajniBroj(), rand() % 5 + 1);
            break;
        case 5:
            if (popRedPrioritet(&glavaRed))
                printf("Red je prazan\n");
            break;
        case 6:
            ispis(glavaRed.sljedeci);
            break;
        }
    } while (izbor != 7);

    obrisiCirkularniStog(&glavaStog);
    obrisiSve(&glavaRed);

    return 0;
}

int slucajniBroj(void) {
    return rand() % (MAX - MIN + 1) + MIN;
}

int pushCirkularniStog(Pozicija glava, int vrijednost, int* velicina, int max) {
    if (*velicina >= max) return -1;

    Pozicija novi = malloc(sizeof(struct cvor));
    if (!novi) return -1;

    novi->element = vrijednost;
    novi->sljedeci = glava->sljedeci;
    glava->sljedeci = novi;
    (*velicina)++;
    return 0;
}

int popCirkularniStog(Pozicija glava, int* velicina) {
    if (*velicina == 0) return -1;

    Pozicija temp = glava->sljedeci;
    glava->sljedeci = temp->sljedeci;
    printf("Uklonjeno: %d\n", temp->element);
    free(temp);
    (*velicina)--;
    return 0;
}

int ispisCirkularniStog(Pozicija glava) {
    if (glava->sljedeci == glava) {
        printf("Stog je prazan\n");
        return 0;
    }

    Pozicija p = glava->sljedeci;
    while (p != glava) {
        printf("%d ", p->element);
        p = p->sljedeci;
    }
    printf("\n");
    return 0;
}

int pushRedPrioritet(Pozicija glava, int vrijednost, int prioritet) {
    Pozicija novi = malloc(sizeof(struct cvor));
    if (!novi) return -1;

    novi->element = vrijednost;
    novi->prioritet = prioritet;
    novi->sljedeci = NULL;

    while (glava->sljedeci && glava->sljedeci->prioritet >= prioritet)
        glava = glava->sljedeci;

    novi->sljedeci = glava->sljedeci;
    glava->sljedeci = novi;
    return 0;
}

int popRedPrioritet(Pozicija glava) {
    if (!glava->sljedeci) return -1;

    Pozicija temp = glava->sljedeci;
    glava->sljedeci = temp->sljedeci;
    printf("Uklonjeno: %d (prioritet %d)\n", temp->element, temp->prioritet);
    free(temp);
    return 0;
}

int ispis(Pozicija p) {
    if (!p) {
        printf("Prazno\n");
        return 0;
    }

    while (p) {
        printf("%d(%d) ", p->element, p->prioritet);
        p = p->sljedeci;
    }
    printf("\n");
    return 0;
}

void obrisiCirkularniStog(Pozicija glava) {
    while (glava->sljedeci != glava) {
        popCirkularniStog(glava, &(int){1});
    }
}

void obrisiSve(Pozicija glava) {
    Pozicija temp;
    while (glava->sljedeci) {
        temp = glava->sljedeci;
        glava->sljedeci = temp->sljedeci;
        free(temp);
    }
}
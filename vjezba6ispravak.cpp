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
    Pozicija sljedeci;
};

int pushStog(Pozicija glava, int vrijednost);
int popStog(Pozicija glava);
int pushRed(Pozicija glava, Pozicija* zadnji, int vrijednost);
int popRed(Pozicija glava, Pozicija* zadnji);
int ispis(Pozicija prvi);
int obrisiSve(Pozicija glava);
int slucajniBroj(void);

int main() {
    struct cvor glavaStog = { 0, NULL };
    struct cvor glavaRed = { 0, NULL };
    Pozicija zadnjiRed = NULL;
    int izbor = 0;
    int rezultat = 0;

    srand((unsigned)time(NULL));

    do {
        printf("\n1 Push stog\n2 Pop stog\n3 Ispis stog\n4 Ispis red\n5 Push red\n6 Pop red\n");
        scanf("%d", &izbor);

        switch (izbor) {

        case 1:
            rezultat = pushStog(&glavaStog, slucajniBroj());
            if (rezultat == -1)
                printf("Greska pri alokaciji memorije!\n");
            break;

        case 2:
            rezultat = popStog(&glavaStog);
            if (rezultat == -1)
                printf("Stog je prazan!\n");
            break;

        case 3:
            ispis(glavaStog.sljedeci);
            break;

        case 4:
            ispis(glavaRed.sljedeci);
            break;

        case 5:
            rezultat = pushRed(&glavaRed, &zadnjiRed, slucajniBroj());
            if (rezultat == -1)
                printf("Greska pri alokaciji memorije!\n");
            break;

        case 6:
            rezultat = popRed(&glavaRed, &zadnjiRed);
            if (rezultat == -1)
                printf("Red je prazan!\n");
            break;

        default:
            printf("Nepostojeca opcija!\n");
        }

        printf("0 nastavi, 1 izlaz: ");
        scanf("%d", &izbor);

    } while (izbor == 0);

    obrisiSve(&glavaStog);
    obrisiSve(&glavaRed);

    return 0;
}

int slucajniBroj(void) {
    return rand() % (MAX - MIN + 1) + MIN;
}

int pushStog(Pozicija glava, int vrijednost) {
    Pozicija novi = (Pozicija)malloc(sizeof(struct cvor));
    if (!novi)
        return -1;

    novi->element = vrijednost;
    novi->sljedeci = glava->sljedeci;
    glava->sljedeci = novi;
    return 0;
}

int popStog(Pozicija glava) {
    Pozicija temp;

    if (!glava->sljedeci)
        return -1;

    temp = glava->sljedeci;
    glava->sljedeci = temp->sljedeci;
    printf("Uklonjeno: %d\n", temp->element);
    free(temp);
    return 0;
}

int pushRed(Pozicija glava, Pozicija* zadnji, int vrijednost) {
    Pozicija novi = (Pozicija)malloc(sizeof(struct cvor));
    if (!novi)
        return -1;

    novi->element = vrijednost;
    novi->sljedeci = NULL;

    if (!glava->sljedeci)
        glava->sljedeci = novi;
    else
        (*zadnji)->sljedeci = novi;

    *zadnji = novi;
    return 0;
}

int popRed(Pozicija glava, Pozicija* zadnji) {
    Pozicija temp;

    if (!glava->sljedeci)
        return -1;

    temp = glava->sljedeci;
    glava->sljedeci = temp->sljedeci;

    if (!glava->sljedeci)
        *zadnji = NULL;

    printf("Uklonjeno: %d\n", temp->element);
    free(temp);
    return 0;
}

int ispis(Pozicija p) {
    if (!p) {
        printf("Prazno\n");
        return 0;
    }

    while (p) {
        printf("%d ", p->element);
        p = p->sljedeci;
    }
    printf("\n");
    return 0;
}

int obrisiSve(Pozicija glava) {
    Pozicija temp;
    while (glava->sljedeci) {
        temp = glava->sljedeci;
        glava->sljedeci = temp->sljedeci;
        free(temp);
    }
    return 0;
}


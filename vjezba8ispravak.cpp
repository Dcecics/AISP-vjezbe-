#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct cvor;
typedef struct cvor* Pozicija;

struct cvor {
    int element;
    Pozicija sljedeci;
};

int push(Pozicija glava, int vrijednost);
int pop(Pozicija glava, int* vrijednost);
void obrisiSve(Pozicija glava);

int main() {
    struct cvor glava;
    glava.sljedeci = NULL;

    FILE* dat = fopen("postfiks.txt", "r");
    if (!dat) {
        printf("Greska pri otvaranju datoteke\n");
        return 1;
    }

    int a, b, rezultat, broj;
    char znak;

    while ((znak = fgetc(dat)) != EOF) {
        if (znak >= '0' && znak <= '9') {
            ungetc(znak, dat);
            fscanf(dat, "%d", &broj);
            push(&glava, broj);
        }
        else if (znak == '+' || znak == '-' || znak == '*' || znak == '/') {
            if (pop(&glava, &b) || pop(&glava, &a)) {
                printf("Neispravan izraz\n");
                fclose(dat);
                obrisiSve(&glava);
                return 1;
            }

            if (znak == '/' && b == 0) {
                printf("Dijeljenje s nulom\n");
                fclose(dat);
                obrisiSve(&glava);
                return 1;
            }

            switch (znak) {
            case '+': rezultat = a + b; break;
            case '-': rezultat = a - b; break;
            case '*': rezultat = a * b; break;
            case '/': rezultat = a / b; break;
            }

            push(&glava, rezultat);
        }
    }

    if (!glava.sljedeci || glava.sljedeci->sljedeci) {
        printf("Neispravan izraz\n");
    }
    else {
        printf("Rezultat: %d\n", glava.sljedeci->element);
    }

    fclose(dat);
    obrisiSve(&glava);
    return 0;
}

int push(Pozicija glava, int vrijednost) {
    Pozicija novi = malloc(sizeof(struct cvor));
    if (!novi) return -1;

    novi->element = vrijednost;
    novi->sljedeci = glava->sljedeci;
    glava->sljedeci = novi;
    return 0;
}

int pop(Pozicija glava, int* vrijednost) {
    if (!glava->sljedeci) return -1;

    Pozicija temp = glava->sljedeci;
    *vrijednost = temp->element;
    glava->sljedeci = temp->sljedeci;
    free(temp);
    return 0;
}

void obrisiSve(Pozicija glava) {
    Pozicija temp;
    while (glava->sljedeci) {
        temp = glava->sljedeci;
        glava->sljedeci = temp->sljedeci;
        free(temp);
    }
}

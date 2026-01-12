#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define OK             0
#define ERR_ALLOC      1
#define ERR_FILE       2
#define ERR_EMPTY      3
#define ERR_EXPR       4
#define ERR_DIV0       5

typedef struct _cvor {
    int broj;
    struct _cvor* next;
} Cvor;

int Push(Cvor** head, int br) {
    Cvor* novi = (Cvor*)malloc(sizeof(Cvor));
    if (!novi) return ERR_ALLOC;

    novi->broj = br;
    novi->next = *head;
    *head = novi;
    return OK;
}

int Pop(Cvor** head, int* out) {
    if (*head == NULL) return ERR_EMPTY;

    Cvor* temp = *head;
    *out = temp->broj;
    *head = (*head)->next;
    free(temp);
    return OK;
}

int jePrazan(Cvor* head) {
    return head == NULL;
}

void freeStog(Cvor* head) {
    while (head) {
        Cvor* next = head->next;
        free(head);
        head = next;
    }
}

int izrPostfiks(const char* imeDat, int* outRez) {
    FILE* fp = fopen(imeDat, "r");
    if (!fp) return ERR_FILE;

    Cvor* stog = NULL;
    int c;

    int broj = 0;
    int imabr = 0;

    while ((c = fgetc(fp)) != EOF) {
        if (isdigit(c)) {
            broj = broj * 10 + (c - '0');
            imabr = 1;
        }
        else if (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
            if (imabr) {
                int st = Push(&stog, broj);
                if (st != OK) {
                    fclose(fp);
                    freeStog(stog);
                    return st;
                }
                broj = 0;
                imabr = 0;
            }
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            if (imabr) {
                int st = Push(&stog, broj);
                if (st != OK) {
                    fclose(fp);
                    freeStog(stog);
                    return st;
                }
                broj = 0;
                imabr = 0;
            }

            int op2, op1;
            int st = Pop(&stog, &op2);
            if (st != OK) { fclose(fp); freeStog(stog); return ERR_EXPR; }

            st = Pop(&stog, &op1);
            if (st != OK) { fclose(fp); freeStog(stog); return ERR_EXPR; }

            int rez = 0;
            if (c == '+') rez = op1 + op2;
            else if (c == '-') rez = op1 - op2;
            else if (c == '*') rez = op1 * op2;
            else {
                if (op2 == 0) { fclose(fp); freeStog(stog); return ERR_DIV0; }
                rez = op1 / op2;
            }

            st = Push(&stog, rez);
            if (st != OK) { fclose(fp); freeStog(stog); return st; }
        }
        else {
            fclose(fp);
            freeStog(stog);
            return ERR_EXPR;
        }
    }

    fclose(fp);

    if (imabr) {
        int st = Push(&stog, broj);
        if (st != OK) { freeStog(stog); return st; }
    }

    int konacni;
    int st = Pop(&stog, &konacni);
    if (st != OK) { freeStog(stog); return ERR_EXPR; }

    if (!jePrazan(stog)) {
        freeStog(stog);
        return ERR_EXPR;
    }

    *outRez = konacni;
    return OK;
}

int main(void) {
    int rezultat = 0;
    int st = izrPostfiks("postfiks.txt", &rezultat);

    if (st == OK) {
        printf("Finalni rez: %d\n", rezultat);
    }
    else {
        printf("Error ");
        if (st == ERR_FILE) printf("Ne mogu otvorit datoteku\n");
        else if (st == ERR_ALLOC) printf("Alokacija nije uspila\n");
        else if (st == ERR_DIV0) printf("Dijeljenje s 0\n");
        else if (st == ERR_EXPR) printf("Neispravan postfiks izraz\n");
        else printf("Nepoznata greska\n");
    }

    return 0;
}

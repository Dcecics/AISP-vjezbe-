#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


struct node;
typedef struct node* Position;
struct node {
    int element;
    Position next;


};
int PushStack(Position, int);
int Pop(Position);
int calculate(Position);
int Print(Position);
void deleteAll(Position);
int main()
{

    struct node Head;
    Head.next = NULL;
    FILE* fp;

    int operand1, operand2, rez = 0;
    char ch = '\0';
    int num = 0;

    fp = fopen("postfiks.txt", "r");
    if (fp == NULL) {
        printf("Datoteku je nemoguce otvoriti!!!");
        return -1;
    }


    while (!feof(fp)) {
        ch = fgetc(fp);
        if (ch >= '0' && ch <= '9') {
            ungetc(ch, fp);
            fscanf(fp, "%d", &num);
            PushStack(&Head, num);
        }
        else if (ch != 32 && ch != '\n' && ch != EOF) {
            operand2 = Pop(&Head);
            operand1 = Pop(&Head);
            switch (ch) {

            case '+':

                rez = operand1 + operand2;
                break;
            case '-':

                rez = operand1 - operand2;
                break;
            case '/':

                if (operand2 != 0) {
                    rez = operand1 / operand2;
                    break;
                }
                else {
                    printf("Error, cannot be divided with 0\n");
                    break;
                }
            case '*':

                rez = operand1 * operand2;
                break;

            default:
                printf("Invalid operator: %c\n", ch);
                fclose(fp);
                deleteAll(&Head);
                return 1;
                break;


            }
            PushStack(&Head, rez);

        }
    }
    printf("\nFinal result of postfix is: %d\n", rez);
    Print(Head.next);
    deleteAll(&Head);
    fclose(fp);



    return 0;

}
int Print(Position P) {
    if (P == NULL) {
        printf("Prazna lista\n");
        return 0;
    }
    while (P != NULL) {
        printf(" %d\n", P->element);
        P = P->next;
    }
    printf("\n");
    return 0;
}
int PushStack(Position P, int value) {
    Position temp;


    temp = (Position)malloc(sizeof(struct node));
    if (temp == NULL) {
        printf("Memory is not allocated!!!");
        return -1;
    }
    temp->element = value;   // Sprema broj u novi èvor
    temp->next = P->next;    // Novi èvor pokazuje na prvi element stoga
    P->next = temp;          // Novi èvor postaje vrh stoga

    Print(P->next);          // Ispisuje trenutno stanje stoga

    return 0;
}
int Pop(Position P) {
    Position temp = NULL;
    int value = 0;
    if (P->next != NULL) {
        temp = P->next;           // Pokazivaè na vrh stoga
        P->next = temp->next;     // Pomièe vrh na sljedeæi element
        value = temp->element;    // Sprema vrijednost vrha
        free(temp);               // Bri?e stari vrh iz memorije
    }
    return value;                  // Vraæa vrijednost vrha
}
void deleteAll(Position P) {
    Position temp = NULL;
    while (P->next != NULL)
    {
        temp = P->next;
        P->next = temp->next;
        free(temp);

    }

}
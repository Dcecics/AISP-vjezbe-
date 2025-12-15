#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define MAX 100
#define MIN 10
struct node;
typedef struct node* Position;
struct node {
	int element;
	Position next;
};

int PushStack(Position, int);
int PushQueue(Position, int);
int Pop(Position);
int getRandom();
int Print(Position);
int deletAll(Position);

int main() {

	struct node headStack;
	struct node headQueue;
	int resualt = 0, choice = 0;
	headQueue.next = NULL;
	headStack.next = NULL;
	printf("Unesite sto zelite raditi:\n1.Push na stog\n2.Pop iz stog\n3.Ispisi stog\n4.Ispisi red\n5.Push na red\n6.Pop iz reda\n");
	do {
		printf("Unesi 1,2,3,4,5 ili 6\n");
		scanf(" %d", &choice);
		if (choice < 1 || choice > 6) {
			printf(" Netocan unos!!!\n");
		}
		else
		{
			switch (choice) {
			case 1:
				resualt = PushStack(&headStack, getRandom());
				if (resualt == -1) {
					printf(" Greska.\n");
				}
				else {
					printf(" Sve je proslo u redu.\n");
				}
				break;
			case 2:
				resualt = Pop(&headStack);
				break;
			case 3:
				printf("Stog je:");
				Print(headStack.next);
				break;
			case 4:
				printf("Red je:");
				Print(headQueue.next);
				break;
			case 5:
				resualt = PushQueue(&headQueue, getRandom());
				if (resualt == -1) {
					printf(" Greska.\n");
				}
				else {
					printf(" Sve je proslo u redu.\n");
				}
				break;
			case 6:
				resualt = Pop(&headQueue);
				break;
			}
		}
		printf("Ako zelite stati unesite 1, ako zelite nastaviti unesite 0!\n");
		scanf(" %d", &choice);
	} while (choice != 1);
	deletAll(&headStack);
	deletAll(&headQueue);
	return 0;
}
int getRandom() {
	int value = 0;
	//srand((unsigned)time(NULL));
	value = rand() % ((MAX - MIN + 1) + MIN);
	return value;
}
int PushStack(Position P, int value) {
	Position temp;
	temp = (Position)malloc(sizeof(struct node));
	if (temp == NULL) {
		printf("Alokacija nije uspijela!!");
		return -1;
	}
	temp->element = value;
	temp->next = P->next;
	P->next = temp;
	return 0;
}
int Pop(Position P) {
	Position temp = NULL;
	if (P->next != NULL) {
		temp = P->next;
		P->next = temp->next;
		printf("Izbrisana vrijednost je %d\n", temp->element);
		free(temp);
	}
	return 0;
}
int Print(Position P) {
	if (P == NULL) {
		printf("Prazna lista\n");
		return 0;
	}
	while (P != NULL) {
		printf(" %d ", P->element);
		P = P->next;
	}
	printf("\n");
	return 0;
}
int PushQueue(Position  P, int value) {
	static Position last = NULL;
	Position temp = NULL;
	if (last == NULL) {
		last = P;
	}
	temp = (Position)malloc(sizeof(struct node));
	if (temp == NULL) {
		printf("Alokacija nije uspijela!!");
		return -1;
	}
	temp->element = value;
	temp->next = last->next;
	last->next = temp;
	last = last->next;
	return 0;
}
int deletAll(Position P) {
	Position temp = NULL;
	while (P->next != NULL)
	{
		temp = P->next;
		P->next = temp->next;
		free(temp);

	}
	return 0;
}
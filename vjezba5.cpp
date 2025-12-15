#define _CRT_SECURE_NO_WARNINGS
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
int readFromFile(Position);
int presjek(Position, Position, Position);
int printList(Position);
int unija(Position, Position, Position);
int deletAll(Position);
int main() {

	struct node head1;
	struct node head2;
	struct node headPresjek;
	struct node headUnija;
	int result = 0;
	head1.next = NULL;
	head2.next = NULL;
	headPresjek.next = NULL;
	headUnija.next = NULL;
	result = readFromFile(&head1);
	if (result == 1) {
		printf("Error datoteka nije otvorena!\n");
		return 0;
	}
	else if (result == -1) {
		printf("Error memorija nije alocirana!\n");
		deletAll(&head1);
		return 0;
	}
	else {
		printf("Sve je proslo u redu!\n");
	}
	printf("Lista1:\t");
	printList(head1.next);
	result = readFromFile(&head2);
	if (result == 1) {
		printf("Error memorija nije alocirana!\n");
		deletAll(&head1);
		return 0;
	}
	else if (result == -1) {
		printf("Error memorija nije alocirana!\n");
		deletAll(&head1);
		deletAll(&head2);
		return 0;
	}
	else {
		printf("Sve je proslo u redu!\n");
	}
	printf("Lista2:\t");
	printList(head2.next);
	result = presjek(head1.next, head2.next, &headPresjek);
	if (result == -2) {
		printf("Error memorija nije alocirana!\n");
		deletAll(&head1);
		deletAll(&head1);
		deletAll(&headPresjek);
		return 0;
	}
	else {
		printf("Sve je proslo u redu!\n");
	}
	printf("Presjek:");
	printList(headPresjek.next);
	result = unija(head1.next, head2.next, &headUnija);
	if (result == -2) {
		printf("Error memorija nije alocirana!\n");
		deletAll(&head1);
		deletAll(&head1);
		deletAll(&headUnija);
		return 0;
	}
	else {
		printf("Sve je proslo u redu!\n");
	}
	printf("Unija:\t");
	printList(headUnija.next);
	deletAll(&head1);
	deletAll(&head2);
	deletAll(&headPresjek);
	deletAll(&headUnija);
	printList(headPresjek.next);
	printList(headUnija.next);
	printList(head1.next);
	printList(head2.next);
	return 0;
}
int readFromFile(Position P) {
	FILE* fp = NULL;
	char fileName[128] = "\0";
	Position q = NULL;
	printf("Upisite ime datoteke:\n");
	scanf(" %s", fileName);
	fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("Datoteka nije pronadena!!\n");
		return 1;
	}
	while (!feof(fp)) {
		q = (Position)malloc(sizeof(struct node));
		if (q == NULL) {
			printf("Alokacija nije uspijela!!\n");
			fclose(fp);
			return -1;
		}

		while (P->next != NULL) {
			P = P->next;
		}
		fscanf(fp, "%d", &q->element);
		q->next = P->next;
		P->next = q;
	}
	fclose(fp);
	return 0;
}
int presjek(Position L1, Position L2, Position P) {
	Position q = NULL;
	while (L1 != NULL && L2 != NULL)
	{
		if (L1->element == L2->element) {
			q = (Position)malloc(sizeof(struct node));
			if (q == NULL) {
				printf("Alokacija nije uspijela!!\n");
				return -1;
			}
			q->element = L1->element;  
			q->next = P->next;          
			P->next = q;                
			P = P->next;
			L1 = L1->next;
			L2 = L2->next;              
		}
		else if (L1->element > L2->element) {
			L2 = L2->next;              
		}
		else if (L1->element < L2->element) {
			L1 = L1->next;              
		}
	}
	return 0;
}
int printList(Position P) {
	if (P == NULL) {
		printf("Prazna lista\n");
		return 0;
	}
	while (P != NULL) {
		printf(" %d\t", P->element);
		P = P->next;
	}
	printf("\n");
	return 0;
}
int unija(Position L1, Position L2, Position U) {
	Position q = NULL;
	while (L1 != NULL || L2 != NULL)
	{
		q = (Position)malloc(sizeof(struct node));
		if (q == NULL) {
			printf("Alokacija nije uspijela!!\n");
			return -1;
		}
		if (L1 == NULL) {             
			q->element = L2->element;
			L2 = L2->next;
		}
		else if (L2 == NULL) {
			q->element = L1->element;
			L1 = L1->next;
		}
		else
		{
			if (L1->element > L2->element) {    
				q->element = L2->element;
				L2 = L2->next;
			}
			else if (L1->element < L2->element) {
				q->element = L1->element;
				L1 = L1->next;
			}
			else {                     
				q->element = L1->element;
				L1 = L1->next;
				L2 = L2->next;
			}
		}
		q->next = U->next;
		U->next = q;
		U = U->next;      
	}
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
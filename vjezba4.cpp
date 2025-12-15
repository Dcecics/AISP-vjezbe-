#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define ERRORFILE -1;
#define ERRORMEMORY -2;
struct node;
typedef struct node* Position;
struct node {
	int coefficient;
	int exponent;
	Position next;
};
int readPolynom(Position);
int sumPolynom(Position, Position, Position);
int mulPolynom(Position, Position, Position);
int printList(Position);
int freePolynom(Position);
int main() {
	struct node head1;
	struct node head2;
	struct node headSuma;
	struct node headMultiple;
	int result = 0;
	head1.next = NULL;
	head2.next = NULL;
	headSuma.next = NULL;
	headMultiple.next = NULL;
	result = readPolynom(&head1);
	if (result == -1) {
		printf("Error file not open!\n");
		return 0;
	}
	else if (result == -2) {
		printf("Error memory is not allocated!\n");
		freePolynom(&head1);
		return 0;
	}
	else {
		printf("Everything is okayl!\n");
	}
	result = readPolynom(&head2);
	if (result == -1) {
		printf("Error! File not opened!\n");
		freePolynom(&head1);
		return 0;
	}
	else if (result == -2) {
		printf("Error memory is not allocated!\n");
		freePolynom(&head1);
		freePolynom(&head2);
		return 0;
	}
	else {
		printf("Everything is okay!\n");
	}
	printList(head1.next);
	printList(head2.next);
	result = sumPolynom(head1.next, head2.next, &headSuma);
	if (result == -2) {
		printf("Error memory is not allocated!\n");
		freePolynom(&head1);
		freePolynom(&head1);
		freePolynom(&headSuma);
		return 0;
	}
	else {
		printf("Everything is okayl!\n");
	}
	printList(headSuma.next);
	result = mulPolynom(head1.next, head2.next, &headMultiple);
	if (result == -2) {
		printf("Error memory is not allocated!\n");
		freePolynom(&head1);
		freePolynom(&head1);
		freePolynom(&headMultiple);
		return 0;
	}
	else {
		printf("Everything is okay!\n");
	}
	printList(headMultiple.next);
	freePolynom(&head1);
	freePolynom(&head2);
	freePolynom(&headSuma);
	freePolynom(&headMultiple);
	printList(headMultiple.next);
	printList(headSuma.next);
	printList(head1.next);
	printList(head2.next);
	return 0;
}
int readPolynom(Position P) {
	FILE* fp = NULL;
	char fileName[128] = "\0";
	Position q = NULL;
	Position start = P;
	printf("Type name of file:\n");
	scanf(" %s", fileName);
	fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("File is not opened!!!\n");
		return ERRORFILE;
	}
	while (!feof(fp)) {
		q = (Position)malloc(sizeof(struct node));
		if (q == NULL) {
			printf("Allocation failed!!!\n");
			fclose(fp);
			return ERRORMEMORY;
		}
		if (fscanf(fp, "%d %d", &(q->coefficient), &(q->exponent)) == 2) {
			while (P->next != NULL && P->next->exponent > q->exponent) {
				P = P->next;
			}
			q->next = P->next;
			P->next = q;
		}
		P = start;

	}
	fclose(fp);
	return 0;
}
int sumPolynom(Position P1, Position P2, Position Suma) {
	Position q = NULL;
	while (P1 != NULL || P2 != NULL)
	{
		q = (Position)malloc(sizeof(struct node));
		if (q == NULL) {
			printf("Allocation failed!!!\n");
			return ERRORMEMORY;
		}
		if (P1 == NULL) {
			q->exponent = P2->exponent;
			q->coefficient = P2->coefficient;

			P2 = P2->next;
		}
		else if (P2 == NULL) {
			q->exponent = P1->exponent;
			q->coefficient = P1->coefficient;
			P1 = P1->next;
		}
		else {
			if (P1->exponent > P2->exponent)
			{
				q->exponent = P1->exponent;
				q->coefficient = P1->coefficient;

				P1 = P1->next;
			}
			else if (P1->exponent < P2->exponent)
			{
				q->exponent = P2->exponent;
				q->coefficient = P2->coefficient;

				P2 = P2->next;
			}
			else
			{
				q->exponent = P1->exponent;
				q->coefficient = P1->coefficient + P2->coefficient;

				P1 = P1->next;
				P2 = P2->next;
			}
		}
		q->next = Suma->next;
		Suma->next = q;
		Suma = Suma->next;
	}

	return 0;
}
int mulPolynom(Position P1, Position P2, Position multiple) {
	Position q = NULL, i = NULL, j = NULL, tmp = NULL;
	int eksp = 0;
	int koef = 0;
	i = P1;
	while (i != NULL)
	{
		j = P2;
		while (j != NULL)
		{
			eksp = i->exponent + j->exponent;
			koef = i->coefficient * j->coefficient;
			tmp = multiple;
			while (tmp->next != NULL && tmp->next->exponent > eksp)
				tmp = tmp->next;
			if (tmp->next != NULL && tmp->next->exponent == eksp)
			{
				tmp->next->coefficient += koef;
			}
			else
			{
				q = (Position)malloc(sizeof(struct node));
				if (q == NULL) {
					printf("Allocation failed!!!\n");
					return ERRORMEMORY;
				}
				q->exponent = eksp;
				q->coefficient = koef;
				q->next = tmp->next;
				tmp->next = q;
			}
			j = j->next;
		}
		i = i->next;
	}
	return 0;
}
int printList(Position P) {
	Position start = P;
	if (P == NULL) {
		printf("Empty list\n");
		return 0;
	}
	printf("Polynomial:\t");
	while (P != NULL) {
		if (P != start && P->coefficient > 0) {
			printf("+%dx^(%d)", P->coefficient, P->exponent);
		}
		else {
			printf("%dx^(%d)", P->coefficient, P->exponent);
		}
		P = P->next;
	}
	printf("\n");
	return 0;
}
int freePolynom(Position P) {
	Position temp = NULL, start = P;
	while (P->next != NULL)
	{
		temp = P->next;
		P->next = temp->next;
		free(temp);

	}
	return 0;
}
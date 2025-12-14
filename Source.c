#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct node;
typedef struct node* Position;
struct node {
	int koef;
	int eksp;
	Position next;
};
int readPolynom(Position);
int sumaPolynom(Position, Position, Position);
int MulPolynom(Position, Position, Position);
int printList(Position);
int deletAll(Position);
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
	if (result == 1) {
		printf("Datoteka nije otvorena!\n");
		return 0;
	}
	else if (result == -1) {
		printf("Greska pri alokaciji memorije!\n");
		deletAll(&head1);
		return 0;
	}
	else {
		printf("Sve je proslo u redu!\n");
	}
	result = readPolynom(&head2);
	if (result == 1) {
		printf("Datoteka nije otvorena!\n");
		return 0;
	}
	else if (result == -1) {
		printf("Greska pri alokaciji memorije!\n");
		deletAll(&head2);
		return 0;
	}
	else {
		printf("Sve je proslo u redu!\n");
	}
	printf("Prvi polinom:\t");
	printList(head1.next);
	printf("Drugi polinom:\t");
	printList(head2.next);
	result = sumaPolynom(head1.next, head2.next, &headSuma);
	if (result == -1) {
		printf("Greska pri alokaciji memorije!\n");
		deletAll(&head1);
		deletAll(&head2);
		deletAll(&headSuma);
		return 0;
	}
	else {
		printf("Sve je proslo u redu!\n");
	}
	printf("Suma polinoma:\t");
	printList(headSuma.next);
	result = MulPolynom(head1.next, head2.next, &headMultiple);
	if (result == -1) {
		printf("Greska pri alokaciji memorije!\n");
		deletAll(&head1);
		deletAll(&head2);
		deletAll(&headMultiple);
		return 0;
	}
	else {
		printf("Sve je proslo u redu!\n");
	}
	printf("Produkt polinoma:");
	printList(headMultiple.next);

	deletAll(&head1);
	deletAll(&head2);
	deletAll(&headSuma);
	deletAll(&headMultiple);
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

	printf("Upisi ime datoteke:\n");
	scanf(" %s", fileName);
	fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("Datoteka nije otvorena!\n");
		return 1;
	}
	int koef, eksp;
	while (fscanf(fp, "%d %d", &koef, &eksp) == 2) {
		q = (Position)malloc(sizeof(struct node));
		if (q == NULL) {
			printf("Greška pri alokaciji memorije!\n");
			fclose(fp);
			return -1;
		}

		// Postavljanje vrednosti 
		q->koef = koef;
		q->eksp = eksp;

		// Umetanje elementa u sortiranu listu
		while (P->next != NULL && P->next->eksp > q->eksp) {
			P = P->next;
		}

		q->next = P->next;
		P->next = q;
	}
	fclose(fp);
	return 0;
}
int sumaPolynom(Position P1, Position P2, Position Suma) {
	Position q = NULL;
	while (P1 != NULL || P2 != NULL)
	{
		q = (Position)malloc(sizeof(struct node));
		if (q == NULL) {
			printf("Greska pri alokaciji memorije!\n");
			return -1;
		}

		if (P1 == NULL) {  // Ako je prvi polinom prazan, preuzmi element iz drugog polinoma
			q->eksp = P2->eksp;
			q->koef = P2->koef;
			P2 = P2->next;
		}
		else if (P2 == NULL) {
			q->eksp = P1->eksp;
			q->koef = P1->koef;
			P1 = P1->next;
		}
		else if (P1->eksp > P2->eksp) {   // Ako je eksponent iz prvog polinoma veæi, dodaj taj element u sumu
			q->eksp = P1->eksp;
			q->koef = P1->koef;
			P1 = P1->next;
		}
		else if (P1->eksp < P2->eksp) {
			q->eksp = P2->eksp;
			q->koef = P2->koef;
			P2 = P2->next;
		}
		else {   // Ako su eksponenti jednaki, zbroji koeficijente
			q->eksp = P1->eksp;
			q->koef = P1->koef + P2->koef;
			P1 = P1->next;
			P2 = P2->next;
		}

		q->next = Suma->next;
		Suma->next = q;
		Suma = q;  // Pokazivaè Suma  pomakni na kraj nove liste

	}

	return 0;
}
int MulPolynom(Position P1, Position P2, Position multiple) {
	Position q = NULL, i = NULL, j = NULL, tmp = NULL;
	int eksp = 0;
	int koef = 0;
	
	for (i = P1; i != NULL; i = i->next) {
		for (j = P2; j != NULL; j = j->next) {
			eksp = i->eksp + j->eksp;
			koef = i->koef * j->koef;

			tmp = multiple;
			while (tmp->next != NULL && tmp->next->eksp > eksp) {
				tmp = tmp->next;
			}
			// Ako je eksponent veæ prisutan u rezultatu, samo zbrojimo koeficijente
			if (tmp->next != NULL && tmp->next->eksp == eksp) {
				tmp->next->koef += koef;
			}
			else {
				// Ako eksponent nije prisutan, stvaramo novi èvor
				q = (Position)malloc(sizeof(struct node));
				if (q == NULL) {
					printf("Greska pri alokaciji memorije!\n");
					return -1;
				}
				q->eksp = eksp;
				q->koef = koef;
				q->next = tmp->next;
				tmp->next = q;
			}
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
		
		if (P->koef > 0) {
			printf("+%dx^%d ", P->koef, P->eksp);
		}
		else {
			printf("%dx^%d ", P->koef, P->eksp);
		}
		P = P->next;
	}
	printf("\n");
	return 0;
}
int deletAll(Position P) {
	Position temp = NULL;

	while (P->next != NULL) {
		temp = P->next;
		P->next = temp->next;
		free(temp);
	}

	return 0;
}
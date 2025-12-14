#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME_LEN 50

typedef struct osoba Osoba;
typedef struct osoba* Position;

struct osoba {
	char firstname[NAME_LEN], lastname[NAME_LEN];
	int birthYear;
	Position Next;
};

int inputF(Position, char[], char[], int);
void printList(Position);
int inputE(Position, char[], char[], int);
Position findEl(Position, char[]);
Position findPrev(Position,char[]);
int deletEl(Position, char[]);
int PushBefore(Position, char[]);
int PushAfter(Position, char[]);
int PushSorted(Position);
int WriteInFile(Position);
int ReadFromFile(Position);
int deleteAll(Position);

int main() {

	Osoba head;
	head.Next = NULL;
	Position person = NULL;
	int choice = 0;
	int check = 0;
	char firstname[NAME_LEN];
	char lastname[NAME_LEN];
	int birthYear;
	char target[NAME_LEN] = { 0 };

	

	while (choice != 12) {

		printf("Izbornik:\n");
		printf("1. Dodaj element na pocetak\n");
		printf("2. Ispisi listu\n");
		printf("3. Dodaj element na kraj\n");
		printf("4. Pronadi element po prezimenu\n");
		printf("5. Izbrisi element po prezimenu\n");
		printf("6. Dodaj element iza odredenog elementa\n");
		printf("7. Dodaj element ispred odredenog elementa\n");
		printf("8. Sortirano dodaj\n");
		printf("9. Upisi listu u datoteku\n");
		printf("10. Citaj listu iz datoteke\n");
		printf("11. Izbrisi cijelu listu\n");
		printf("12. Izlaz\n");
		printf("#########################################################\n");
		printf("Unesite izbor\n");
		scanf(" %d", &choice);

		switch (choice) {
		case 1:
			printf("Unesite ime, prezime i godinu rodenja\n");
			scanf(" %s %s %d", firstname, lastname, &birthYear);
			check=inputF(&head, firstname, lastname, birthYear);
			if (check == -1) {
				printf(" ERROR!! Alokacije nije izvrsena\n");
			}
			else {
				printf(" Sve je proslo u redu.\n");
			}
			break;
		case 2:
			printList(head.Next);
			break;
		case 3:
			printf("Unesite ime, prezime i godinu rodenja\n");
			scanf(" %s %s %d", firstname, lastname, &birthYear);
			check=inputE(&head, firstname, lastname, birthYear);
			if (check == -1) {
				printf(" ERROR!! Alokacije nije izvrsena\n");
			}
			else {
				printf(" Sve je proslo u redu.\n");
			}
			break;
		case 4:
			printf("Upisite trazeno prezime:\n");
			scanf(" %s", target);
			person = findEl(head.Next,target);
			if (person != NULL) {
				printf("Trazeni osoba je:\n %s %s %d\n", person->firstname, person->lastname, person->birthYear);
			}
			else
				printf("Nije pronadena osoba s tim prezimenom\n");
			break;
		case 5:
			printf("Upisite trazeno prezime:\n");
			scanf(" %s", target);
			deletEl(&head,target);
			printList(head.Next);
			break;
		case 6:
			printf("Upisite trazeno prezime:\n");
			scanf(" %s", target);
			check = PushAfter(&head, target);
			if (check == -1) {
				printf(" ERROR!! Alokacije nije izvrsena\n");
			}
			else {
				printf(" Sve je proslo u redu.\n");
			}
			break;
		case 7:
			printf("Upisite trazeno prezime:\n");
			scanf(" %s", target);
			check = PushBefore(&head, target);
			if (check == -1) {
				printf(" ERROR!! Alokacije nije izvrsena\n");
			}
			else {
				printf(" Sve je proslo u redu.\n");
			}
			break;
		case 8:
			check = PushSorted(&head);
			if (check == -1) {
				printf(" ERROR!! Alokacije nije izvrsena\n");
			}
			else {
				printf(" Sve je proslo u redu.\n");
			}
			break;
		case 9:
			check = WriteInFile(&head);
			if (check == -1) {
				printf(" ERROR!! Alokacije nije izvrsena\n");
			}
			else {
				printf(" Sve je proslo u redu.\n");
			}
			break;
		case 10:
			check = ReadFromFile(&head);
			if (check == -1) {
				printf(" ERROR!! Alokacije nije izvrsena\n");
			}
			else {
				printf(" Sve je proslo u redu.\n");
				printList(head.Next);
			}
			break;
		case 11:
			check = deleteAll(&head);
			if (check == -1) {
				printf("ERROR!\n");
				return -1;
			}
			break;
		case 12:
			printf("Kraj odabira!\n");
			break;
		default:
			printf("Pogresan izbor\nPokusajte ponovo");
			break;
		}
	}

	return 0;
}

int inputF(Position P, char firstname[],char lastname[],int birthYear) {

	Position q = (Position*)malloc(sizeof(struct osoba));
	if (q == NULL) {
		printf("Alokacija nije uspijela\n");
		return -1;
	}
	strcpy(q->firstname, firstname);
	strcpy(q->lastname, lastname);
	q->birthYear = birthYear;
	q->Next = P->Next;
	P->Next = q;

	return 0;
}

void printList(Position P) {
	if (P == NULL) {
		printf("Lista je prazna\n");
	}
	else {
		printf("Ispis liste:\n");
		while (P != NULL) {
			printf("%s %s %d\n", P->firstname, P->lastname, P->birthYear);
			P=P->Next;
		}
	}
}

int inputE(Position P, char firstname[], char lastname[], int birthYear) {
	while (P->Next != NULL)
		P = P->Next;

	return inputF(P, firstname, lastname, birthYear);
}
Position findEl(Position P, char lastname[]) {
	while (P != NULL && strcmp(P->lastname, lastname) != 0)
		P = P->Next;

	return P;
}
Position findPrev(Position P, char lastname[]) {
	while (P->Next != NULL && strcmp(P->Next->lastname, lastname) != 0) {
		P = P->Next;
	}

	if (P->Next != NULL) {
		return P;
	}
	return NULL;
}
int deletEl(Position P, char lastname[]) {
	Position temp = NULL;

	P = findPrev(P,lastname);

	if (P != NULL) {// za cijelu listu je potrebna while petlja da sve izbrise alii istog principa
		temp = P->Next;
		P->Next = temp->Next;
		printf("Brisemo osobu: %s %s %d\n", temp->firstname, temp->lastname, temp->birthYear);
		free(temp);
	}
	return 0;
}
int PushAfter(Position P, char target[]) {
	char firstname[NAME_LEN];
	char lastname[NAME_LEN];
	int birthYear;

	P = findEl(P, target);

	if (P == NULL) {
		return -1;
	}

	printf("Unesite ime, prezime i godinu rodenja\n");
	scanf(" %s %s %d", firstname, lastname, &birthYear);

	return inputF(P, firstname, lastname, birthYear);
}
int PushBefore(Position P, char target[]) {
	char firstname[NAME_LEN];
	char lastname[NAME_LEN];
	int birthYear; 
	P = findPrev(P, target);
	if (P == NULL) {
		return -1;
	}
	printf("Unesite ime, prezime i godinu rodenja\n");
	scanf(" %s %s %d", firstname, lastname, &birthYear);
	return inputF(P, firstname, lastname, birthYear);
}
int PushSorted(Position P) {
	Position q = (Position)malloc(sizeof(struct osoba));
	if (q == NULL) {
		printf("Alokacija nije uspjela!\n");
		return -1;
	}
	printf("Unesite ime, prezime i godinu rodenja\n");
	scanf(" %s %s %d", q->firstname, q->lastname, &q->birthYear);
	while (P->Next != NULL && _strcmpi(P->Next->lastname, q->lastname) < 0) {
		P = P->Next;
	}
	q->Next = P->Next;
	P->Next = q;
	return 0;
}
int ReadFromFile(Position P) {
	int result = 0;
	char firstname[NAME_LEN];
	char lastname[NAME_LEN];
	int birthYear = 0;
	char filename[NAME_LEN];
	printf("Upisite ime datoteke\n");
	scanf(" %s", &filename);
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Datoteka nije pronadena!\n");
		return 1;
	}
	while ((fscanf(fp, " %s %s %d", firstname, lastname, &birthYear) > 0)) {
		result = inputF(P, firstname, lastname, birthYear);
		if (result != 0) {
			fclose(fp);
			return result;
		}
	}

	fclose(fp);
	return 0;
}

int WriteInFile(Position P) {
	char filename[NAME_LEN] = { '\0' };
	printf("Unesite ime datoteke\n");
	scanf(" %s", &filename);
	FILE* fp = fopen(filename, "w");
	if (fp == NULL) {
		printf("Alokacija nije uspjela!\n");
		return -1;
	}
	while (P->Next != NULL) {
		fprintf(fp, " %s %s %d\n", P->Next->firstname, P->Next->lastname, P->Next->birthYear);
		P->Next = P->Next->Next;
	}
	/*while (P != NULL) {
		fprintf(fp, " %s %s %d\n", P->firstname, P->lastname, P->birthYear);
		P = P->Next;
	}*/
	fclose(fp);
	return 0;
}
int deleteAll(Position P) {
	Position temp=NULL;
	while (P->Next != NULL) {
		temp = P->Next;
		P->Next = temp->Next;
		free(temp);
	}
	return 0;
}
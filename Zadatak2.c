#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BROJ_ZNAKOVA (20)
#define ERROR (-1)

struct _Osoba;
typedef struct _Osoba* position;

typedef struct _Osoba
{
	char Ime[MAX_BROJ_ZNAKOVA];
	char Prezime[MAX_BROJ_ZNAKOVA];
	int GodRodenja;

	position Next;

}Osoba;

void UnesiPodatkeUStrukturu(position p);
int DodajNaPocetakListe(position p);
int IspisiListu(position p);
int DodajNaKrajListe(position p);
position PronadiElementListe(position p, char* Prezime);
int IzbrisiElementListe(position p, char* Prezime);

int main(void) {
	int BrOsoba = 0;
	int BrOsobaK = 0; 
	int i = 0;
	char Prezime[MAX_BROJ_ZNAKOVA];
	position q = NULL;
	
	position Head = NULL;
	Head = (position)malloc(sizeof(Osoba));
	Head->Next = NULL;

	printf("Koliko osoba zelite upisati na pocetak liste: ");
	scanf("%d", &BrOsoba);

	for (i = 0; i < BrOsoba; i++) {
		DodajNaPocetakListe(Head);
	}

	printf("Ispis liste nakon upisa na pocetak:\n");
	IspisiListu(Head->Next); 

	printf("Koliko osoba zelite upisati na kraj liste: ");
	scanf("%d", &BrOsobaK);

	for (i = 0; i < BrOsobaK; i++) {
		DodajNaKrajListe(Head);
	}

	printf("Ispis liste nakon upisa na kraj:\n");
	IspisiListu(Head->Next);

	printf("Koje prezime zelite pronaci: ");
	scanf(" %s", Prezime);
	q= PronadiElementListe(Head, Prezime);
	printf("Ime, prezime i godina rođenja osobe: %s, %s, %d", q->Ime, q->Prezime, q->GodRodenja);
	

	printf("\nKoje prezime zelite izbrisati: ");
	scanf(" %s", Prezime);
	IzbrisiElementListe(Head, Prezime);

	printf("Ispis liste nakon brisanja elementa:\n");
	IspisiListu(Head->Next);
	
	return 0;

}

void UnesiPodatkeUStrukturu(position p) {
		
	printf("Upisite ime osobe, prezime i godinu rodenja: ");
	scanf(" %s %s %d", p->Ime, p->Prezime, &p->GodRodenja);
}

int DodajNaPocetakListe(position p) {
	
	position q = NULL;
	q = (position)malloc(sizeof(Osoba));
	if (q == NULL)
		return ERROR;
	UnesiPodatkeUStrukturu(q);
	q->Next = p->Next;
	p->Next = q;
	return 0;
}

int IspisiListu(position p) {

	if (p == NULL) {
		printf("Lista je prazna.");
		return ERROR;
	}
	while (p != NULL) {
		printf("%s\t%s\t%d\n", p->Ime, p->Prezime, p->GodRodenja);
		p = p->Next;
	}
	return 0;
}

int DodajNaKrajListe(position p) {
	
	position q = NULL; 
	q = (position)malloc(sizeof(Osoba));
	if (q == NULL)
		return ERROR;
	UnesiPodatkeUStrukturu(q);
	while (p->Next != NULL) {
		p = p->Next;
	}
	p->Next = q;
	q->Next = NULL;
	
	return 0;
}

position PronadiElementListe(position p, char* Prezime) {

	while (p != NULL && strcmp(p->Prezime, Prezime) != 0) 
		p = p->Next;
	if (p == NULL)
		return ERROR;
	return p;
}

int IzbrisiElementListe(position p, char* Prezime) {
	position Prethodni = NULL;
	position Trenutni = NULL;
	Trenutni = p;
	Prethodni = Trenutni->Next;
	while (Trenutni != NULL && strcmp(Trenutni->Prezime, Prezime) != 0){
		Prethodni = Trenutni;
		Trenutni = Prethodni->Next;
	}
	if (Trenutni == NULL)
		return ERROR;
	Prethodni->Next = Prethodni->Next->Next;
	free(Trenutni);
	return 0;
}
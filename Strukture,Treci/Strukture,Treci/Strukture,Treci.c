#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _lista;
typedef struct _lista* position;

typedef struct _lista
{
	char ime[50];
	char prezime[50];
	int godina;
	position next;
} lista;

int UnosP(position);
void UnesiPod(position);
int Ispis(position);
int UnosK(position);
int Pretrazi(position);
int Brisanje(position);
position PronadiPosljednji(position);
int UnosIza(position);
int UnosIspred(position);
void Sort(position);
void UnosDat(position);
void IspisDat(position);

int main()
{
	int izbor = 0;
	int element = 0;
	struct _lista head;
	head.next = NULL;
	char ime[50] = { 0 };
	char prezime[50] = { 0 };
	int godina = 0;


	while (izbor != '0')
	{
		printf("\nOdaberi '1' za Unos elementa na pocetak liste:\nOdaberi '2' za ispis liste:\nOdaberi '3' za dodati na kraj liste:\nOdaberi '4' za pronalazak elementa u listi po prezimenu\n");
		printf("Odaberi '5' za brisanje elementa\nOdaberi '6' za dodavanje elementa iza odredenog elementa\nOdaberi '7' za dodavanje elemnta ispred odredenog elementa\nOdaberi '8' za unos u datoteku\nOdaberi '9' za ispis datoteke\nOdaberi '10' za sortitanje liste \nOdaberi '0' za kraj programa\n");
		scanf(" %c", &izbor);
		switch (izbor)
		{
		case '1':

			UnosP(&head);
			Ispis(head.next);
			break;

		case '2':
			Ispis(head.next);
			break;

		case '3':
			UnosK(&head);
			break;

		case '4':
			Pretrazi(&head);
			break;

		case '5':
			Brisanje(&head);
			break;

		case '6':
			UnosIza(&head);
			break;

		case '7':
			UnosIspred(&head);
			break;

		case '8':
			UnosDat(head.next);
			break;

		case '9':
			IspisDat(head.next);
			break;
		case '10':
			Sort(head.next);
			break;
		case '0':
			printf("\nKraj programa.\n");
			break;
		default:
			printf("\nKrivi unos.\n");
		}

	}
	return 0;


}

int UnosP(position p)
{
	position q = NULL;
	q = (position)malloc(sizeof(struct _lista));
	if (q == NULL)
	{
		return -1;
	}
	else
	{
		UnesiPod(q);
		q->next = p->next;
		p->next = q;
	}
	return 0;
}

void UnesiPod(position p)
{
	printf("\nUnesi ime:\n");
	scanf(" %s", p->ime);

	printf("\nUnesi prezime:\n");
	scanf(" %s", p->prezime);

	printf("\nUnesi godinu rodenja:\n");
	scanf("%d", &p->godina);

	return;
}

int Ispis(position p)
{
	if (p == NULL)
	{
		printf("\nLista je prazna\n");
		return -1;
	}

	else
	{
		while (p != NULL)
		{
			printf("\n%s %s %d\n", p->ime, p->prezime, p->godina);
			p = p->next;
		}

	}
	return 0;
}

position PronadiPosljednji(position p)
{
	while (p->next != NULL)
	{
		p = p->next;
	}

	return p;
}

int UnosK(position p)
{
	position last = NULL;
	last = PronadiPosljednji(p);
	UnesiPod(last);

	return 0;
}

int Pretrazi(position p)
{
	p = p->next;
	char trazen[50];
	printf("Unesite trazeno prezime:\n");
	scanf(" %s", &trazen);

	while (p != NULL)
	{
		if (strcmp(trazen, p->prezime) == 0)
		{
			printf("Prezime postoji u listi\n");
			return 0;
		}
		p = p->next;
	}
	printf("Prezime ne postoji u listi.");
	return 0;
}
int Brisanje(position p)
{
	int n = 0;
	lista* temp = NULL;
	printf("Koji element zelite obrisati?\n");
	scanf("%d", &n);

	for (int i = 0; i < (n - 1); i++)
	{
		p = p->next;
	}

	temp = p->next;
	p->next = temp->next;
	free(temp);
	printf("element je izbrisan\n");
	return 0;
}

int UnosIza(position p)
{
	int n = 0;
	lista* temp = NULL;
	temp = (lista*)malloc(sizeof(lista));
	printf("Unesi na koje mjesto cemo element ubaciti:\n");
	scanf("%d", &n);

	for (int i = 0; i < (n - 1); i++)
	{
		p = p->next;
	}

	temp->next = p->next;
	p->next = temp;

	UnesiPod(temp);
}

int UnosIspred(position p)
{
	int n = 0;
	lista* temp = NULL;
	temp = (lista*)malloc(sizeof(lista));
	printf("Unesi na koje mjesto cemo element ubaciti:\n");
	scanf("%d", &n);

	for (int i = 0; i < n; i++)
	{
		p = p->next;
	}

	temp->next = p->next;
	p->next = temp;

	UnesiPod(temp);
}
void UnosDat(position p)
{
	FILE* f;
	f = fopen("studenti.txt", "w");

	if (f == NULL)
	{
		printf("Greska!Datoteka ne postoji.\n");
		return -1;
	}
	else
	{
		while (p != NULL)
		{
			fprintf(f, "%s\t%s\t%d\n", p->ime, p->prezime, p->godina);
			p = p->next;
		}
	}
	fclose(f);
	return;
}
void IspisDat(position p)
{
	position q = NULL;

	int i = 0;
	FILE* f;
	f = fopen("st.txt", "r");



	if (f == NULL)
	{
		printf("GRESKA!Datoteka ne postoji.\n");
		
	}

	else
	{
		while (feof(f) == 0)
		{
			q = (position)malloc(sizeof(struct _lista));
			fscanf(f, "%s %s %d", q->ime, q->prezime, &q->godina);
			printf("%s\t%s\t%d\n", q->ime, q->prezime, q->godina);
			q->next = p->next;
			p->next = q;
			p = q;

		}

	}
	fclose(f);
	return;
}

void Sort(position p)
{
	position q, prev_q, temp, end;

	end = NULL;
	while (p->next != end)
	{
		prev_q = p;
		q = p->next;
		while (q->next != end)
		{
			if (strcmp(prev_q->prezime, q->prezime) < 0)
			{
				temp = q->next;
				prev_q->next = temp;
				q->next = temp->next;
				temp->next = q;

				q = temp;
			}

			prev_q = q;
			q = q->next;

		}
		end = q;
	}
	printf("lista je sortirana!");
}

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define MAX_SIZE (50)
#define MAX_LINE (1024)
#define ERROR (-1)

struct _Polinom;
typedef struct _Polinom* Pozicija;
typedef struct _Polinom {
	int koeficijent;
	int eksponent;
	Pozicija next;
}Polinom;

int ProcitajIzDatoteke(Pozicija, Pozicija, char*);
Pozicija NoviElement(int, int);
int DodajUListu(Pozicija, char*);
void SortiraniUnos(Pozicija, Pozicija);
int IzbrisiIza(Pozicija p);
void Zbroji(Pozicija, Pozicija, Pozicija);

int main() {
	Polinom head1 = { .koeficijent = 0, .eksponent = 0, .next = NULL };
	Polinom head2 = { .koeficijent = 0, .eksponent = 0, .next = NULL };
	Polinom rez_zbrajanja = { .koeficijent = 0, .eksponent = 0, .next = NULL };
	Polinom rez_mnozenja = { .koeficijent = 0, .eksponent = 0, .next = NULL };
	char ime_datoteke[MAX_SIZE] = { 0 };

	printf("Upisite ime datoteke iz koje zelite procitati polinom:");
	scanf(" %s", ime_datoteke);
}

int ProcitajIzDatoteke(Pozicija head1, Pozicija head2, char* datoteka) {
	FILE* f = NULL;
	char buffer[MAX_LINE] = { 0 };
	int s = 0; 

	f = fopen(datoteka, "r");
	if (!f)
	{
		printf("\nGreska u otvaranju datoteke!");
		return ERROR;
	}
	fgets(buffer, MAX_LINE, f);
	s = DodajUListu;
	if (s != 0)
	{
		return EXIT_FAILURE;
	}
	fgets(buffer, MAX_LINE, f);
	s = DodajNaListu(head2, buffer);
	if (s != 0)
	{
		return ERROR;
	}

	return 0;
}
Pozicija NoviElement(int koeficijent, int eksponent) {
	Pozicija novi_element = NULL;
	novi_element = (Pozicija)malloc(sizeof(Polinom));
	if (novi_element == NULL) {
		printf("\nGreska u alociranju memorije!");
		return NULL;
	}
	novi_element->koeficijent = koeficijent;
	novi_element->eksponent = eksponent;
	novi_element->next = NULL;
	return novi_element;
}
int DodajUListu(Pozicija head, char* buffer) {
	int koef = 0;
	int eksp = 0;
	int num = 0;
	int s = 0;
	Pozicija element = NULL;
	while (strlen(buffer) > 0) {
		s = sscanf(temp_buffer, "%d %d %n", &temp_koef, &temp_eksp, &num);
		if (s != 2) {
			printf("\nGreška u sadrzaju datoteke!");
			return ERROR;
		}
		buffer = NoviElement(koef, eksp);
		SortiraniUnos(head, element);
		buffer = buffer + num;
	}
	return 0;
}
void SortiraniUnos(Pozicija p, Pozicija element) {
	Pozicija q = element;
	while (p->next!=NULL && p->next->eksponent != element->eksponent)
	{
		p=p->next:
	}
	if (p->next == NULL || p->next->eksponent != element->eksponent) {
		element->next = p->next;
		p->next = element;
	}
	else
	{
		int a = p->next->koeficijent + element->koeficijent;
		if (a == 0)
		{
			IzbrisiIza(p);
		}
		else
		{
			p->next->koeficijent = a;
		}
		free(element);
	}
}
int IzbrisiIza(Pozicija p)
{
	Pozicija tr = p->next;

	p->next = tr->next;
	free(tr);

	return 0;
}
void Zbroji(Pozicija suma, Pozicija p1, Pozicija p2) {
	Pozicija tmp;
	while (p1 != NULL && p2 != NULL) {
		if (p1->eksponent == p2->eksponent) {
			SortiraniUnos(suma, p1->Koef + p2->Koef, p1->Pot);
			p1 = p1->Next; p2 = p2->Next;
		}
		else if (p1->Pot > p2->Pot) {
			unos(S, p1->Koef, p1->Pot); p1 = p1->Next;
		}
		else {
			unos(S, P2->Koef, P2->Pot); P2 = P2->Next;
		}
	}
	if (P1 != NULL) tmp = P1;
	else tmp = P2;
	while (tmp != NULL) {
		unos(S, tmp->Koef, tmp->Pot);
		tmp = tmp->Next;
	}

}
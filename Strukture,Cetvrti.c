#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR -1
#define MAX_LINE 1024 


struct _broj;
typedef struct _broj* position;

typedef struct _broj
{
	int eksponent;
	int koeficijent;

	position next;
}broj;

int CitanjeIzDat(position, position, char*);
int Ispisivanje(position);
int Zbroj(position, position, position);
int Umnozak(position, position, position);
int Unos(char*, position);
position Stvaranje(int, int);
int SortiraniUnos(position, position);
int Brisanje(position, position);
position Trazi(position, position);
int UnosIza(position, position);

int main()
{
	broj head1;
	head1.next = NULL;
	position pol1 = &head1;
	broj head2;
	head2.next = NULL;
	position pol2 = &head2;


	char imeDat[] = "lista.txt";
	CitanjeIzDat(pol1, pol2, imeDat);

	printf("1. polinom:\n");
	Ispisivanje(pol1->next);

	printf("2. polinom:\n");
	Ispisivanje(pol2->next);

	broj head3;
	head3.next = NULL;
	position pol3 = &head3;

	broj head4;
	head4.next = NULL;
	position pol4 = &head4;

	Zbroj(pol1, pol2, pol3);
	printf("\nZbroj polinoma:\n");
	Ispisivanje(pol3->next);


	return 0;


}

int CitanjeIzDat(position p1, position p2, char* ime)
{
	char buffer1[MAX_LINE] = { 0 };
	char buffer2[MAX_LINE] = { 0 };

	FILE* f = NULL;
	f = fopen(ime, "r");

	if (!f) {
		printf("Datoteka ne postoji\r\n", ime);
		return ERROR;
	}

	fgets(buffer1, MAX_LINE, f);
	unesiPolinom(buffer1, p1);

	fgets(buffer2, MAX_LINE, f);
	unesiPolinom(buffer2, p2);

	fclose(f);

	return EXIT_SUCCESS;

}

int Unos(char* buff, position head)
{
	int pomak = 0, koef = 0, eksp = 0, n = 0;
	position temp = NULL;

	while (buff[pomak] != '\0')
	{
		int result = sscanf(buff + pomak, " %d %d %n", &koef, &eksp, &n);
		pomak += n;


		temp = Stvaranje(koef, eksp);
		if (!temp)
		{
			return ERROR;
		}

		SortiraniUnos(temp, head);
	}
	return EXIT_SUCCESS;

}

position Stvaranje(int koef, int eksp)
{
	position polinom = NULL;
	polinom = (position)malloc(sizeof(position));

	if (!polinom)
	{
		return ERROR;
	}

	polinom->eksponent = eksp;
	polinom->koeficijent = koef;
	polinom->next = NULL;

	return polinom;
}

int SortiraniUnos(position element, position head)
{
	position temp = head->next;
	position prethodni = NULL;

	while ((temp != NULL) && (element->eksponent) < (temp->eksponent))
	{
		temp = temp->next;
	}

	if ((temp != NULL) && (element->eksponent == temp->eksponent))
	{
		if (temp->koeficijent + element->koeficijent)
		{
			temp->koeficijent = temp->koeficijent + element->koeficijent;
		}
		else
		{
			Brisanje(temp, head);
			free(element);
		}
	}
	else {
		prethodni = Trazi(head, temp);
		UnosIza(prethodni, element);
	}

	return EXIT_SUCCESS;
}

int Brisanje(position tmp, position head)
{
	position temp = NULL;
	temp = Trazi(head, tmp);
	temp->next = tmp->next;
	free(tmp);

	return EXIT_SUCCESS;
}

position Trazi(position head, position tmp)
{
	position temp = head;
	while (temp->next != tmp)
	{
		temp = temp->next;
	}

	return temp;
}

int UnosIza(position prev, position tmp)
{
	tmp->next = prev->next;
	prev->next = tmp;

	return EXIT_SUCCESS;
}

int Ispisivanje(position head)
{
	position temp = head;
	printf("\n");
	while (temp != NULL)
	{
		printf("\t%dX^%d\n", temp->koeficijent, temp->eksponent);
		temp = temp->next;
	}

	return EXIT_SUCCESS;
}

int Zbroj(position p1, position p2, position zbroj)
{
	position temp = NULL;
	position ostali = NULL;
	while (p1 && p2)
	{
		if (p1->eksponent == p2->eksponent)
		{
			temp = Stvaranje(p1->koeficijent + p2->koeficijent, p1->eksponent);
			SortiraniUnos(temp, zbroj);
			p1 = p1->next;
			p2 = p2->next;
		}
		else if ((p1->eksponent) > (p2->eksponent))
		{
			temp = Stvaranje(p1->koeficijent, p1->eksponent);
			SortiraniUnos(temp, zbroj);
			p1 = p1->next;
		}
		else if ((p1->eksponent) < (p2->eksponent))
		{
			temp = Stvaranje(p2->koeficijent, p2->eksponent);
			SortiraniUnos(temp, zbroj);
			p2 = p2->next;
		}



	}
	if (p1 && p2 == NULL)
	{
		while (p1->next)
		{

			ostali = Stvaranje(p1->koeficijent, p1->eksponent);
			SortiraniUnos(ostali, zbroj);
			p1 = p1->next;

		}
	}
	else if (p2 && p1 == NULL)
	{
		while (p2->next)
		{
			ostali = Stvaranje(p2->koeficijent, p2->eksponent);
			SortiraniUnos(ostali, zbroj);
			p2 = p2->next;
		}
	}
	return EXIT_SUCCESS;
}
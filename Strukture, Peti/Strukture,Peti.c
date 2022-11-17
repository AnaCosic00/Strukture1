#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define ERROR -1
#define MAX_LINE 1024

struct _Stog;
typedef struct _Stog* position;
typedef struct _Stog {
	double broj;
	position next;
} Stog;

int IzracunajRezultat(double*, char*);
int Push(position, double);
position StvoriNoviElement(double);
int UmetniNakon(position, position);
int IzvrsiOperaciju(position, char);
int Pop(double*, position);
int IzbrisiNakon(position);

int main() {
	double rezultat = 0;
	if (IzracunajRezultat(&rezultat, "postfix.txt") == EXIT_SUCCESS)
	{
		printf("Rezultat: %0.1lf", rezultat);
	}
	else
	{
		printf("Greska!");
		return ERROR;
	}
	return 0;
	
}

int IzracunajRezultat(double* rezultat, char* ime_datoteke) {
	
	char buffer[MAX_LINE] = { 0 };
	int pomak = 0;
	double broj = 0;
	int n = 0;
	char operacija = 0;
	int status = 0;
	Stog head = { .broj = 0, .next = NULL };
	FILE* f = NULL;
	f = fopen(ime_datoteke, "r");
	if (!f) {
		printf("Datoteka %s nije se otvorila", ime_datoteke);
		return ERROR;
	}

	fgets(buffer, MAX_LINE, f);
	while (buffer[pomak] != '\0') {
		status = sscanf(buffer + pomak, "%lf %n", &broj, &n);
		if (status == 1) {
			Push(&head, broj);
			pomak += n;
		}
		else {
			sscanf(buffer + pomak, "%c %n", &operacija, &n);
			status = IzvrsiOperaciju(&head, operacija);
			if (status != EXIT_SUCCESS) {
				while (head.next != NULL)
					IzbrisiNakon(&head);
				return ERROR;
			}
			pomak += n;
		}
		
	}
	status = Pop(rezultat, &head);
	if (status != EXIT_SUCCESS)
	{
		while (head.next != NULL)
		{
			IzbrisiNakon(&head);
		}
		return ERROR;
	}

	return EXIT_SUCCESS;

}
int Push(position head, double broj) {
	position novi_element = NULL;
	novi_element = StvoriNoviElement(broj);
	if (!novi_element)
	{
		return ERROR;
	}

	UmetniNakon(head, novi_element);
	return EXIT_SUCCESS;
}
position StvoriNoviElement(double br)
{
	position novi_element;

	novi_element = (position)malloc(sizeof(Stog));
	if (!novi_element)
	{
		printf("Memorija nije alocirana!\n");
		return ERROR;
	}
	novi_element->broj = br;
	novi_element->next = NULL;

	return novi_element;
}
int UmetniNakon(position s, position novi_element)
{
	novi_element->next = s->next;
	s->next = novi_element;

	return EXIT_SUCCESS;
}
int IzvrsiOperaciju(position head, char operacija) {
	double operand1 = 0;
	double operand2 = 0;
	int status1 = EXIT_SUCCESS;
	int status2 = EXIT_SUCCESS;
	double rezultat = 0;

	status2 = Pop(&operand2, head);
	if (status2 != EXIT_SUCCESS)
	{
		return ERROR;
	}

	status1 = Pop(&operand1, head);
	if (status1 != EXIT_SUCCESS)
	{
		return ERROR;
	}
	switch (operacija)
	{
	case '+':
	{
		rezultat = operand1 + operand2;
		break;
	}
	case '-':
	{
		rezultat = operand1 - operand2;
		break;
	}
	case '*':
	{
		rezultat = operand1 * operand2;
		break;
	}
	case '/':
	{
		if (operand2 == 0)
		{
			printf("Ne moze se dijeliti s 0!\n");
			return ERROR;
		}
		rezultat = operand1 / operand2;
		break;
	}
	default:
		printf("Operacija se ne moze izvrsiti!\n");
		return ERROR;
	}
	Push(head, rezultat);

	return EXIT_SUCCESS;
}
int Pop(double* br, position head)
{
	position prvi = head->next;
	if (!prvi)
	{
		return ERROR;
	}
	*br = prvi->broj;
	IzbrisiNakon(head);

	return EXIT_SUCCESS;
}
int IzbrisiNakon(position s)
{
	position temp = s->next;
	if (!temp)
	{
		return EXIT_SUCCESS;
	}

	s->next = temp->next;
	free(temp);

	return EXIT_SUCCESS;
}

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_DIDNT_OPEN_ERROR (-1)
#define MAX_LINE (1024)
#define MAX_FILE_NAME (256)

typedef struct
{
	char ime[20];
	char prezime[20];
	int bodovi;
}Student;

int BrojacStudenata(char* datoteka);
void UnosStudenata(int, Student*, char* datoteka);
void IspisStudenata(int, Student*, int);


int main(void) {
	char datoteka[MAX_FILE_NAME] = { 0 };
	int BrStudenata = 0, maxBrojBodova = 0;
	Student* s;

	printf("Upisite ime datoteke: ");
	scanf(" %s", datoteka);

	BrStudenata = BrojacStudenata(datoteka);
	printf("U datoteci postoji %d studenata.\n", BrojacStudenata(datoteka));

	printf("Upisite maksimalni broj bodova: ");
	scanf(" %d", &maxBrojBodova);

	s = (Student*)malloc(BrStudenata * sizeof(Student));

	UnosStudenata(BrStudenata, s, datoteka);
	IspisStudenata(BrStudenata, s, maxBrojBodova);

	return 0;
}

int BrojacStudenata(char* datoteka) {
	FILE* fp = NULL;
	int brojac = 0;
	char buffer[MAX_LINE] = { 0 };

	fp = fopen(datoteka, "r");
	if (fp == NULL) {
		printf("Datoteka %s se nije otvorila. \r\n", datoteka);
		return FILE_DIDNT_OPEN_ERROR;
	}

	while (fgets(buffer, MAX_LINE, fp)) {
		if (strcmp("\n", buffer) != 0) {
			brojac++;
		}
	}
	fclose(fp);
	return brojac;
}

void UnosStudenata(int BrojS, Student* s, char* datoteka) {
	int i = 0;
	FILE* fp = NULL;

	fp = fopen(datoteka, "r");
	if (fp == NULL) {
		printf("Datoteka %s se nije otvorila. \r\n", datoteka);
		return FILE_DIDNT_OPEN_ERROR;
	}

	for (i = 0; i < BrojS; i++) {
		fscanf(fp, " %s", s[i].ime);
		fscanf(fp, " %s", s[i].prezime);
		fscanf(fp, " %d", &s[i].bodovi);
	}

	fclose(fp);
	return;
}

void IspisStudenata(int BrojS, Student* s, int max) {
	int i = 0;

	for (i = 0; i < BrojS; i++) {
		printf("%s\t%s\t%d\t%f\n", s[i].ime, s[i].prezime, s[i].bodovi, (float)s[i].bodovi / max * 100);
	}
}
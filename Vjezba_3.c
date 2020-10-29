#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define IME_PREZIME_MAX 50

typedef struct Osoba
{
	char ime[IME_PREZIME_MAX];
	char prezime[IME_PREZIME_MAX];
	int godina;
	struct Osoba* next;
}Osoba;

Osoba* Nova_Osoba(char* ime, char* prezime, int godina)
{
	Osoba* nova = (Osoba*)malloc(sizeof(Osoba));
	strcpy(nova->ime, ime);
	strcpy(nova->prezime, prezime);
	nova->godina = godina;
	nova->next = NULL;
	return nova;
}

void Na_Pocetak(Osoba* dummy, Osoba* nova)
{
	nova->next = dummy->next;
	dummy->next = nova;
}

void Dodaj_Nakon(Osoba* dummy, Osoba* nakon_mene, Osoba* nova)
{
	Osoba* tmp = dummy->next;
	while(tmp != nakon_mene)
	{
		tmp = tmp->next;
	}
	Osoba* od_nakon = tmp->next;
	tmp->next = nova;
	nova->next = od_nakon;
}

void Dodaj_Ispred(Osoba* dummy, Osoba* prije_mene,Osoba* nova)
{
	Osoba* tmp = dummy->next;
	while (tmp->next != prije_mene)
	{
		tmp = tmp->next;
	}
	Osoba* od_nakon = tmp->next;
	tmp->next = nova;
	nova->next = od_nakon;
}

void Na_Kraj(Osoba* dummy, Osoba* nova)
{
	Osoba* tmp = NULL;
	tmp = dummy->next;
	while(tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = nova;
}

void Ispis_Liste(Osoba* dummy)
{
	Osoba* tmp = NULL;
	tmp = dummy->next;
	while(tmp != NULL)
	{
		printf("%s %s %d\n", tmp->ime, tmp->prezime, tmp->godina);
		tmp = tmp->next;
	}
}

Osoba* Trazi_Po_Prezimenu(Osoba* dummy, char* prezime)
{
	Osoba* tmp = dummy->next;
	while(tmp->next != NULL)
	{
		if(strcmp(tmp->prezime, prezime) == 0)
		{
			return tmp;
		}
		tmp = tmp->next;
	}
	return NULL;
}

void Izbrisi(Osoba* dummy, Osoba* stara)
{
	Osoba* tmp = NULL;
	Osoba* prev = NULL;
	tmp = dummy->next;
	prev = dummy;
	while(tmp != stara)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	prev->next = tmp->next;
	free(stara);
}

void Upisi_U_File(Osoba* dummy)
{
	FILE* data;
	data = fopen("Studenti.txt", "w");
	if(data == NULL)
	{
		printf("\nGreska prilikom otvaranja.\n");
	}
	else
	{
		Osoba* tmp = NULL;
		tmp = dummy->next;
		while(tmp != NULL)
		{
			fprintf(data, "%s %s %d\n", tmp->ime, tmp->prezime, tmp->godina);
			tmp = tmp->next;
		}
		fclose(data);
	}
}

void Sort_Unos(Osoba* dummy, Osoba* nova)
{
	
}

void Ucitaj_Iz_Filea(const char* filename, Osoba* dummy)
{
	int student_count = 0;
	FILE* data;
	data = fopen(filename, "r");
	if(data == NULL)
	{
		printf("\nGreska prilikom otvaranja.\n");
	}
	else
	{
		char temp = '\0';
		while(feof(data) != 1)
		{
			temp = fgetc(data);
			if (temp == '\n')
			{
				student_count++;
			}
		}
		rewind(data);
		int tmp = 0;
		for(int i = 0; i < student_count; i++)
		{
			char ime[50];
			char prezime[50];
			int godina = 0;
			tmp = fscanf(data, "%s %s %d", ime, prezime, & godina);
			Sort_Unos(dummy, Nova_Osoba(ime, prezime, godina));
		}
		fclose(data);
	}
}

int main()
{
	Osoba dummy;
	dummy.next = NULL;
	Na_Pocetak(&dummy, Nova_Osoba("Pero", "Peric", 1991));
	Na_Pocetak(&dummy, Nova_Osoba("Jure", "Juric", 1992));
	Na_Kraj(&dummy, Nova_Osoba("Marko", "Markic", 2000));
	Na_Pocetak(&dummy, Nova_Osoba("Ivo", "Ivic", 2003));
	Na_Kraj(&dummy, Nova_Osoba("Boris", "Borisovic", 2004));
	Na_Pocetak(&dummy, Nova_Osoba("Siljo", "Siljic", 2001));
	Ispis_Liste(&dummy);
	Izbrisi(&dummy, Trazi_Po_Prezimenu(&dummy, "Markic"));
	printf("\n");
	Dodaj_Nakon(& dummy, Trazi_Po_Prezimenu(& dummy, "Juric"), Nova_Osoba("Ante", "Antic", 2000));
	Ispis_Liste(&dummy);
	printf("\n");
	Dodaj_Ispred(&dummy, Trazi_Po_Prezimenu(&dummy, "Antic"), Nova_Osoba("Haso", "Hasic", 2005));
	Ispis_Liste(&dummy);
	Upisi_U_File(&dummy);
	Ucitaj_Iz_Filea("Studenti.txt", & dummy);
	Ispis_Liste(&dummy);
	printf("\n");
	system("pause");
	return 0;
}

/*
int main()
{
	student* studenti;
	FILE* text_file;
	int student_count = 0;
	text_file = fopen("Studenti.txt", "r");
	if(text_file == NULL)
	{
		printf("\nGreska pri otvaranju!\n");
	}
	else
	{
		char temp = '\0';
		while(feof(text_file) != 1)
		{
			temp = fgetc(text_file);
			if (temp == '\n')
			{
				student_count++;
			}
		}
		printf("Nasli smo: %d studenata.\n", student_count);
		studenti = (student*) malloc (sizeof(student) * student_count);
		if(studenti == NULL)
		{
			printf("Nema memorije vise!");
		}
		else
		{
			rewind(text_file);
			int tmp = 0;
			for (int i = 0; i < student_count; i++)
			{
				tmp = fscanf(text_file, "%s %s %d", studenti[i].ime, studenti[i].prezime, & studenti[i].broj_bodova);
				printf("Student: %s %s BB Apsolutno: %d BB Relativno: %f\n", studenti[i].ime, studenti[i].prezime, studenti[i].broj_bodova, (float) studenti[i].broj_bodova / (MAX_BB * 100));
			}
			free(studenti);
			fclose(text_file);
		}
	}
	return 0;
}*/
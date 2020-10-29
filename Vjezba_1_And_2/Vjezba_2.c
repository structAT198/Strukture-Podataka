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
	Osoba* nova = (Osoba*) malloc(sizeof(Osoba));
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

int main()
{
	Osoba dummy;
	dummy.next = NULL;
	Na_Pocetak(& dummy, Nova_Osoba("Pero", "Peric", 1991));
	Na_Pocetak(& dummy, Nova_Osoba("Jure", "Juric", 1992));
	Na_Kraj(& dummy, Nova_Osoba("Marko", "Markic", 2000));
	Na_Pocetak(& dummy, Nova_Osoba("Ivo", "Ivic", 2003));
	Na_Kraj(& dummy, Nova_Osoba("Boris", "Borisovic", 2004));
	Na_Pocetak(& dummy, Nova_Osoba("Siljo", "Siljic", 2001));
	Ispis_Liste(& dummy);
	Izbrisi(& dummy, Trazi_Po_Prezimenu(& dummy, "Markic"));
	printf("\n\n");
	Ispis_Liste(&dummy);
	return 0;
}
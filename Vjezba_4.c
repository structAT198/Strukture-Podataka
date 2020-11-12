#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct Polinom
{
	int coefficient;
	int exponent;
	struct Polinom* next;
}Polinom;

Polinom* Nova_Polinom(int coefficient, int exponent)
{
	Polinom* novi = (Polinom*) malloc(sizeof(Polinom));
	novi->coefficient = coefficient;
	novi->exponent = exponent;
	novi->next = NULL;
	return novi;
}

void Na_Pocetak(Polinom* dummy, Polinom* nova)
{
	nova->next = dummy->next;
	dummy->next = nova;
}

void Dodaj_Nakon(Polinom* dummy, Polinom* nakon_mene, Polinom* nova)
{
	Polinom* tmp = dummy->next;
	while(tmp != nakon_mene)
	{
		tmp = tmp->next;
	}
	Polinom* od_nakon = tmp->next;
	tmp->next = nova;
	nova->next = od_nakon;
}

void Dodaj_Ispred(Polinom* dummy, Polinom* prije_mene, Polinom* nova)
{
	Polinom* tmp = dummy->next;
	while(tmp->next != prije_mene)
	{
		tmp = tmp->next;
	}
	Polinom* od_nakon = tmp->next;
	tmp->next = nova;
	nova->next = od_nakon;
}

void Na_Kraj(Polinom* dummy, Polinom* nova)
{
	Polinom* tmp = NULL;
	tmp = dummy->next;
	while(tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = nova;
}

void Ispis_Liste(Polinom* dummy)
{
	Polinom* tmp = dummy->next;
	while(tmp != NULL)
	{
		printf("%dX^%d ", tmp->coefficient, tmp->exponent);
		tmp = tmp->next;
	}
}

void Sort_Unos(Polinom* dummy, Polinom* nova)
{
    if(dummy->next->exp >= nova->exp)
    {
        nova->next = dummy->next->next;
        dummy = nova;
        return;
    }
    Polinom* tmp = dummy->next;
    while(tmp->next != NULL && tmp->next->exp < nova->exp)
    {
        tmp = tmp->next;
    }
    nova->next = tmp->next;
    tmp->next = nova;
}

void Ucitaj_Polinom(const char* filename, Polinom* dummy)
{
	FILE* polinom = fopen(filename, "r");
	if(polinom == NULL)
	{
		printf("\nFATAL ERROR! Nema polinoma!");
	}
	else
	{
		Polinom* temp = (Polinom*) malloc(sizeof(Polinom));
		int tmp = 0;
		while(feof(polinom) != 1)
		{
			tmp = fscanf(polinom, "%d %d", & temp->coefficient, & temp->exponent);
			Unesi_Sortirano(dummy, temp);
		}
	}
}

void Dodaj_Polinome(Polinom* first, Polinom* second, Polinom* rezultat)
{
    while(first->next && next->next) 
	{
		if(first->exp > second->exp) 
		{ 
			rezultat->exp = first->exp; 
			rezultat->coefficient = first->coefficient; 
			first = first->next; 
		}
		else if(first->exp < second->exp) 
		{ 
			rezultat->exp = second->exp; 
			rezultat->coefficient = second->coefficient; 
			second = second->next; 
		}
		else
		{ 
			rezultat->exp = first->exp; 
			rezultat->coefficient = first->coefficient + second->coefficient; 
			first = first->next; 
			second = second->next; 
		}
		rezultat->next = (Polinom*) malloc(sizeof(Polinom)); 
		rezultat = rezultat->next; 
		rezultat->next = NULL; 
	} 
    while(first->next || second->next) 
	{ 
		if(first->next) 
		{ 
			rezultat->exp = first->exp; 
			rezultat->coefficient = first->coefficient; 
			first = first->next; 
		} 
		if(second->next) 
		{ 
			rezultat->exp = second->exp; 
			rezultat->coefficient = second->coefficient; 
			second = second->next; 
		} 
		rezultat->next = (Polinom*) malloc(sizeof(Polinom); 
		rezultat = rezultat->next; 
		rezultat->next = NULL; 
	} 
}

void Mnozi_Polinome(Polinom* first, Polinom* second, Polinom* rezultat)
{
    while(first->next && next->next) 
	{
		if(first->exp > second->exp) 
		{ 
			rezultat->exp = first->exp; 
			rezultat->coefficient = first->coefficient; 
			first = first->next; 
		}
		else if(first->exp < second->exp) 
		{ 
			rezultat->exp = second->exp; 
			rezultat->coefficient = second->coefficient; 
			second = second->next; 
		}
		else
		{ 
			rezultat->exp = first->exp; 
			rezultat->coefficient = first->coefficient * second->coefficient; 
			first = first->next; 
			second = second->next; 
		}
		rezultat->next = (Polinom*) malloc(sizeof(Polinom)); 
		rezultat = rezultat->next; 
		rezultat->next = NULL; 
	} 
    while(first->next || second->next) 
	{ 
		if(first->next) 
		{ 
			rezultat->exp = first->exp; 
			rezultat->coefficient = first->coefficient; 
			first = first->next; 
		} 
		if(second->next) 
		{ 
			rezultat->exp = second->exp; 
			rezultat->coefficient = second->coefficient; 
			second = second->next; 
		} 
		rezultat->next = (Polinom*) malloc(sizeof(Polinom); 
		rezultat = rezultat->next; 
		rezultat->next = NULL; 
	} 
}

int main()
{
	Polinom prvi;
	Polinom drugi;
	prvi.next = NULL;
	drugi.next = NULL;
	Ucitaj_Polinom("Polinom_1.txt", & prvi);
	Ispis_Liste(& prvi);
	Ucitaj_Polinom("Polinom_2.txt", & drugi);
	Ispis_Liste(&drugi);
	system("pause");
	return 0;
}
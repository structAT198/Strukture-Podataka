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

Polinom* Novi_Polinom(int coefficient, int exponent)
{
	Polinom* novi = (Polinom*) malloc(sizeof(Polinom));
	novi->coefficient = coefficient;
	novi->exponent = exponent;
	novi->next = NULL;
	return novi;
}

void Sort_Unos(Polinom* dummy, Polinom* novi)
{
    Polinom* tmp = dummy->next;
    if(tmp == NULL)
    {
        dummy->next = novi;
    }
    else
    {
        if(tmp->exponent > novi->exponent)
        {
            dummy->next = novi;
            novi->next = tmp;
        }
        else
        {
            while((tmp->next != NULL) && !((tmp->next->exponent > novi->exponent) && (tmp->exponent <= novi->exponent)))
            {
                tmp = tmp->next;
            }
            if(tmp->next == NULL)
            {
                tmp->next = novi;
            }
            else
            {
                Polinom* tmp2 = tmp->next;
                tmp->next = novi;
                novi->next = tmp2;
            }
        }
    }
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
			Sort_Unos(dummy, temp);
		}
	}
}

void Dodaj_Polinome(Polinom* first, Polinom* second, Polinom* rezultat)
{
    while(first->next && second->next) 
	{
		if(first->exponent > second->exponent) 
		{ 
			rezultat->exponent = first->exponent; 
			rezultat->coefficient = first->coefficient; 
			first = first->next; 
		}
		else if(first->exponent < second->exponent) 
		{ 
			rezultat->exponent = second->exponent; 
			rezultat->coefficient = second->coefficient; 
			second = second->next; 
		}
		else
		{ 
			rezultat->exponent = first->exponent; 
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
			rezultat->exponent = first->exponent; 
			rezultat->coefficient = first->coefficient; 
			first = first->next; 
		} 
		if(second->next) 
		{ 
			rezultat->exponent = second->exponent; 
			rezultat->coefficient = second->coefficient; 
			second = second->next; 
		} 
		rezultat->next = (Polinom*) malloc(sizeof(Polinom)); 
		rezultat = rezultat->next; 
		rezultat->next = NULL; 
	} 
}

void Mnozi_Polinome(Polinom* first, Polinom* second, Polinom* rezultat)
{
    while(first->next && second->next) 
	{
		if(first->exponent > second->exponent) 
		{ 
			rezultat->exponent = first->exponent; 
			rezultat->coefficient = first->coefficient; 
			first = first->next; 
		}
		else if(first->exponent < second->exponent) 
		{ 
			rezultat->exponent = second->exponent; 
			rezultat->coefficient = second->coefficient; 
			second = second->next; 
		}
		else
		{ 
			rezultat->exponent = first->exponent; 
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
			rezultat->exponent = first->exponent; 
			rezultat->coefficient = first->coefficient; 
			first = first->next; 
		} 
		if(second->next) 
		{ 
			rezultat->exponent = second->exponent; 
			rezultat->coefficient = second->coefficient; 
			second = second->next; 
		} 
		rezultat->next = (Polinom*) malloc(sizeof(Polinom)); 
		rezultat = rezultat->next; 
		rezultat->next = NULL; 
	} 
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

int main()
{
	Polinom prvi;
	Polinom drugi;
    Polinom rezultat_d;
    Polinom rezultat_m;
	prvi.next = NULL;
	drugi.next = NULL;
    rezultat_d.next = NULL;
	rezultat_m.next = NULL;
	Ucitaj_Polinom("Polinom_1.txt", & prvi);
	Ispis_Liste(& prvi);
	Ucitaj_Polinom("Polinom_2.txt", & drugi);
	Ispis_Liste(& drugi);
    Dodaj_Polinome(& prvi, & drugi, & rezultat_d);
    Ispis_Liste(& rezultat_d);
    Mnozi_Polinome(& prvi, & drugi, & rezultat_m);
    Ispis_Liste(& rezultat_m);
	return 0;
}

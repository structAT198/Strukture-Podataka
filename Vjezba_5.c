#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Lista
{
    int broj;
    struct Lista* next;
}Lista;

Lista* Nova_Lista(int broj)
{
    Lista* nova = (Lista*) malloc(sizeof(Lista));
    nova->broj = broj;
    nova->next = NULL;
    return nova;
}

void Unesi_Sortirano(int broj, Lista* dummy)
{
    Lista* tmp = dummy->next;
    if(tmp == NULL)
    {
        dummy->next = Nova_Lista(broj);
    }
    else
    {
        if(tmp->broj > broj)
        {
            Lista* nova = Nova_Lista(broj);
            dummy->next = nova;
            nova->next = tmp;
        }
        else
        {
            while((tmp->next != NULL) && !((tmp->next->broj > broj) && (tmp->broj <= broj)))
            {
                tmp = tmp->next;
            }
            if(tmp->next == NULL)
            {
                Lista* nova = Nova_Lista(broj);
                tmp->next = nova;
            }
            else
            {
                Lista* nova = Nova_Lista(broj);
                Lista* tmp2 = tmp->next;
                tmp->next = nova;
                nova->next = tmp2;
            }
        }
    }
}

void Ispisi_Listu(Lista* dummy)
{
    Lista* tmp = dummy->next;
    while(tmp != NULL)
    {
        printf("%d ", tmp->broj);
        tmp = tmp->next;
    }
    printf("\n");
}

int main()
{
    Lista prva;
    Lista druga;
    Lista rezultat;
    prva.next = NULL;
    druga.next = NULL;
    rezultat.next = NULL;
    Unesi_Sortirano(8, & prva);
    Unesi_Sortirano(1, & prva);
    Unesi_Sortirano(5, & prva);
    Unesi_Sortirano(7, & prva);
    Unesi_Sortirano(5, & druga);
    Unesi_Sortirano(9, & druga);
    Unesi_Sortirano(9, & druga);
    Unesi_Sortirano(1, & druga);
    Unesi_Sortirano(2, & druga);
    Ispisi_Listu(& prva);
    Ispisi_Listu(& druga);
    return 0;
}

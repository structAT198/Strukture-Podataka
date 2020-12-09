#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct Stack
{
    int broj;
    struct Stack* next;
}Stack;

typedef struct Red
{
    int broj;
    struct Red* next;
}Red;

Stack* Novi_Stack(int broj)
{
    Stack* novi = (Stack*) malloc(sizeof(Stack));
    novi->broj = broj;
    novi->next = NULL;
    return novi;
}

Red* Novi_Red(int broj)
{
    Red* novi = (Red*) malloc(sizeof(Red));
    novi->broj = broj;
    novi->next = NULL;
    return novi;
}

int Random_Broj()
{
    int random = (rand() % (100 - 10 + 1)) + 10;
}

void Ispisi_Stack(Stack* dummy)
{
    Stack* tmp = dummy->next;
    while(tmp != NULL)
    {
        printf("%d ", tmp->broj);
        tmp = tmp->next;
    }
    printf("\n");
}

void Ispisi_Red(Red* dummy)
{
    Red* tmp = dummy->next;
    while(tmp != NULL)
    {
        printf("%d ", tmp->broj);
        tmp = tmp->next;
    }
    printf("\n");
}

void Push(Stack* dummy)
{
    Stack* tmp = dummy->next;
    if(tmp == NULL)
    {
        dummy->next = Novi_Stack(Random_Broj());
    }
    else
    {
        Stack* prije = tmp;
        dummy->next = Novi_Stack(Random_Broj());
        dummy->next->next = tmp;
    }
}

void Pop(Stack* dummy)
{
    Stack* tmp = dummy->next;
    if(tmp == NULL)
    {
        printf("Stack prazan!");
    }
    else
    {
        Stack* prije = tmp->next;
        free(tmp);
        dummy->next = prije;
    }
}

void Uredi(Red* dummy)
{
    Red* tmp = dummy->next;
    if(tmp == NULL)
    {
        dummy->next = Novi_Red(Random_Broj());
    }
    else
    {
        while(tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        tmp->next = Novi_Red(Random_Broj());
    }
}

void Izneredi(Red* dummy)
{
    Red* tmp = dummy->next;
    if(tmp == NULL)
    {
        printf("Red prazan!");
    }
    else
    {
        Red* prije = tmp->next;
        free(tmp);
        dummy->next = prije;
    }
}

int main()
{
    srand(time(0));
    Stack stack;
    stack.next = NULL;
    printf("Test stack-a:\n");
    Push(& stack);
    Ispisi_Stack(& stack);
    Push(& stack);
    Ispisi_Stack(& stack);
    Push(& stack);
    Ispisi_Stack(& stack);
    Push(& stack);
    Ispisi_Stack(& stack);
    Pop(& stack);
    Ispisi_Stack(& stack);
    Pop(& stack);
    Ispisi_Stack(& stack);
    Pop(& stack);
    Ispisi_Stack(& stack);
    Pop(& stack);
    Pop(& stack);
    printf("\nTest reda:\n");
    Red red;
    red.next = NULL;
    Uredi(& red);
    Ispisi_Red(& red);
    Uredi(& red);
    Ispisi_Red(& red);
    Uredi(& red);
    Ispisi_Red(& red);
    Uredi(& red);
    Ispisi_Red(& red);
    Izneredi(& red);
    Ispisi_Red(& red);
    Izneredi(& red);
    Ispisi_Red(& red);
    Izneredi(& red);
    Ispisi_Red(& red);
    Izneredi(& red);
    Izneredi(& red);
    printf("\n");
    return 0;
}

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 256

typedef struct Stack
{
    int broj;
    struct Stack* next;
}Stack;

typedef struct Directory
{
    char name[MAX_NAME_LENGTH];
    struct Directory* siblings;
    struct Directory* child;
}Directory;

Stack* Novi_Stack(int broj)
{
    Stack* novi = (Stack*) malloc(sizeof(Stack));
    novi->broj = broj;
    novi->next = NULL;
    return novi;
}

Directory* Novi_Directory()
{
    Directory* novi = (Directory*) malloc(sizeof(Directory));
    novi->siblings = NULL;
    novi->child = NULL;
    return novi;
}

void Ispisi_Stack(Stack* dummy)
{
    Stack* tmp = dummy->next;
    while (tmp != NULL)
    {
        printf("%d ", tmp->broj);
        tmp = tmp->next;
    }
    printf("\n");
}

void Push(Stack* dummy, int broj)
{
    Stack* tmp = dummy->next;
    if (tmp == NULL)
    {
        dummy->next = Novi_Stack(broj);
    }
    else
    {
        Stack* prije = tmp;
        dummy->next = Novi_Stack(broj);
        dummy->next->next = tmp;
    }
}

void Pop(Stack* dummy)
{
    Stack* tmp = dummy->next;
    if (tmp == NULL)
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

/*void Unesi_Sortirano(int broj, Lista* dummy)
{
    Lista* tmp = dummy->next;
    if (tmp == NULL)
    {
        dummy->next = Nova_Lista(broj);
    }
    else
    {
        if (tmp->broj > broj)
        {
            Lista* nova = Nova_Lista(broj);
            dummy->next = nova;
            nova->next = tmp;
        }
        else
        {
            while ((tmp->next != NULL) && !((tmp->next->broj > broj) && (tmp->broj <= broj)))
            {
                tmp = tmp->next;
            }
            if (tmp->next == NULL)
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
}*/

int main()
{
    char command_name[256];
    char command[6];
    char name[256];
    int trash = 0;
    while(1)
    {
        trash = scanf("%s", command_name);
        int trash_size = strlen(command_name);
        /*if(strcmp(command, "cd") == 0)
        {
            printf("Pozvan cd, na: %s\n", name);
        }
        else if (strcmp(command, "md") == 0)
        {
            printf("Pozvan md, na: %s\n", name);
        }
        else if (strcmp(command, "dir") == 0)
        {
            printf("Pozvan dir, na: %s\n", name);
        }
        else if (strcmp(command, "rm") == 0)
        {
            printf("Pozvan rm, na: %s\n", name);
        }
        else
        {
            printf("Nepoznata komanda!\n");
        }*/
    }
}

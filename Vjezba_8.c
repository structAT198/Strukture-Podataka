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

Directory* Novi_Directory(char* name)
{
    Directory* novi = (Directory*) malloc(sizeof(Directory));
    strcpy(novi->name, name);
    novi->siblings = NULL;
    novi->child = NULL;
    return novi;
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

void Push(Stack* dummy, int broj)
{
    Stack* tmp = dummy->next;
    if(tmp == NULL)
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

void Add_Child(char* name, Directory* parent)
{
    //W.I.P.
    Directory* tmp = parent->child;
    if(tmp == NULL)
    {
        tmp = Novi_Directory(name);
    }
    else
    {
        if(tmp->name[0] > name[0])
        {
            Directory* novi = Novi_Directory(name);
            parent->child = novi;
            novi->child = tmp;
        }
        else
        {
            while((tmp->child != NULL) && !((tmp->child->name[0] > name[0]) && (tmp->name[0] <= name[0])))
            {
                tmp = tmp->child;
            }
            if(tmp->child == NULL)
            {
                Directory* novi = Novi_Directory(name);
                tmp->child = novi;
            }
            else
            {
                Directory* nova = Novi_Directory(name);
                Directory* tmp2 = tmp->child;
                tmp->child = nova;
                nova->child = tmp2;
            }
        }
    }
}

void Add_Sibling(char* name, Directory* parent)
{

}

int main()
{
    char command_name[256];
    Directory root;
    strcpy(root.name, "C:");
    root.siblings = NULL;
    root.child = NULL;
    while(1)
    {
        gets_s(& command_name, 256);
        char* command = strtok(command_name, " ");
        char* name = strtok(NULL, " ");
        if(strcmp(command, "cd") == 0)
        {
            
        }
        else if(strcmp(command, "md") == 0)
        {

        }
        else if(strcmp(command, "dir") == 0)
        {

        }
        else if(strcmp(command, "rm") == 0)
        {

        }
        else if(strcmp(command, "exit") == 0)
        {
            return 0;
        }
        else
        {
            printf("Nepoznata komanda!\n");
        }
    }
}

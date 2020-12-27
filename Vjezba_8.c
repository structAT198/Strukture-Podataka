#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAME_LENGTH 256

typedef struct Stack
{
    struct Directory* directory;
    struct Stack* next;
}Stack;

typedef struct Directory
{
    char name[MAX_NAME_LENGTH];
    struct Directory* sibling;
    struct Directory* child;
}Directory;

Stack* Novi_Stack(Directory* directory)
{
    Stack* novi = (Stack*) malloc(sizeof(Stack));
    novi->directory = directory;
    novi->next = NULL;
    return novi;
}

Directory* Novi_Directory(char* name)
{
    Directory* novi = (Directory*) malloc(sizeof(Directory));
    strcpy(novi->name, name);
    novi->sibling = NULL;
    novi->child = NULL;
    return novi;
}

void Ispisi_Stack(Stack* dummy)
{
    Stack* tmp = dummy->next;
    while(tmp != NULL)
    {
        printf("%s ", tmp->directory->name);
        tmp = tmp->next;
    }
    printf("\n");
}

void Push(Stack* dummy, Directory* directory)
{
    Stack* tmp = dummy->next;
    if(tmp == NULL)
    {
        dummy->next = Novi_Stack(directory);
    }
    else
    {
        Stack* prije = tmp;
        dummy->next = Novi_Stack(directory);
        dummy->next->next = tmp;
    }
}

Directory* Pop(Stack* dummy)
{
    Stack* tmp = dummy->next;
    if(tmp == NULL)
    {
        printf("Stack prazan!");
    }
    else
    {
        Directory* directory = tmp->directory;
        Stack* prije = tmp->next;
        free(tmp);
        dummy->next = prije;
        return directory;
    }
}

void Add_Sibling(Directory* relative, char* name)
{
    Directory* tmp = relative;
    while(tmp->sibling != NULL)
    {
        tmp = tmp->sibling;
    }
    tmp->sibling = Novi_Directory(name);
}

void Add_Child(Directory* parent, char* name)
{
    if(parent->child != NULL)
    {
        Add_Sibling(parent->child, name);
    }
    else
    {
        parent->child = Novi_Directory(name);
    }
}

void Remove_Child(Directory* directory)
{
    //jos samo ovo
}

bool Directory_Exists(Directory* current_directory, char* name)
{
    Directory* tmp = current_directory;
    if(tmp->child == NULL)
    {
        return false;
    }
    else
    {
        if(strcmp(tmp->child->name, name) == 0)
        {
            return true;
        }
        else
        {
            Directory* tmp_2 = current_directory->child->sibling;
            while(tmp_2 != NULL)
            {
                if(strcmp(tmp_2->name, name) == 0)
                {
                    return true;
                }
                tmp_2 = tmp_2->sibling;
            }
            return false;
        }
    }
}

Directory* Get_Directory(Directory* current_directory, char* name)
{
    Directory* tmp = current_directory;
    if(tmp->child != NULL)
    {
        if(strcmp(tmp->child->name, name) == 0)
        {
            return tmp->child;
        }
        else
        {
            Directory* tmp_2 = current_directory->child->sibling;
            while(tmp_2 != NULL)
            {
                if(strcmp(tmp_2->name, name) == 0)
                {
                    return tmp_2;
                }
                tmp_2 = tmp_2->sibling;
            }
        }
    }
}

void Print_Directory(Directory* current_directory)
{
    Directory* tmp = current_directory->child;
    if(tmp == NULL)
    {
        printf("Direktorij prazan!\n");
        return;
    }
    else
    {
        printf("    >> %s\n", tmp->name);
        if(tmp->sibling != NULL)
        {
            Directory* tmp_2 = current_directory->child->sibling;
            while(tmp_2 != NULL)
            {
                printf("    >> %s\n", tmp_2->name);
                tmp_2 = tmp_2->sibling;
            }
        }
    }
}

int main()
{
    char command_name[256];
    Directory root;
    strcpy(root.name, "C:");
    root.sibling = NULL;
    root.child = NULL;
    Stack cd_stack;
    cd_stack.next = NULL;
    Directory* current_directory = & root;
    char prompt[512] = { "C:\\" };
    printf("%s", prompt);
    printf(">");
    while(1)
    {
        gets_s(& command_name, 256);
        char* command = strtok(command_name, " ");
        char* name = strtok(NULL, " ");
        if(strcmp(command, "cd") == 0)
        {
            if(strcmp(name, "..") == 0) 
            {
                if(strcmp(current_directory->name, "C:") != 0)
                {
                    int prompt_length = strlen(prompt);
                    int current_name_length = strlen(current_directory->name);
                    for(int i = 0; i < (current_name_length + 2); i++)
                    {
                        prompt[prompt_length - i] = '\0';
                    }
                    current_directory = Pop(& cd_stack);
                }
            }
            else
            {
                if(Directory_Exists(current_directory, name) == true)
                {
                    Push(& cd_stack, current_directory);
                    current_directory = Get_Directory(current_directory, name);
                    strcat(& prompt, name);
                    prompt[strlen(prompt)] = '\\';
                }
                else
                {
                    printf("Direktorij \"%s\" ne postoji!\n", name);
                }
            }
        }
        else if(strcmp(command, "md") == 0)
        {
            if(Directory_Exists(current_directory, name) == false)
            {
                Add_Child(current_directory, name);
            }
            else
            {
                printf("Direktorij vec postoji!\n");
            }
        }
        else if(strcmp(command, "dir") == 0)
        {
            Print_Directory(current_directory);
        }
        else if(strcmp(command, "rm") == 0)
        {
            if(Directory_Exists(current_directory, name) == true)
            {
                Remove_Child(Get_Directory(current_directory, name));
            }
            else
            {
                printf("Direktorij ne postoji!\n");
            }
        }
        else if(strcmp(command, "exit") == 0)
        {
            return 0;
        }
        else
        {
            printf("Nepoznata komanda!\n");
        }
        printf("%s", prompt);
        printf(">");
    }
}

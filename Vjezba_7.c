#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stack
{
	double broj;
	struct Stack* next;
}Stack;

Stack* Novi_Stack(double broj)
{
	Stack* novi = (Stack*) malloc(sizeof(Stack));
	novi->broj = broj;
	novi->next = NULL;
	return novi;
}

void Push(Stack* dummy, double broj)
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

double Pop(Stack* dummy)
{
    Stack* tmp = dummy->next;
    if(tmp == NULL)
    {
        printf("Stack prazan!");
    }
    else
    {
        double value = tmp->broj;
        Stack* prije = tmp->next;
        free(tmp);
        dummy->next = prije;
        return value;
    }
}

int main()
{
	char postfiks[512];
	FILE* data = fopen("Postfiks.txt", "r");
    Stack stack;
    stack.next = NULL;
	if(data != NULL)
	{
		fgets(postfiks, 512, data);
		printf("Ucitan postfiks: %s\n", postfiks);
        int length = strlen(postfiks);
        for(int i = 0; i < length; i++)
        {
            if(postfiks[i] != ' ' && postfiks[i] != '\0' && postfiks[i] != '\n')
            {
                switch(postfiks[i])
                {
                    case '+':
                    {
                        double number_1 = Pop(& stack);
                        double number_2 = Pop(& stack);
                        Push(& stack, number_2 + number_1);
                        break;
                    }
                    case '-':
                    {
                        double number_1 = Pop(& stack);
                        double number_2 = Pop(& stack);
                        Push(& stack, number_2 - number_1);
                        break;
                    }
                    case '*':
                    {
                        double number_1 = Pop(& stack);
                        double number_2 = Pop(& stack);
                        Push(& stack, number_2 * number_1);
                        break;
                    }
                    case '/':
                    {
                        double number_1 = Pop(& stack);
                        double number_2 = Pop(& stack);
                        Push(& stack, number_2 / number_1);
                        break;
                    }
                    default:
                    {
                        int broj = postfiks[i] - '0';
                        Push(& stack, broj);
                        break;
                    }
                }
            }
        }
        double result = Pop(& stack);
        printf("Rezultat: %f\n", result);
	}
	else
	{
		printf("\nFatal error: postfix not found!");
		return 0;
	}
}

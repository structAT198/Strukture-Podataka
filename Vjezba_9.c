#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Tree
{
	int number;
	struct Tree* left;
	struct Tree* right;
}Tree;

Tree* NewTree(int number)
{
	Tree* new = (Tree*) malloc(sizeof(Tree));
	new->number = number;
	new->left = NULL;
	new->right = NULL;
	return new;
}

Tree* Insert(Tree* current, Tree* element)
{
	if(current == NULL)
	{
		return element;
	}
	if(current->number > element->number)
	{
		current->left = Insert(current->left, element);
	}
	else if(current->number < element->number)
	{
		current->right = Insert(current->right, element);
	}
	else
	{
		free(element);
	}
	return current;
}

Tree* Find(Tree* current, int number)
{
	if(current == NULL)
	{
		return NULL;
	}
	if(current->number > number)
	{
		return Find(current->left, number);
	}
	else if(current->number < number)
	{
		return Find(current, number);
	}
	else
	{
		return current;
	}
}

void PrintInOrder(Tree* current)
{
	if(current == NULL)
	{
		return;
	}
	PrintInOrder(current->left);
	printf("%d ", current->number);
	PrintInOrder(current->right);
}

Tree* FindMax(Tree* current)
{
	if(current == NULL)
	{
		return NULL;
	}
	while(current->right != NULL)
	{
		current = current->right;
	}
	return current;
}

Tree* FindMin(Tree* current)
{
	if(current == NULL)
	{
		return NULL;
	}
	while(current->left != NULL)
	{
		current = current->left;
	}
	return current;
}

Tree* DeleteNode(Tree* current, int number)
{
	if(current == NULL)
	{
		return NULL;
	}
	if(current->number == number)
	{
		if(current->left != NULL)
		{
			Tree* temp = FindMax(current->left);
			current->number = temp->number;
			current->left = DeleteNode(current->left, temp->number);
		}
		else if(current->right != NULL)
		{
			Tree* temp = FindMin(current->right);
			current->number = temp->number;
			current->right = DeleteNode(current->right, temp->number);
		}
		else
		{
			free(current);
			return NULL;
		}
	}
	else if(current->number > number)
	{
		current->left = DeleteNode(current->left, number);
	}
	else
	{
		current->right = DeleteNode(current->right, number);
	}
	return current;
}

int main()
{
		FILE* brojevi = fopen("Brojevi.txt", "r");
		if(brojevi == NULL)
		{
			printf("Error: Brojevi.txt ne postoji!");
			return -1;
		}
		else
		{

			Tree* root = NULL;
			int first = 0;
			fscanf(brojevi, "%d ", & first);
			root = Insert(root, NewTree(first));
			while(feof(brojevi) != 1)
			{
				fscanf(brojevi, "%d ", & first);
				Insert(root, NewTree(first));
			}
			PrintInOrder(root);
			system("pause");
			return 0;
		}
}
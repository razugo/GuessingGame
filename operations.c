#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operations.h"

char * readLine(FILE * test)
{
	int counter = 0;
	int size = 10;
	char *string;
	char temp = getc(test);
	if(temp == EOF)
	{
		fprintf(stderr, "corrupted database -- prompt with missing response.\n");
		exit(-1);
	}
	if(temp == '\n')
	{
		return NULL;
	}
	string = (char *)malloc(sizeof(char) * size);
	if(string == NULL)
	{
		fprintf(stderr, "Malloc Error\n");
		exit(-1);
	}
	while(temp != '\n' && temp != EOF)
	{
		string[counter] = temp;
		counter++;
		if(counter == size)
		{
			char * tchar = NULL;
			size = size + 10;
			tchar = realloc(string, size);
			if(tchar == NULL)
			{
				fprintf(stderr, "Realloc Error\n");
				exit(-1);
			}
			string = tchar;
		}
		temp = getc(test);
	}
	string[counter] = '\0';
	return string;
}

struct node * createTree(FILE * file)
{
	struct node *returnNode = recursiveTree(file);
	char temp = getc(file);
	if(temp != EOF)
	{
		fprintf(stderr, "corrupted database -- prompt with missing response\n");
		exit(-1);
	}
	return returnNode;
}

struct node * recursiveTree(FILE * file)
{
	char * temp;
	char * string;
	struct node *newNode = (struct node *)malloc(sizeof(struct node));
	if(newNode == NULL)
	{
		fprintf(stderr, "Malloc Error\n");
		free(newNode);
		exit(-1);
	}
	newNode -> left = NULL;
	newNode -> right = NULL;
	temp = readLine(file);
	string = (char *)malloc(sizeof(char) * strlen(temp));
	strcpy(string, temp + 1);
	newNode -> contents = string;
	if(temp[0] == 'a')
	{
		free(temp);
		return newNode;
	}
	else if(temp[1] == 'q');
	{
		newNode -> left = recursiveTree(file);
		newNode -> right = recursiveTree(file);
		free(temp);
		return newNode;
	}
	free(newNode);
	return NULL;
}
void writeFile(FILE * file, struct node * current)
{
	 if(current -> left == NULL && current -> right == NULL)
	 {
		 fprintf(file, "a%s\n", current -> contents);
		 return;
	 }
	 fprintf(file, "q%s\n", current -> contents);
	 writeFile(file, current -> left);
	 writeFile(file, current -> right);
	 return;
}

void freeTree(struct node * first)
{
	if(first -> left != NULL && first -> right != NULL)
	{
		freeTree(first -> left);
		freeTree(first -> right);
	}

	free(first -> contents);
	first -> contents = NULL;
	free(first -> left);
	first -> left = NULL;
	free(first -> right);
	first -> right = NULL;
	return;
}

void finish(FILE * file, struct node * current)
{
	fclose(file);
	file = fopen("qa.db", "w");
	writeFile(file, current);
	freeTree(current);
	free(current);
	fclose(file);
}

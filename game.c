#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "operations.h"
#include "game.h"
void playgame(struct node **first)
{
	int game = 0;
	struct node ** pcurrent = first;
	int correct;
	/*printf("Address of first: %p\n", (void *)first);*/
	while(game == 0)
	{
		if((*pcurrent) -> left == NULL && (*pcurrent) -> right == NULL)
		{
			
			correct = answer(pcurrent);
			game = 1;
		}
		else
		{
			pcurrent = question(pcurrent);
		}
	}
	if(correct == 1)
	{
		printf("\nMy, am I clever. :)\nThanks for playing.\n\n");
	}
	else
	{
		/*printf("Address of pcurrent: %p\n", (void *)pcurrent);
		*printf("Address of pcurrent dereferenced: %p\n", (void *)*pcurrent);*/
		wrong(pcurrent);
		/*printf("Address of pcurrent after wrong: %p\n", (void *)pcurrent);
		*printf("Address of pcurrent dereferenced after wrong: %p\n", (void *)*pcurrent);*/
	}
}
struct node * fresh()
{
	char * input = NULL;
	struct node * answer = (struct node *)malloc(sizeof(struct node));
	printf("What is it (with article)? ");
	input = readLine(stdin);
	while(input == NULL)
	{
		printf("An empty response is not acceptable.  Please answer again.\n");
		printf("What is it (with article)? ");
		input = readLine(stdin);
	}
	answer -> contents = input;
	answer -> left = NULL;
	answer -> right = NULL;
	return answer;
}
	
void wrong(struct node ** current)
{
	char * input = NULL;
	char * input2 = NULL;
	char * input3 = NULL;
	struct node * temp = *current;
	struct node * question = (struct node *)malloc(sizeof(struct node));
	struct node * answer = (struct node *)malloc(sizeof(struct node));
	printf("\nHow disappointing.\n");
	printf("What is it (with article)? ");
	input = readLine(stdin);
	while(input == NULL)
	{
		printf("An empty response is not acceptable.  Please answer again.\n");
		printf("What is it (with article)? ");
		input = readLine(stdin);
	}
	printf("What is a yes/no question that will distinguish %s from %s?\n? ", input, temp -> contents);
	input2 = readLine(stdin);
	while (input2 == NULL)
	{
		printf("An empty response is not acceptable.  Please answer again.\n");
		printf("? ");
		input2 = readLine(stdin);
	}
	printf("\nWhat is the answer to the question for %s? ", input);
	input3 = readLine(stdin);
	while(input3 == NULL)
	{
		printf("An empty response is not acceptable.  Please answer again.\n");
		printf("\nWhat is the answer to the question for %s? ", input);
		input3 = readLine(stdin);
	}
	printf("\nI'll get it next time, I'm sure.\nThanks for playing.\n\n");
	question -> contents = input2;
	answer -> contents = input;
	answer -> left = NULL;
	answer -> right = NULL;
	if(input3[0] == 'y' || input3[0] == 'Y')
	{
		question -> right = answer;
		question -> left = *current;
	}
	else
	{
		question -> right = *current;
		question -> left = answer;
	}
	free(input3);
	/*printf("Address of dereferenced current in wrong function: %p\n", (void *)*current);*/
	*current = question;
	/*printf("Address of dereferenced current in wrong function: %p\n", (void *)*current);*/
}
		

struct node ** question(struct node ** current)
{
	char * input = NULL;
	printf("%s ", (*current) -> contents);
	input = readLine(stdin);
	while(input == NULL)
	{
		printf("An empty response is not acceptable.  Please answer again.\n");
		printf("%s ", (*current) -> contents);
		input = readLine(stdin);
	}
	if(input[0] == 'y' || input [0] == 'Y')
	{
		free(input);
		return &((*current) -> right);
		
	}
	else
	{
		free(input);
		return &((*current) -> left);
	}
}

int answer(struct node ** current)
{
	char * input = NULL;
	printf("Is it %s? ", (*current) -> contents);
	input = readLine(stdin);
	while(input == NULL)
	{
		printf("An empty response is not acceptable.  Please answer again.\n");
		printf("Is it %s? ", (*current) -> contents);
		input = readLine(stdin);
	}
	if(input[0] == 'y' || input[0] == 'Y')
	{
		free(input);
		return 1;
	}
	else
	{
		free(input);
		return 0;
	}
}

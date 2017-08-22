#include <stdio.h>
#include <unistd.h>
#include "game.h"
#include "operations.h"

int main(void)
{
	FILE * file;
	struct node * root;
	if(access("qa.db", F_OK) != -1)
	{
		file = fopen("qa.db", "r");
		root = createTree(file);
		playgame(&root);
	}
	else
	{
		printf("qa.db: No such file or directory\n");
		printf("Unable to read database qa.db.  Starting fresh.\n\n");
		file = fopen("qa.db", "w+");
		root = fresh();
	}
	finish(file, root);
	return 0;
}

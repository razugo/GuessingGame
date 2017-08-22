#ifndef OPERATIONS_H
#define OPERATIONS_H

struct node
{
	char * contents;
	struct node * left;
	struct node * right;
};

char *readLine(FILE * test);
struct node * createTree(FILE * file);
struct node * recursiveTree(FILE * file);
void writeFile(FILE * file, struct node * current);
void freeTree(struct node * first);
void finish(FILE * file, struct node * current);

#endif

#ifndef GAME_H
#define GAME_H
#include "operations.h"
void playgame(struct node ** first);
struct node *fresh(void);
void wrong(struct node ** current);
struct node ** question(struct node ** current);
int answer(struct node ** current);

#endif

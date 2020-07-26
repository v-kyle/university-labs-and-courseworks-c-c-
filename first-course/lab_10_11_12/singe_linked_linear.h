#ifndef HEADERS_SINGE_LINKED_LINEAR_H
#define HEADERS_SINGE_LINKED_LINEAR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "s_car.h"

Head *MakeHead();
car *CreateNode(char *bname, int slen, int y, int m);
void AddFirst(Head *MyHead, car *newcar);
void InsertAfter(Head *MyHead, car *NewNode, car *CurrentNode);
int compareVozr(const void * x1, const void * x2);
car* readFromFile(FILE* file, Head* MyHead);

#endif //HEADERS_SINGE_LINKED_LINEAR_H

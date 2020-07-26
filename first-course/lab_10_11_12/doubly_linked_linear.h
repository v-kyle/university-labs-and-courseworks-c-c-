#ifndef TEST2_DOUBLY_LINKED_LINEAR_H
#define TEST2_DOUBLY_LINKED_LINEAR_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "s_car.h"

Head *MakeHead2();
car *CreateNode2(char *bname, int slen, int y, int m);
void AddFirst2(Head *MyHead, car *NewNode);
void AddLast2(Head *MyHead, car *NewNode, car *PrevNode);
void InsertAfter2(Head *MyHead, car *NewNode, car *CurrentNode);
void InsertBefore2(Head *MyHead, car *NewNode, car *CurrentNode);
car* SelectByOrder(Head* MyHead, int n);
int number_cars(Head* MyHead);
void autoinkAll(Head* MyHead);
void autoinkN(Head* MyHead, int n);
car* readFromFile2(FILE* file, Head* MyHead);


#endif //TEST2_DOUBLY_LINKED_LINEAR_H

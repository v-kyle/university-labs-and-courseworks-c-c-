#ifndef TEST3_SINGLE_LINKED_CIRCULAR_H
#define TEST3_SINGLE_LINKED_CIRCULAR_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "s_car.h"

Head *MakeHead_c();
car *CreateNode_c(char *bname, int slen, int y, int m);
void AddFirst_c(Head *MyHead, car *newcar);
void InsertAfter_c(Head *MyHead, car *NewNode, car *CurrentNode);
void deleteSelected_c(Head *MyHead, car *CurrentNode);
void makeCircular_c(Head *MyHead);
car* readFromFile_c(FILE* file, Head* MyHead);



#endif //TEST3_SINGLE_LINKED_CIRCULAR_H

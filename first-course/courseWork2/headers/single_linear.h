#ifndef COURSE_WORK_2SEM_SINGLE_LINEAR_H
#define COURSE_WORK_2SEM_SINGLE_LINEAR_H

#include "type_car.h"
#include <stdio.h>
#include <stdlib.h>

Head *MakeHead();
car *CreateNode(char *brand, char *model, int year, int mileage, int maxSpeed, int condition);
car* inputData();
void AddFirst(Head *MyHead, car *NewNode);
void AddLast(Head *MyHead, car *NewNode);
void InsertAfter(Head *MyHead, car *NewNode, car *CurrentNode);
car* SelectById(Head* MyHead, int n, int o);
void showCar(car* p);
void showAll(Head* MyHead);
int deleteSelected(Head *MyHead, car *CurrentNode);
void editNode(car* CurrentNode);
void searchNode(Head* MyHead);
void sortList(Head* MyHead);

#endif //COURSE_WORK_2SEM_SINGLE_LINEAR_H

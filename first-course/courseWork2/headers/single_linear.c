#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "type_car.h"
#include "single_linear.h"
#include "interaction.h"
#define ML 255

Head *MakeHead()
{
    Head *ph=NULL;

    ph=(Head*)malloc(sizeof(Head));
    if(ph)
    {
        ph->cnt=0;
        ph->first=NULL;
        ph->last=NULL;
    }
    return ph;
}
car *CreateNode(char *brand, char *model, int year, int mileage, int maxSpeed, int condition)
{
    car *NewNode=NULL; /* pointer to new node */
    char *b_word=NULL;
    char *m_word=NULL;
    int b_len = strlen(brand)+1;
    int m_len = strlen(model)+1;

    NewNode = (car*)malloc(sizeof(car));
    b_word=(char*)malloc(b_len*sizeof(char));
    m_word=(char*)malloc(m_len*sizeof(char));
    if(NewNode && b_word && m_word)
    {
        NewNode->id = 1;

        strcpy(b_word, brand);
        NewNode->brand=b_word;
        strcpy(m_word, model);
        NewNode->model=m_word;
        NewNode->year = year;
        NewNode->mileage = mileage;
        NewNode->maxSpeed = maxSpeed;
        NewNode->condition = condition;

        NewNode->next = NULL;
    }
    return NewNode;
}
car* inputData(){
    car* p;
    char brand[ML], model[ML];
    int year, mileage, maxSpeed, condition;
    puts("Enter car brand:");
    fgets(brand, ML, stdin);
    brand[strlen(brand)-1] = '\0';
    puts("Enter car model:");
    fgets(model, ML, stdin);
    model[strlen(model)-1] = '\0';
    puts("Enter car year:");
    year = smartInt(4);
    puts("Enter car mileage:");
    mileage = smartInt(10);
    puts("Enter car max speed:");
    maxSpeed = smartInt(4);
    puts("Enter car condition:");
    condition = smartInt(2);
    p = CreateNode(brand, model, year, mileage, maxSpeed, condition);
    puts("Creation of new record was successful.");
    return p;
}
void AddFirst(Head *MyHead, car *NewNode)
{
    MyHead->first = NewNode;
    MyHead->last = NewNode;
    MyHead->cnt++;
}

void AddLast(Head *MyHead, car *NewNode){
    if (MyHead->first == NULL) AddFirst(MyHead, NewNode);
    else {
        int n;
        car *lastElement = MyHead->last;
        n = MyHead->cnt + 1;
        lastElement->next = NewNode;
        MyHead->last = NewNode;
        NewNode->id = n;
        MyHead->cnt = n;
    }
}

void InsertAfter(Head *MyHead, car *NewNode, car *CurrentNode)
{
    int n;
    car* q = NULL;
    if(MyHead&&NewNode&&CurrentNode)
    {
        n=MyHead->cnt+1;
        if(CurrentNode->next==NULL)
        {
            CurrentNode->next=NewNode;
            MyHead->last=NewNode;
        }
        else
        {
            q = CurrentNode->next;
            NewNode->next = CurrentNode->next;
            CurrentNode->next=NewNode;
        }
        NewNode->id=n;
        MyHead->cnt=n;
    }
}

car* SelectById(Head* MyHead, int n, int o){
    int flag = 1;
    car* q = MyHead->first;
    if (n > 0)
    {
        while(q!=NULL && flag) {
            if (q->id == n) {
                flag = 0;
                if (o) puts("Your choice is:");
                showCar(q);
            }
            else q = q->next;
        }
    }
    else q = NULL;
    if (flag == 1) q = NULL;
    return q;
}

void showCar(car* p){
    printf("id: %02d \t %-15s %-15s year: %4d \t mileage: %06d \t Max Speed %3d \t car condition: %02d\n", p->id, p->brand, p->model, p->year, p->mileage, p->maxSpeed, p->condition);
}

void showAll(Head* MyHead){
    car* p = MyHead->first;
    while(p!=NULL){
        showCar(p);
        p = p->next;
    }
}

int deleteSelected(Head *MyHead, car *CurrentNode)
{
    car *q, *q_last;
    int rtn;
    q=MyHead->first;
    q_last=MyHead->last;

    if (CurrentNode == NULL) {
        rtn = 0;
    }
    else {
        if (CurrentNode == q) {
            MyHead->first = CurrentNode->next;
            CurrentNode->next = NULL;
            free(CurrentNode);
        } else {
            do {
                if (q->next == CurrentNode) {
                    if (CurrentNode == q_last) {
                        MyHead->last = q;
                        MyHead->last->next = MyHead->first;
                    }
                    q->next = CurrentNode->next;
                    CurrentNode->next = NULL;
                    free(CurrentNode);
                } else q = q->next;
            } while (q != NULL);
        }
        rtn = 1;
    }
    return rtn;
}

void editNode(car* CurrentNode){
    char str[ML];
    if (CurrentNode == NULL) outWrong();
    else {
        puts("Choose the field, which you want to edit:");
        outFields();
        int field = smartInt(1);
        switch (field) {
            case 1:
                puts("Enter the new car brand");
                fgets(str, ML, stdin);
                str[strlen(str)-1] = '\0';
                strcpy(CurrentNode->brand, str);
                break;
            case 2:
                puts("Enter the new car model");
                fgets(str, ML, stdin);
                str[strlen(str)-1] = '\0';
                strcpy(CurrentNode->model, str);
                break;
            case 3:
                puts("Enter the new car year");
                CurrentNode->year = smartInt(4);
                break;
            case 4:
                puts("Enter the new car mileage");
                CurrentNode->mileage = smartInt(10);
                break;
            case 5:
                puts("Enter the new car max speed");
                CurrentNode->maxSpeed = smartInt(4);
                break;
            case 6:
                puts("Enter the new car condition (0-10");
                CurrentNode->condition = smartInt(2);
                break;
            default:
                outWrong();
        }
        puts("Editing Success");
    }
}

void searchNode(Head* MyHead){
    if (MyHead != NULL){
        char str[ML];
        int value;
        int first_match = 1;
        car* p = MyHead->first;
        outFields();
        int field = smartInt(1);
        switch (field) {
            case 1:
                puts("Enter car brand for search:");
                fgets(str, ML, stdin);
                str[strlen(str)-1] = '\0';
                while(p != NULL){
                    if (!strcmp(str, p->brand)){
                        if(first_match){
                            first_match = 0;
                            puts("Found cars:");
                        }
                        showCar(p);
                    }
                    p = p->next;
                }
                if (first_match) puts("No cars found with these parameters");
                break;
            case 2:
                puts("Enter car model for search:");
                fgets(str, ML, stdin);
                str[strlen(str)-1] = '\0';
                while(p != NULL){
                    if (!strcmp(str, p->model)){
                        if(first_match){
                            first_match = 0;
                            puts("Found cars:");
                        }
                        showCar(p);
                    }
                    p = p->next;
                }
                if (first_match) puts("No cars found with these parameters");
                break;
            case 3:
                puts("Enter car production year for search:");
                value = smartInt(4);
                if (value == 0) outWrong();
                else {
                    if (value == -1) value = 0;
                    while (p != NULL) {
                        if (value == p->year) {
                            if (first_match) {
                                first_match = 0;
                                puts("Found cars:");
                            }
                            showCar(p);
                        }
                        p = p->next;
                    }
                    if (first_match) puts("No cars found with these parameters");
                }
                break;
            case 4:
                puts("Enter car mileage for search:");
                value = smartInt(10);
                if (value == 0) outWrong();
                else {
                    if (value == -1) value = 0;
                    while (p != NULL) {
                        if (value == p->mileage) {
                            if (first_match) {
                                first_match = 0;
                                puts("Found cars:");
                            }
                            showCar(p);
                        }
                        p = p->next;
                    }
                    if (first_match) puts("No cars found with these parameters");
                }
                break;
            case 5:
                puts("Enter car max speed for search:");
                value = smartInt(4);
                if (value == 0) outWrong();
                else {
                    if (value == -1) value = 0;
                    while (p != NULL) {
                        if (value == p->maxSpeed) {
                            if (first_match) {
                                first_match = 0;
                                puts("Found cars:");
                            }
                            showCar(p);
                        }
                        p = p->next;
                    }
                    if (first_match) puts("No cars found with these parameters");
                }
                break;
            case 6:
                puts("Enter car condition (from from 0 to 10) for search:");
                value = smartInt(2);
                if (value == 0) outWrong();
                else {
                    if (value == -1) value = 0;
                    while (p != NULL) {
                        if (value == p->condition) {
                            if (first_match) {
                                first_match = 0;
                                puts("Found cars:");
                            }
                            showCar(p);
                        }
                        p = p->next;
                    }
                    if (first_match) puts("No cars found with these parameters");
                }
                break;
            default:
                outWrong();
        }
    }
    else{
        outWrong();
    }
}

void swapCars(car *a, car *b) {
    int id = a->id;
    car* tmp = CreateNode(a->brand, a->model, a->year, a->mileage, a->maxSpeed, a->condition);

    a->id = b->id;
    a->brand = b->brand;
    a->model = b->model;
    a->year = b->year;
    a->mileage = b->mileage;
    a->maxSpeed = b->maxSpeed;
    a->condition = b->condition;

    b->id = id;
    b->brand = tmp->brand;
    b->model = tmp->model;
    b->year = tmp->year;
    b->mileage = tmp->mileage;
    b->maxSpeed = tmp->maxSpeed;
    b->condition = tmp->condition;
}



void sortList(Head* MyHead){
    car *p, *p1 = NULL;
    if (MyHead == NULL) outWrong();
    else {
        outFields();
        int flag_swap;
        int field = smartInt(1);
        switch (field) {
            case 1:
                do {
                    flag_swap = 0;
                    p = MyHead->first;
                    while (p->next != NULL) {
                        p1 = p->next;
                        if (strcmp(p->brand, p1->brand) > 0) {
                            swapCars(p, p->next);
                            flag_swap = 1;
                        }
                        p = p->next;
                    }
                } while (flag_swap);
                puts("Sorting Success");
                break;
            case 2:
                do {
                    flag_swap = 0;
                    p = MyHead->first;

                    while (p->next != NULL) {
                        p1 = p->next;
                        if (strcmp(p->model, p1->model) > 0) {
                            swapCars(p, p->next);
                            flag_swap = 1;
                        }
                        p = p->next;
                    }
                } while (flag_swap);
                puts("Sorting Success");
                break;
            case 3:
                do {
                    flag_swap = 0;
                    p = MyHead->first;

                    while (p->next != NULL) {
                        p1 = p->next;
                        if (p->year > p1->year) {
                            swapCars(p, p->next);
                            flag_swap = 1;
                        }
                        p = p->next;
                    }
                } while (flag_swap);
                puts("Sorting Success");
                break;
            case 4:
                do {
                    flag_swap = 0;
                    p = MyHead->first;

                    while (p->next != NULL) {
                        p1 = p->next;
                        if (p->mileage > p1->mileage) {
                            swapCars(p, p->next);
                            flag_swap = 1;
                        }
                        p = p->next;
                    }
                } while (flag_swap);
                puts("Sorting Success");
                break;
            case 5:
                do {
                    flag_swap = 0;
                    p = MyHead->first;

                    while (p->next != NULL) {
                        p1 = p->next;
                        if (p->maxSpeed > p1->maxSpeed) {
                            swapCars(p, p->next);
                            flag_swap = 1;
                        }
                        p = p->next;
                    }
                } while (flag_swap);
                puts("Sorting Success");
                break;
            case 6:
                do {
                    flag_swap = 0;
                    p = MyHead->first;

                    while (p->next != NULL) {
                        p1 = p->next;
                        if (p->condition > p1->condition) {
                            swapCars(p, p->next);
                            flag_swap = 1;
                        }
                        p = p->next;
                    }
                } while (flag_swap);
                puts("Sorting Success");
                break;
            default:
                outWrong();
        }
    }
}

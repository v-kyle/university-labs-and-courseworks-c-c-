#include "doubly_linked_linear.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MS 64

Head *MakeHead2()
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
car *CreateNode2(char *bname, int slen, int y, int m)
{
    car *NewNode=NULL; /* pointer to new node */
    char *someword=NULL;

    NewNode = (car*)malloc(sizeof(car));
    someword=(char*)malloc((slen+1)*sizeof(char));
    if(NewNode&&someword)
    {
        NewNode->id = 1;
        strcpy(someword, bname);
        NewNode->brandname=someword;
        NewNode->year = y;
        NewNode->mileage = m;
        NewNode->prev = NULL;
        NewNode->next = NULL;
    }
    return NewNode;
}
void AddFirst2(Head *MyHead, car *NewNode)
{
    MyHead->first = NewNode;
    MyHead->last = NewNode;
    MyHead->cnt++;
}

void AddLast2(Head *MyHead, car *NewNode, car *PrevNode)
{
    int n;

    if(MyHead&&NewNode&&PrevNode)
    {
        n=MyHead->cnt+1;
        PrevNode->next=NewNode;
        NewNode->prev=PrevNode;
        MyHead->last=NewNode;
        NewNode->id=n;
        MyHead->cnt=n;
    }
}

void InsertAfter2(Head *MyHead, car *NewNode, car *CurrentNode)
{
    int n;
    car* q = NULL;
    if(MyHead&&NewNode&&CurrentNode)
    {
        n=MyHead->cnt+1;
        if(CurrentNode->next==NULL)
        {
            CurrentNode->next=NewNode;
            NewNode->prev=CurrentNode;
            MyHead->last=NewNode;
        }
        else
        {
            q = CurrentNode->next;
            NewNode->next = CurrentNode->next;
            CurrentNode->next=NewNode;
            NewNode->prev=CurrentNode;
            q->prev = NewNode;
        }
        NewNode->id=n;
        MyHead->cnt=n;
    }
}

void InsertBefore2(Head *MyHead, car *NewNode, car *CurrentNode)
{
    car *q=NULL;
    int n;

    if(MyHead&&NewNode&&CurrentNode)
    {
        if(MyHead->first==CurrentNode)
        {
            NewNode->next=CurrentNode;
            CurrentNode->prev=NewNode;
            MyHead->first=NewNode;
        }
        else
        {
            q=CurrentNode->prev;
            NewNode->next=CurrentNode;
            NewNode->prev=q;
            q->next=NewNode;
            CurrentNode->prev=NewNode;
        }
        n=MyHead->cnt+1;
        NewNode->id=n;
        MyHead->cnt=n;
    }
}

car* SelectByOrder(Head* MyHead, int n)
{
    car* q;
    int k;
    k = MyHead->cnt;
    q = MyHead->first;
    if ((n > 0) && (n < (k+1)))
    {
        for (int i = 1; i < n; i++) q = q->next;
    }
    else q = NULL;
    return q;
}

int number_cars(Head* MyHead)
{
    car* p;
    int n = 0;
    p = MyHead->first;
    while (p!=NULL)
    {
        p = p->next;
        n++;
    }
    return n;
}

void autoinkAll(Head* MyHead)
{
    car * p;
    p = MyHead->first;
    p = p->next;
    while (p!=NULL)
    {
        p->id++;
        p = p->next;
    }
}

void autoinkN(Head* MyHead, int n)
{
    car * p;
    p = MyHead->first;
    while (p!=NULL)
    {
        if (p->id >= n) p->id++;
        p = p->next;
    }
}

car* readFromFile2(FILE* file, Head* MyHead){
    car *p = NULL;
    if (file != NULL){
        car *MyNode;
        char brand[MS];
        int slen, y, m;
        char tmp[1024];
        int boolFlag = -1;
        while (fgets(tmp, 1024, file)) {
            boolFlag++;
            int count = 0;
            char* lexeme = strtok(tmp, ";");
            while (lexeme!=NULL){
                switch (count){
                    case 0:
                        strcpy(brand, lexeme);
                        slen = strlen(brand);
                        break;
                    case 1:
                        y = atoi(lexeme);
                        break;
                    case 2:
                        m = atoi(lexeme);
                        break;
                }
                lexeme = strtok(NULL, ";");
                count++;
            }
            if (boolFlag == 0) {
                p = CreateNode2(brand, slen, y, m);
                AddFirst2(MyHead, p);
                p = MyHead->first;
            }
            else{
                MyNode = CreateNode2(brand, slen, y, m);
                InsertAfter2(MyHead, MyNode, p);
                p = MyNode;
            }
        }
    }
    else puts("Problems with input file");
    return p;
}

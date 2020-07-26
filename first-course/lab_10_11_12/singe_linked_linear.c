#include "singe_linked_linear.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MS 64


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

car *CreateNode(char *bname, int slen, int y, int m)
{
    car *NewNode=NULL; /* pointer to new node */
    char *word;
    NewNode = (car*)malloc(sizeof(car));
    word=(char*)malloc((slen+1)*sizeof(char));
    if(NewNode&&word)
    {
        NewNode->id = 1;    /* setting node ID to 1 */
        memcpy(word, bname, slen+1);
        NewNode->brandname=word;
        NewNode->year = y;
        NewNode->mileage = m;

        NewNode->next = NULL;           /* next node is absent */
    }
    return NewNode;  /* return of node address */
}

void AddFirst(Head *MyHead, car *newcar)
{
    if(MyHead&&newcar)
    {
        MyHead->first = newcar;
        MyHead->last = newcar;
        MyHead->cnt++;
    }
}

void InsertAfter(Head *MyHead, car *NewNode, car *CurrentNode)
{
    int n;
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
            NewNode->next = CurrentNode->next;
            CurrentNode->next=NewNode;
        }
        NewNode->id=n;
        MyHead->cnt=n;
    }
}

int compareVozr(const void * x1, const void * x2)
{
    return ( *(int*)x1 - *(int*)x2 );
}

car* readFromFile(FILE* file, Head* MyHead){
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
                p = CreateNode(brand, slen, y, m);
                AddFirst(MyHead, p);
                p = MyHead->first;
            }
            else{
                MyNode = CreateNode(brand, slen, y, m);
                InsertAfter(MyHead, MyNode, p);
                p = MyNode;
            }
        }
    }
    else puts("Problems with input file");
    return p;
}

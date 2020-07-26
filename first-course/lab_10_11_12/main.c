#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MS 64
#include "singe_linked_linear.h"
#include "doubly_linked_linear.h"
#include "single_linked_circular.h"

void single_linear();
void doubly_linear();
void single_circular();

int main(){
    int mode;
    int successful = 0;

    puts("Select lab:");
    puts("Enter 1 for 10 lab - single linked linear list");
    puts("Enter 2 for 11 lab - doubly linked linear list");
    puts("Enter 3 for 12 lab - single linked circular list");
    scanf("%d", &mode);
    while(!successful) {
        switch (mode) {
            case 1:
                single_linear();
                successful = 1;
                break;
            case 2:
                doubly_linear();
                successful = 1;
                break;
            case 3:
                single_circular();
                successful = 1;
                break;
            default:
                puts("You enter wrong number, please, enter again");
        }
    }

    return 0;
}

void single_linear()
{
    Head *p0, *np0;
    car *p, *np, *p1, *MyNode=NULL;
    char brand[MS];
    int slen, y, m;
    int  answer, n, flag = 1, flag2 = 0;
    int* array;
    FILE* pF = fopen("input.txt", "r");
    p0 = MakeHead();
    p = readFromFile(pF, p0);

    puts("Enter 1 to add elements or 0 to not add");
    scanf("%d", &answer);
    getchar();
    while (answer)
    {
        puts("Enter car brand");
        fgets(brand, MS, stdin);
        slen = strlen(brand);
        brand[slen-1] = '\0';
        puts("Enter car year");
        scanf("%d", &y);
        puts("Enter car mileage");
        scanf("%d", &m);
        MyNode = CreateNode(brand, slen, y, m);
        InsertAfter(p0, MyNode, p);
        p=MyNode;
        puts("Enter 1 if you want to continue, 0 to end");
        scanf("%d", &answer);
        getchar();
    }

    printf("\n--Input teminated. Your data are:--\n");

    p=p0->first;
    while(p!=NULL)
    {
        printf("id: %d; brandname: %s; year: %d; mileage: %d;\n", p->id, p->brandname, p->year, p->mileage);
        p=p->next;
    }

    puts("How many elements do you want to have in new List?");
    scanf("%d", &n);
    array = (int*)malloc(n*sizeof(int));
    for (int i = 0; i < n; i++)
    {
        printf("Enter the id, which you want to copy to new List\n");
        scanf("%d", &array[i]);
    }
    qsort(array, n, sizeof(int), compareVozr);

    np0 = MakeHead();
    p = p0->first;
    for (int i = 0; i < n; i++) {
        while (p != NULL) {
            if (p->id == array[i]) {
                flag2 = 1;
                if (flag) {
                    np = CreateNode(p->brandname, strlen(p->brandname), p->year, p->mileage);
                    AddFirst(np0, np);
                    flag = 0;
                    np = np0->first;
                } else {
                    MyNode = CreateNode(p->brandname, strlen(p->brandname), p->year, p->mileage);
                    InsertAfter(np0, MyNode, np);
                    np = MyNode;
                }
            }
            p = p->next;
        }
        if (!flag2) printf("The %d id was not found\n", array[i]);
        flag2 = 0;
        p = p0->first;
    }
    np = np0->first;
    if (np0->first != NULL) puts("New List:");
    while(np!=NULL)
    {
        printf("id: %d; brandname: %s; year: %d; mileage: %d;\n", np->id, np->brandname, np->year, np->mileage);
        np=np->next;
    }

    p = p0->first;
    while(p!=NULL)
    {
        p1=p->next;
        free(p);
        p=p1;
    }
    free(p0);

    np = np0->first;
    while(np!=NULL)
    {
        p1=np->next;
        free(np);
        np=p1;
    }
    free(np0);

    free(array);
    if(fclose(pF)==EOF)
        puts("Input closing error");
}

void doubly_linear()
{
    int slen, y, m, answer, search_id, position, n;
    Head* p0;
    car *p, *p1, *MyNode;
    char brand[MS];
    p0 = MakeHead2();
    FILE* pF = fopen("input.txt", "r");
    p = readFromFile2(pF, p0);

    puts("Enter 1 if you want to continue, 0 to end");
    scanf("%d", &answer);
    getchar();
    while (answer)
    {
        puts("Enter car brand");
        fgets(brand, MS, stdin);
        slen = strlen(brand);
        brand[slen-1] = '\0';
        puts("Enter car year");
        scanf("%d", &y);
        puts("Enter car mileage");
        scanf("%d", &m);
        MyNode = CreateNode2(brand, slen, y, m);
        InsertAfter2(p0, MyNode, p);
        p=MyNode;
        puts("Enter 1 if you want to continue, 0 to end");
        scanf("%d", &answer);
        getchar();
    }
    printf("\n--Input teminated. Your data are:--\n");

    p=p0->first;
    while(p!=NULL)
    {
        printf("id: %d; brandname: %s; year: %d; mileage: %d;\n", p->id, p->brandname, p->year, p->mileage);
        p=p->next;
    }

    n = number_cars(p0);
    puts("Choose the id");
    scanf("%d", &search_id);
    getchar();
    if (search_id < 1 || search_id > n) puts("This id does not exist.");
    else{
        MyNode = (car*)malloc(sizeof(car));
        MyNode = CreateNode2(SelectByOrder(p0, search_id)->brandname, strlen(SelectByOrder(p0, search_id)->brandname), SelectByOrder(p0, search_id)->year, SelectByOrder(p0, search_id)->mileage);
        puts("Choose the position");
        scanf("%d", &position);
        getchar();
        if (position < 0) puts("Wrong position");
        else
        {
            if (position == 0) {
                InsertBefore2(p0, MyNode, p0->first); p0->first->id = 1; autoinkAll(p0);
            }
            else if (position > n) {
                MyNode->next = NULL;  InsertAfter2(p0, MyNode, p0->last);
            }
            else{
                p = SelectByOrder(p0, position);
                InsertBefore2(p0, MyNode, p);
                autoinkN(p0, position);
                MyNode->id = position;
            }
        }

    }

    p=p0->first;
    while(p!=NULL)
    {
        printf("id: %d; brandname: %s; year: %d; mileage: %d;\n", p->id, p->brandname, p->year, p->mileage);
        p=p->next;
    }

    p=p0->first;
    while(p!=NULL)
    {
        p1=p->next;
        free(p);
        p=p1;
    }
    free(p0);
    if(fclose(pF)==EOF)
        puts("Input closing error");
}

void single_circular()
{
    Head *p0;
    car *p, *p1, *MyNode=NULL;
    char brand[MS];
    int slen, y, m, answer;
    FILE* pF = fopen("input.txt", "r");
    p0 = MakeHead_c();
    p = readFromFile_c(pF, p0);

    puts("Enter 1 if you want to continue, 0 to end");
    scanf("%d", &answer);
    getchar();
    while (answer)
    {
        puts("Enter car brand");
        fgets(brand, MS, stdin);
        slen = strlen(brand);
        brand[slen-1] = '\0';
        puts("Enter car year");
        scanf("%d", &y);
        puts("Enter car mileage");
        scanf("%d", &m);
        MyNode = CreateNode_c(brand, slen, y, m);
        InsertAfter_c(p0, MyNode, p);
        p=MyNode;
        puts("Enter 1 if you want to continue, 0 to end");
        scanf("%d", &answer);
        getchar();
    }
    printf("\n--Input teminated. Your data are:--\n");

    p=p0->first;
    while(p!=NULL)
    {
        printf("id: %d; brandname: %s; year: %d; mileage: %d;\n", p->id, p->brandname, p->year, p->mileage);
        p=p->next;
    }

    makeCircular_c(p0);
    int n = p0->cnt;
    if (n == 1) puts("You have only 1 element in list.");
    else{
        p = p0->first;
        while (p->id != n-1)
            p=p->next;
        deleteSelected_c(p0, p);
        puts("Deletion complete");
        puts("New list: ");
        p=p0->first;
        do
        {
            printf("id: %d; brandname: %s; year: %d; mileage: %d;\n", p->id, p->brandname, p->year, p->mileage);
            p=p->next;
        }while(p!=p0->last->next);
    }

    p0->last->next=NULL;
    p = p0->first;
    while(p!=NULL)
    {
        p1=p->next;
        free(p);
        p=p1;
    }
    free(p0);
    if(fclose(pF)==EOF)
        puts("Input closing error");
}


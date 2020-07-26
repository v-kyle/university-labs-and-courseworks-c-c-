#include "file_actions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "type_car.h"
#include "single_linear.h"
#define FILENAME "input.txt"
#define ML 255

car* readFromFile(Head* MyHead){
    FILE* file = fopen(FILENAME, "r");
    car *p = NULL;
    if (file != NULL){
        car *MyNode;
        char b_name[ML];
        char m_name[ML];
        int b_len;
        int m_len;
        int year = 0, mileage = 0, maxSpeed = 0, condition = 0;
        char tmp[1024];
        int boolFlag = -1;
        while (fgets(tmp, 1024, file)) {
            boolFlag++;
            int count = 0;
            char* lexeme = strtok(tmp, ";");
            while (lexeme!=NULL){
                switch (count){
                    case 0:
                        strcpy(b_name, lexeme);
                        break;
                    case 1:
                        strcpy(m_name, lexeme);
                        break;
                    case 2:
                        year = atoi(lexeme);
                        break;
                    case 3:
                        mileage = atoi(lexeme);
                        break;
                    case 4:
                        maxSpeed = atoi(lexeme);
                        break;
                    case 5:
                        condition = atoi(lexeme);
                        break;
                }
                lexeme = strtok(NULL, ";");
                count++;
            }
            if (boolFlag == 0) {
                p = CreateNode(b_name, m_name, year, mileage, maxSpeed, condition);
                AddFirst(MyHead, p);
                p = MyHead->first;
            }
            else{
                MyNode = CreateNode(b_name, m_name, year, mileage, maxSpeed, condition);
                InsertAfter(MyHead, MyNode, p);
                p = MyNode;
            }
        }
    }
    else puts("Problems with input file");


    if(fclose(file)==EOF)
        puts("Input closing error");
    return p;
}

int saveToFile(Head* MyHead){
    int rtn = 1;
    car* p = MyHead->first;
    FILE *file = fopen("input.txt", "w");
    if (p && file) {
        while(p != NULL){
            fprintf(file, "%s;%s;%d;%d;%d;%d;\n", p->brand, p->model, p->year, p->mileage, p->maxSpeed, p->condition);
            p = p->next;
        }

    }
    else rtn = 0;
    if(fclose(file)==EOF)
        puts("Input closing error");
    return rtn;
}
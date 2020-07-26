#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/type_car.h"
#include "headers/single_linear.h"
#include "headers/file_actions.h"
#include "headers/interaction.h"

int main(){
    int userAnswerInt;
    int exitFlag = 1;
    Head* p0 = MakeHead();
    readFromFile(p0);

    outHelp();
    while(exitFlag) {
        userAnswerInt = smartInt(1);
        switch (userAnswerInt){
            case -1:
                outS0();
                exitFlag = 0;
                break;
            case 1:
                outS1();
                showAll(p0);
                break;
            case 2:
                outS2();
                AddLast(p0, inputData());
                break;
            case 3:
                outS3();
                if (deleteSelected(p0, SelectById(p0, smartInt(10), 1))) puts("Delete successfully");
                else outWrong();
                break;
            case 4:
                outS4();
                editNode(SelectById(p0, smartInt(10), 1));
                break;
            case 5:
                outS5();
                searchNode(p0);
                break;
            case 6:
                outS6();
                sortList(p0);
                break;
            case 7:
                outS7(saveToFile(p0));
                break;
            case 8:
                outHelp();
                break;
            default:
                outWrong();
        }
    }

    return 0;
}
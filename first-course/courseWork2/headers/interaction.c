#include "interaction.h"
#include "type_car.h"
#include <stdio.h>
#include <stdlib.h>

void outHelp(){
    puts("Hello! Welcome to the electronic filing of vintage cars museum!");
    puts("To interact with the program, press the key with the corresponding number from the menu.");
    puts("1 - Show the entire list of cars.");
    puts("2 - Add a new car to the list.");
    puts("3 - Delete the car from the list.");
    puts("4 - Edit the car record.");
    puts("5 - Search car record.");
    puts("6 - Sort the list.");
    puts("7 - Save the updated list to a file.");
    puts("8 - Display Help.");
    puts("0 - Exit");
}
void outWrong(){
    puts("Input error, try again.");
}

void outFields(){
    puts("1 - car brand");
    puts("2 - car model");
    puts("3 - car production year");
    puts("4 - car mileage");
    puts("5 - car max speed");
    puts("6 - car condition");
}

void outS1(){
    puts("Entire list of cars:");
}
void outS2(){
    puts("Fill in the car data:");
}
void outS3(){
    puts("Enter the id of the car, which you want to delete:");
};
void outS4(){
    puts("Enter the id of the car, which you want to edit:");
}
void outS5(){
    puts("Select the field, which you want to use for the search:");
}
void outS6(){
    puts("Select the field, which you want to use for the sorting:");
}
void outS7(int q){
    if (q==1) puts("You list was saved.");
    else puts("You list was not saved!!!");
}
void outS0(){
    puts("GoodBye!!!");
}

int smartInt(int len){
    char userAnswer[255];
    int userAnswerInt;

    fgets(userAnswer, 255, stdin);
    while (strlen(userAnswer) > (len+1)){
        outWrong();
        fgets(userAnswer, 255, stdin);
    }
    userAnswer[strlen(userAnswer)-1] = '\0';
    if (userAnswer[0] == '0') userAnswerInt = -1;
    else userAnswerInt = atoi(userAnswer);

    return userAnswerInt;
}
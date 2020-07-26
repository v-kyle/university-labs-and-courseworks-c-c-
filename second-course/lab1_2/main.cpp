#include <iostream>
#include <time.h>

#include "SetArray.h"
#include "SetList.h"
#include "SetBinary.h"
#include "SetMachine.h"

#define RANDOM_SIZE 8
#define TESTS 1000000

using namespace std;

void realisationArray(const string &enter) {
    SetArray A('A'), B('B'), C('C'), D('D'), E('E');

    if (enter == "1") {
        A.randomEnter(RANDOM_SIZE);
        B.randomEnter(RANDOM_SIZE);
        C.randomEnter(RANDOM_SIZE);
        D.randomEnter(RANDOM_SIZE);
    } else {
        A.handEnter();
        B.handEnter();
        C.handEnter();
        D.handEnter();
    }

    auto start = clock();
    for (int i = 0; i < TESTS; ++i) {
        E |= A & (B & C).invert();
        E |= D;
    }
    auto stop = clock();
    double time = (stop - start) / (double) CLOCKS_PER_SEC;

    A.print();
    B.print();
    C.print();
    D.print();
    E.print();
    cout << "Time: " << time << "/" << TESTS << endl;
}

void realisationList(const string &enter) {
    SetList A('A'), B('B'), C('C'), D('D'), E('E');

    if (enter == "1") {
        A.randomEnter(RANDOM_SIZE);
        B.randomEnter(RANDOM_SIZE);
        C.randomEnter(RANDOM_SIZE);
        D.randomEnter(RANDOM_SIZE);
    } else {
        A.handEnter();
        B.handEnter();
        C.handEnter();
        D.handEnter();
    }

    auto start = clock();
    for (int i = 0; i < TESTS; ++i) {
        E |= A & (B & C).invert();
        E |= D;
    }
    auto stop = clock();
    double time = (stop - start) / (double) CLOCKS_PER_SEC;

    A.print();
    B.print();
    C.print();
    D.print();
    E.print();
    cout << "Time: " << time << "/" << TESTS << endl;
}

void realisationBinary(const string &enter) {
    SetBinary A('A'), B('B'), C('C'), D('D'), E('E');

    if (enter == "1") {
        A.randomEnter(RANDOM_SIZE);
        B.randomEnter(RANDOM_SIZE);
        C.randomEnter(RANDOM_SIZE);
        D.randomEnter(RANDOM_SIZE);
    } else {
        A.handEnter();
        B.handEnter();
        C.handEnter();
        D.handEnter();
    }

    auto start = clock();
    for (int i = 0; i < TESTS; ++i) {
        E |= A & (B & C).invert();
        E |= D;
    }
    auto stop = clock();
    double time = (stop - start) / (double) CLOCKS_PER_SEC;

    A.print();
    B.print();
    C.print();
    D.print();
    E.print();
    cout << "Time: " << time << "/" << TESTS << endl;
}

void realisationMachine(const string &enter) {
    SetMachine A('A'), B('B'), C('C'), D('D'), E('E');

    if (enter == "1") {
        A.randomEnter(RANDOM_SIZE);
        B.randomEnter(RANDOM_SIZE);
        C.randomEnter(RANDOM_SIZE);
        D.randomEnter(RANDOM_SIZE);
    } else {
        A.handEnter();
        B.handEnter();
        C.handEnter();
        D.handEnter();
    }

    auto start = clock();
    for (int i = 0; i < TESTS; ++i) {
        E |= A & (B & C).invert();
        E |= D;
    }
    auto stop = clock();
    double time = (stop - start) / (double) CLOCKS_PER_SEC;

    A.print();
    B.print();
    C.print();
    D.print();
    E.print();
    cout << "Time: " << time << "/" << TESTS << endl;
}

int main() {
    srand(time(NULL));

    string realisation, enter;
    do {
        cout << "\nEnter type of realisation (1 - array, 2 - list, 3 - binary, 4 - machine) : ";
        cin >> realisation;
    }
    while(realisation != "1" && realisation != "2" && realisation != "3" && realisation != "4");
    do {
        cout << "\nEnter type of enter data (1 - random, 2 - hand) : ";
        cin >> enter;
    }
    while(enter != "1" && enter != "2");

    if(realisation == "1") {
        realisationArray(enter);
    } else if(realisation == "2") {
        realisationList(enter);
    } else if(realisation == "3") {
        realisationBinary(enter);
    } else {
        realisationMachine(enter);
    }
    return 0;
}
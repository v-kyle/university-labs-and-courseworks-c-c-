#include <iostream>
#include <limits>
#include "SetMachine.h"

using namespace std;

char universumMachine[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                         'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

SetMachine::SetMachine(char C) {
    n = 0;
    TAG = C;
}

SetMachine SetMachine::copy() const {
    SetMachine set = SetMachine(this->TAG);
    set.n = this->n;
    set.container = this->container;
    return set;
}

bool SetMachine::add(char C) {
    int k;
    for (k = 0; C != universumMachine[k]; ++k) {}
    if(bool((1 << k)  &  container)) {
        return false;
    }
    container ^= (1 << k);
    n++;
    return true;
}

int SetMachine::getSize() {
    return this->n;
}

void SetMachine::print() {
    cout << this->TAG << " = [";
    for (int i = 0; i < SetMachine::N; i++) {
        if ((container >> i & 1)) {
            cout << universumMachine[i];
        }
    }
    cout << "]" << endl;
}

SetMachine &SetMachine::operator|=(const SetMachine &B) {
    this->container |= B.container;
    return *this;
}

SetMachine SetMachine::operator|(const SetMachine &B) const {
    SetMachine copy = this->copy();
    return copy |= B;
}

SetMachine &SetMachine::operator&=(const SetMachine &B) {
    this->container &= B.container;
    return *this;
}

SetMachine SetMachine::operator&(const SetMachine &B) const {
    SetMachine copy = this->copy();
    return copy &= B;
}

SetMachine SetMachine::invert() {
    this->container = ~this->container;
    return *this;
}

void SetMachine::handEnter() {
    int t;
    char c;
    do {
        cout << "\nEnter size of SetMachine: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } while (!(cin >> t));

    while (getSize() < t) {
        do {
            cout << this->TAG << "[" << getSize() + 1 << "]: ";
            cin.clear();
        } while (!(cin >> c));
        add(c);
    }
}

void SetMachine::randomEnter(int n) {
    for (int j = 0; j < n; j++) {
        while (getSize() < n) {
            char c = universumMachine[rand() % SetMachine::N];
            add(c);
        }
    }
}

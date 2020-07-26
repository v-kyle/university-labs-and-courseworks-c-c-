#include "SetArray.h"
#include <iostream>
#include <limits>

using namespace std;

char universumArray[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                         'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

SetArray::SetArray(char C) {
    n = 0;
    TAG = C;
    container = new char[N];
}

SetArray SetArray::copy() const {
    SetArray set = SetArray(this->TAG);
    set.n = this->n;
    set.container = new char[N];
    for(int i = 0; i < set.n; i++) {
        set.container[i] = this->container[i];
    }
    return set;
}

bool SetArray::check(char C) const {
    for (int i = 0; i < this->n; i++) {
        if(this->container[i] == C)
            return false;
    }
    for (int i = 0; i < SetArray::N; i++) {
        if(universumArray[i] == C)
            return true;
    }
    return false;
}

void SetArray::add(char C) {
    if(!check(C))
        return;

    this->container[n] = C;
    this->n++;
}

int SetArray::getSize() {
    return this->n;
}

void SetArray::print() {
    cout << this->TAG << " = [";
    for (int i = 0; i < this->n; ++i) {
        cout << this->container[i];
    }
    cout << "]" << endl;
}

SetArray& SetArray::operator|=(const SetArray &B) {
    for (int i = 0; i < B.n; ++i) {
        if(this->check(B.container[i])) {
            this->container[n] = B.container[i];
            this->n++;
        }
    }
    return *this;
}

SetArray SetArray::operator|(const SetArray &B) const {
    SetArray copy = this->copy();
    return copy |= B;
}

SetArray& SetArray::operator&=(const SetArray &B) {
    SetArray temp = B.copy();

    for (int i = 0; i < temp.n; ++i) {
        if(this->check(temp.container[i])) {
            temp.container[i] = '\0';
        }
    }

    this->container = new char[N];
    this->n = 0;

    for (int j = 0; j < temp.n; ++j) {
        if(temp.container[j] != '\0') {
            this->container[this->n] = temp.container[j];
            this->n++;
        }
    }
    return *this;
}

SetArray SetArray::operator&(const SetArray &B) const {
    SetArray copy = this->copy();
    return copy &= B;
}

SetArray SetArray::invert() {
    SetArray temp = this->copy();
    this->n = 0;
    for (int i = 0; i < N; ++i) {
        if(temp.check(universumArray[i])) {
            this->container[n] = universumArray[i];
            this->n++;
        }
    }
    return *this;
}

void SetArray::handEnter() {
    int t;
    char c;
    do {
        cout << "\nEnter size of SetArray: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } while(!(cin >> t));

    while(getSize() < t) {
        do {
            cout << this->TAG << "[" << getSize() + 1 << "]: ";
            cin.clear();
        } while (!(cin >> c));
        add(c);
    }
}

void SetArray::randomEnter(int n) {
    for (int j = 0; j < n; j++) {
        while (getSize() < n) {
            char c = universumArray[rand() % SetArray::N];
            add(c);
        }
    }
}

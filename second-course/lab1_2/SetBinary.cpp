#include "SetBinary.h"
#include <iostream>
#include <limits>

using namespace std;

char universumBinary[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                         'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

SetBinary::SetBinary(char C) {
    n = 0;
    TAG = C;
    container = new bool[N];
    for (int i = 0; i < N; ++i) {
        container[i] = false;
    }
}

SetBinary SetBinary::copy() const {
    SetBinary set = SetBinary(this->TAG);
    set.n = this->n;
    set.container = new bool[N];
    for (int i = 0; i < SetBinary::N; i++) {
        set.container[i] = this->container[i];
    }
    return set;
}

bool SetBinary::add(char C) {
    int k;
    for (k = 0; universumBinary[k] != C; k++) {};
    if(container[k]) {
        return false;
    }
    container[k] = true;
    n++;
    return true;
}

int SetBinary::getSize() {
    return this->n;
}

void SetBinary::print() {
    cout << this->TAG << " = [";
    for (int i = 0; i < SetBinary::N; ++i) {
        if (container[i])
            cout << universumBinary[i];
    }
    cout << "]" << endl;
}

SetBinary &SetBinary::operator|=(const SetBinary &B) {
    for (int i = 0; i < SetBinary::N; ++i) {
        this->container[i] |= B.container[i];
    }
    return *this;
}

SetBinary SetBinary::operator|(const SetBinary &B) const {
    SetBinary copy = this->copy();
    return copy |= B;
}

SetBinary &SetBinary::operator&=(const SetBinary &B) {
    for (int i = 0; i < SetBinary::N; ++i) {
        this->container[i] &= B.container[i];
    }
    return *this;
}

SetBinary SetBinary::operator&(const SetBinary &B) const {
    SetBinary copy = this->copy();
    return copy &= B;
}

SetBinary SetBinary::invert() {
    for (int i = 0; i < this->n; ++i) {
        container[i] = !container[i];
    }
    return *this;
}

void SetBinary::handEnter() {
    int t;
    char c;
    do {
        cout << "\nEnter size of SetBinary: ";
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

void SetBinary::randomEnter(int n) {
    for (int j = 0; j < n; j++) {
        while (getSize() < n) {
            char c = universumBinary[rand() % SetBinary::N];
            add(c);
        }
    }
}

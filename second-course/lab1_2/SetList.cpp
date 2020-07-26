#include <iostream>
#include <limits>
#include "SetList.h"

using namespace std;

char universumList[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                         'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

SetList::SetList(char C) {
    n = 0;
    TAG = C;
    list = new List();
}

SetList SetList::copy() const {
    SetList set = SetList(this->TAG);
    set.n = this->n;
    set.list = new List;
    for(List *p = list; p; p = p->next) {
        set.add(p->c);
    }
    return set;
}

bool SetList::check(char C) const {
    for (List *p = list; p; p = p->next) {
        if (p->c == C)
            return false;
    }

    for (int i = 0; i < SetList::N; i++) {
        if(universumList[i] == C)
            return true;
    }

    return false;
}

void SetList::add(char C) {
    if (!check(C))
        return;
    this->n++;

    if (list->c == '\0') {
        list->c = C;
        return;
    }

    for (List *p = list; p; p = p->next) {
        if (p->next == nullptr) {
            List *current = new List;
            current->c = C;
            p->next = current;
            break;
        }
    }
}

int SetList::getSize() {
    return this->n;
}

void SetList::print() {
    cout << this->TAG << " = [";
    for (List *p = list; p; p = p->next) {
        cout << p->c;
    }
    cout << "]" << endl;
}

SetList& SetList::operator|=(const SetList &B) {
    for (List *p = B.list; p; p = p->next) {
        if(this->check(p->c)) {
            add(p->c);
            this->n++;
        }
    }
    return *this;
}

SetList SetList::operator|(const SetList &B) const {
    SetList copy = this->copy();
    return copy |= B;
}

SetList& SetList::operator&=(const SetList &B) {
    SetList temp = B.copy();

    for (List *p = temp.list; p; p = p->next) {
        if(this->check(p->c)) {
            p->c = '\0';
        }
    }

    this->list = new List;
    this->n = 0;

    for (List *p = temp.list; p; p = p->next) {
        if(p->c != '\0') {
            this->add(p->c);
            this->n++;
        }
    }
    return *this;
}

SetList SetList::operator&(const SetList &B) const {
    SetList copy = this->copy();
    return copy &= B;
}

SetList SetList::invert() {
    SetList temp = this->copy();
    this->list = new List();
    for (int i = 0; i < N; ++i) {
        if(temp.check(universumList[i])) {
            this->add(universumList[i]);
        }
    }
    return *this;
}

void SetList::handEnter() {
    int t;
    char c;
    do {
        cout << "\nEnter size of SetList: ";
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

void SetList::randomEnter(int n) {
    for (int j = 0; j < n; j++) {
        while (getSize() < n) {
            char c = universumList[rand() % SetList::N];
            add(c);
        }
    }
}

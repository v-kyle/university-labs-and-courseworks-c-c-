#ifndef LAB_2_SETLIST_H
#define LAB_2_SETLIST_H

struct List {
    char c = '\0';
    List *next = nullptr;
};

class SetList {
private:
    static const int N = 16;
    int n;
    char TAG;
    List *list;
public:
    explicit SetList(char);
    SetList operator | (const SetList&) const;
    SetList& operator |= (const SetList&);
    SetList operator & (const SetList&) const;
    SetList& operator &= (const SetList&);
    SetList invert();
    SetList copy() const;
    bool check(char) const;
    void add(char);
    int getSize();
    void print();
    void handEnter();
    void randomEnter(int n);
};


#endif //LAB_2_SETLIST_H

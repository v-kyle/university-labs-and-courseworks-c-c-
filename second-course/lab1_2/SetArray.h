#ifndef LAB_2_SETARRAY_H
#define LAB_2_SETARRAY_H

class SetArray {
private:
    static const int N = 16;
    int n;
    char TAG;
    char *container;
public:
    explicit SetArray(char);
    SetArray operator | (const SetArray&) const;
    SetArray& operator |= (const SetArray&);
    SetArray operator & (const SetArray&) const;
    SetArray& operator &= (const SetArray&);
    SetArray invert();
    SetArray copy() const;
    bool check(char) const;
    void add(char);
    int getSize();
    void print();
    void handEnter();
    void randomEnter(int n);
};

#endif //LAB_2_SETARRAY_H

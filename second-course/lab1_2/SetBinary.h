#ifndef LAB_2_SETBINARY_H
#define LAB_2_SETBINARY_H


class SetBinary {
private:
    static const int N = 16;
    int n;
    char TAG;
    bool *container;
public:
    explicit SetBinary(char);
    SetBinary operator | (const SetBinary&) const;
    SetBinary& operator |= (const SetBinary&);
    SetBinary operator & (const SetBinary&) const;
    SetBinary& operator &= (const SetBinary&);
    SetBinary invert();
    SetBinary copy() const;
    bool check(char) const;
    bool add(char);
    int getSize();
    void print();
    void handEnter();
    void randomEnter(int n);
};

#endif //LAB_2_SETBINARY_H

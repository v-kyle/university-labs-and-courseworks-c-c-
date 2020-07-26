#ifndef LAB_2_SETMACHINE_H
#define LAB_2_SETMACHINE_H


class SetMachine {
private:
    static const int N = 16;
    int n;
    char TAG;
    long container = 0;
public:
    explicit SetMachine(char);
    SetMachine operator | (const SetMachine&) const;
    SetMachine& operator |= (const SetMachine&);
    SetMachine operator & (const SetMachine&) const;
    SetMachine& operator &= (const SetMachine&);
    SetMachine invert();
    SetMachine copy() const;
    bool add(char);
    int getSize();
    void print();
    void handEnter();
    void randomEnter(int n);
};


#endif //LAB_2_SETMACHINE_H

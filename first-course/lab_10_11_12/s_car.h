#ifndef LABS_10_12_S_CAR_H
#define LABS_10_12_S_CAR_H

struct s_car
{
    int id;
    char* brandname;
    int year;
    int mileage;
    struct s_car* next;
    struct s_car* prev;
};

struct LHead {
    int cnt;
    struct s_car *first;
    struct s_car *last;
};

typedef struct LHead Head;
typedef struct s_car car;

#endif //LABS_10_12_S_CAR_H

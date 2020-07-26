#ifndef COURSE_WORK_2SEM_TYPE_CAR_H
#define COURSE_WORK_2SEM_TYPE_CAR_H

struct s_car
{
    int id;
    char* brand;
    char* model;
    int year;
    int mileage;
    int maxSpeed;
    int condition;
    struct s_car* next;
};

struct LHead {
    int cnt;
    struct s_car *first;
    struct s_car *last;
};

typedef struct LHead Head;
typedef struct s_car car;

#endif //COURSE_WORK_2SEM_TYPE_CAR_H

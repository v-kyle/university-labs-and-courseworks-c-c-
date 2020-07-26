#include <stdio.h>
#include <stdlib.h>

struct BP
{
    unsigned char b1:8;
    unsigned char b2:8;
    unsigned char b3:8;
    unsigned char b4:8;
};

int inputByte(int* n);
unsigned char shift(unsigned char b, int positions);

int main() {
    struct BP Byte;
    int item;
    int positions;
    int n = 1;

    Byte.b1 = inputByte(&n);
    Byte.b2 = inputByte(&n);
    Byte.b3 = inputByte(&n);
    Byte.b4 = inputByte(&n);

    puts("What number do you want to use for cyclic shift? (1-4)");
    scanf("%d", &item);
    getchar();
    puts("How many positions to the left do you want to shift?");
    scanf("%d", &positions);
    getchar();
    positions = positions%8;
    switch (item){
        case 1:
            Byte.b1 = shift(Byte.b1, positions);
            break;
        case 2:
            Byte.b2 = shift(Byte.b2, positions);
            break;
        case 3:
            Byte.b3 = shift(Byte.b3, positions);
            break;
        case 4:
            Byte.b4 = shift(Byte.b4, positions);
            break;
        default:
            puts("Wrong Input");
    }
    printf("%x - first number\n%x - second number\n%x - third number\n%x - fourth number", Byte.b1,Byte.b2,Byte.b3,Byte.b4);

    return 0;
}

int inputByte(int* n){
    int tmp;
    printf("Enter the %d number in hexadecimal system (0-F)\n", *n);
    scanf("%x0", &tmp);
    getchar();
    *n = *n+1;
    return tmp;
}

unsigned char shift(unsigned char b, int positions){
    return b<<positions;
}

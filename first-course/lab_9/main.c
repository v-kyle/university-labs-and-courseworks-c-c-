#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MS 80
#define LINE 1024

struct car
{
    char* brandname;
    char* modelname;
    int year;
    int mileage;
    float capacity;
};

struct selected
{
    int* a;
    int w;
};

int number_of_lines(FILE* file);
void print_array(struct car* my_car, int t, struct selected (funcName)(struct car*, int));
struct selected select_year(struct car* my_car, int t);
struct selected select_mileage(struct car* my_car, int t);
struct selected select_capacity(struct car* my_car, int t);

int main()
{
    FILE* pF = fopen("input.txt", "r");
    struct car* my_car = NULL;
    struct car temp;
    int answer_add, answer_field;
    if(pF != NULL)
    {
        char text[LINE];
        int t = 0;
        int tt;
        t = number_of_lines(pF);
        my_car = (struct car*)malloc(t*sizeof(struct car));
        if (my_car != NULL)
        {
            for (int i = 0; i < t; i++)
            {
                fgets(text, LINE, pF);
                int q = 0;
                char *lexeme = strtok(text, ";");
                while(lexeme != NULL)
                {
                    switch (q)
                    {
                    case 0:
                        my_car[i].brandname = (char*)malloc(strlen(lexeme)*sizeof(char));
                        strcpy(my_car[i].brandname, lexeme);
                        break;
                    case 1:
                        my_car[i].modelname = (char*)malloc(strlen(lexeme)*sizeof(char));
                        strcpy(my_car[i].modelname, lexeme);
                        break;
                    case 2:
                        my_car[i].year = atoi(lexeme);
                        break;
                    case 3:
                        my_car[i].mileage = atoi(lexeme);
                        break;
                    case 4:
                        my_car[i].capacity = atof(lexeme);
                        break;
                    }
                    lexeme = strtok(NULL, ";");
                    q++;
                }
            }

            printf("List:\n");
            for (int i = 0; i < t; i++)
                printf("%s; %s; %d; %d; %.1f\n", my_car[i].brandname, my_car[i].modelname, my_car[i].year, my_car[i].mileage, my_car[i].capacity);
            puts("");

            printf("Do you want to add element? (0 - no, 1 - yes)\n");
            scanf("%d", &answer_add);
            getchar();
            while (answer_add)
            {
                t++;
                my_car = (struct car*)realloc(my_car, t*sizeof(struct car));
                if (my_car != NULL)
                {
                    tt = t -1;
                    puts("Enter brandname");
                    my_car[tt].brandname = (char*)malloc(MS*sizeof(char));
                    if (my_car[tt].brandname != NULL)
                    {
                        fgets(my_car[tt].brandname, MS, stdin);
                        my_car[tt].brandname[strlen(my_car[tt].brandname) - 1] = '\0';
                        puts("Enter modelname");
                        my_car[tt].modelname = (char*)malloc(MS*sizeof(char));
                        if (my_car[tt].modelname != NULL)
                        {
                            fgets(my_car[tt].modelname, MS, stdin);
                            my_car[tt].modelname[strlen(my_car[tt].modelname) - 1] = '\0';
                            puts("Enter year");
                            scanf("%d", &my_car[tt].year);
                            puts("Enter mileage");
                            scanf("%d", &my_car[tt].mileage);
                            puts("Enter capacity");
                            scanf("%f", &my_car[tt].capacity);
                            printf("Do you want to add element? (0 - no, 1 - yes)\n");
                            scanf("%d", &answer_add);
                            getchar();
                        }
                        else puts("Error Memory!!!");
                    }
                    else puts("Error Memory!!!");
                }
                else puts("Error Memory!");
            }

            for (int i = 0; i < t - 1; i++)
                for (int j = 0; j < t - i - 1; j++)
                    if (strcmp(my_car[j].modelname, my_car[j+1].modelname) < 0)
                    {
                        temp = my_car[j];
                        my_car[j] = my_car[j+1];
                        my_car[j+1] = temp;
                    }
            printf("\nNew sorted list:\n");
            for (int i = 0; i < t; i++)
                printf("%s; %s; %d; %d; %.1f\n", my_car[i].brandname, my_car[i].modelname, my_car[i].year, my_car[i].mileage, my_car[i].capacity);
            puts("");

            puts("Choose the field (1 - year, 2 - mileage, 3 - capacity):");
            scanf("%d", &answer_field);
            switch(answer_field)
            {
            case 1:
                print_array(my_car, t, select_year);
                break;
            case 2:
                print_array(my_car, t, select_mileage);
                break;
            case 3:
                print_array(my_car, t, select_capacity);
                break;
            }

            if(fclose(pF)==EOF)
                puts("Input closing error");
            for (int i = 0; i < t; i++)
            {
                free(my_car[i].modelname);
                free(my_car[i].brandname);
            }
            free(my_car);
        }
        else puts("Error Memory!");
    }

    else
        printf("Opening Error");

    return 0;
}

int number_of_lines(FILE* file)
{
    int t = 0;
    char text[LINE];
    while(fgets(text, LINE, file))
        t++;
    rewind(file);
    return t;
}

void print_array(struct car* my_car, int t, struct selected (*funcName)(struct car*, int))
{
    struct selected value;
    value = funcName(my_car, t);
    int i;
    int* array = value.a;
    if (value.w == 0) puts("Not Finding");
    else
    for (int j = 0; j < value.w; j++)
    {
        i = array[j];
        printf("%s; %s; %d; %d; %.1f\n", my_car[i].brandname, my_car[i].modelname, my_car[i].year, my_car[i].mileage, my_car[i].capacity);
    }
    free(array);
}

struct selected select_year(struct car* my_car, int t)
{
    int sum = 0;
    float mean;
    struct selected value;
    int *array = (int*)calloc(t, sizeof(int));
    if (array != NULL)
    {
        int k = 0;
        for (int i = 0; i < t; i++)
            sum+=my_car[i].year;
        mean = sum / t;
        printf("Mean value: %.1f\n", mean);
        for (int i = 0; i < t; i++)
            if (my_car[i].year <= mean)
            {
                array[k] = i;
                k++;
            }
        value.a = array;
        value.w = k;
    }
    else puts("Error Memory!");
    return value;
}

struct selected select_mileage(struct car* my_car, int t)
{
    int sum = 0;
    float mean;
    struct selected value;
    int *array = (int*)calloc(t, sizeof(int));
    if (array != NULL)
    {
        int k = 0;
        for (int i = 0; i < t; i++)
            sum+=my_car[i].mileage;
        mean = sum / t;
        printf("Mean value: %.1f\n", mean);
        for (int i = 0; i < t; i++)
            if (my_car[i].mileage <= mean)
            {
                array[k] = i;
                k++;
            }
        value.a = array;
        value.w = k;
    }
    else puts("Error Memory!");
    return value;
}

struct selected select_capacity(struct car* my_car, int t)
{
    float sum = 0;
    float mean;
    struct selected value;
    int *array = (int*)calloc(t, sizeof(int));
    if (array != NULL)
    {
        int k = 0;
        for (int i = 0; i < t; i++)
            sum+=my_car[i].capacity;
        mean = sum / t;
        printf("Mean value: %.1f\n", mean);
        for (int i = 0; i < t; i++)
            if (my_car[i].capacity <= mean)
            {
                array[k] = i;
                k++;
            }
        value.a = array;
        value.w = k;
    }
    else puts("Error Memory!");
    return value;
}

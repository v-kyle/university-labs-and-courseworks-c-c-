#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
int main()
{
    setlocale(LC_ALL, "RUS");
    int **a;
    int *b;
    int i, j, n, m, A, B, u = 0, flag = 1, kk = 0;
    float s = 0;
    puts("Кол-во строк:");
    scanf("%d", &n);
    puts("Кол-во столбцов:");
    scanf("%d", &m);
    puts("Значение A:");
    scanf("%d", &A);
    puts("Значение B:");
    scanf("%d", &B);
    if(!(a = (int**)malloc(n * sizeof(int*))))
    {
        puts("Ошибка выделения памяти");
        for (i = 0; i < n; i++)
            free(a[i]);
        free(a);
        free(b);
        return 1;
    }
    else
    {
        for (i = 0; i < n; i++)
        {
            if(!(a[i] = (int*)malloc(m * sizeof(int))))
            {
                puts("Ошибка выделения памяти");
                for (i = 0; i < n; i++)
                    free(a[i]);
                free(a);
                free(b);
                return 1;
            }
            else
            {
                for (j = 0; j < m; j++)
                {
                    scanf("%d", &a[i][j]);
                    if (a[i][j] >= A && a[i][j] <= B)
                        u++;
                }
                if (flag ==1)
                    b = (int*)malloc(u * sizeof(int));
                if(!(a[i]))
                {
                    puts("Ошибка выделения памяти");
                    for (i = 0; i < n; i++)
                        free(a[i]);
                    free(a);
                    free(b);
                    return 1;
                }
                else
                {
                    for (j = 0; j < m; j++)
                    {
                        if (a[i][j] >= A && a[i][j] <= B)
                        {
                            b[kk] = a[i][j];
                            kk++;
                        }
                    }
                    flag = 0;
                }
            }
        }
        for (i = 0; i < u; i++)
            s+=b[i];
        if (u>0)
        {
            s = s/u;
            printf("Среднее значение одномерного массива: %.2f", s);
        }
        else
            printf("Массив пуст");
    }
    for (i = 0; i < n; i++)
        free(a[i]);
    free(a);
    free(b);
    return 0;
}

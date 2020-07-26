#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <limits.h>

int firststr(int km, int *b)
{
    int mx = INT_MIN;
    for (int j = 0; j < km; j++)
    {
        printf("Введите [0, %d] элемент ", j);
        scanf("%d", &b[j]);
        if (abs(b[j]) > mx)
            mx = abs(b[j]);
    }
    return mx;
}
void nextstr(int **b, int kn, int km)
{
    for (int i = 1; i < kn; i++)
    {
        if(!(b[i] = (int*)malloc(km * sizeof(int))))
        {
            puts("Ошибка выделения памяти");
        }
        else
        {
            for (int j = 0; j < km; j++)
            {
                printf("Введите [%d, %d] элемент ", i, j);
                scanf("%d", &b[i][j]);
            }
        }
    }
}
int** transp(int** b, int kn, int km)
{
    int **c;
    if(!(c = (int**)malloc(km*sizeof(int*))))
    {
        puts("Ошибка выделения памяти");
    }
    else
    {
        for (int i = 0; i < km; i++)
        {
            if(!(c[i]=(int*)malloc(kn*sizeof(int))))
            {
                puts("Ошибка выделения памяти");
            }
            else
            {
                for (int j = 0; j < kn; j++)
                    c[i][j]=b[j][i];
            }
        }
    }
    return c;
}
int newmatrix(int **b, int kn, int km, int **nmat)
{
    int i,j,l;
    int uu = 1;
    if(!(nmat = (int**)malloc(uu*sizeof(int*))))
    {
        puts("Ошибка выделения памяти");
    }
    else
    {
        int k = 0;
        for (i = 0; i < kn; i++)
        {
            for (j = 0; j < km-1; j++)
                if (b[i][j+1] >= b[i][j])
                    k++;
            if (k == (km-1))
            {
                uu++;
                if(!(nmat = (int**)realloc(nmat,uu*sizeof(int*))))
                {
                    puts("Ошибка выделения памяти");
                }
                else
                {
                    if(!(nmat[uu-2] = (int*)malloc(km*sizeof(int))))
                    {
                        puts("Ошибка выделения памяти");
                    }
                    else
                    {
                        for (l = 0; l < km; l++)
                            nmat[uu-2][l] = b[i][l];
                    }
                    k = 0;
                }
            }
        }
    }
    return uu-1;
}
int** newmatrix2(int **b, int kn, int km)
{
    int i,j,l;
    int uu = 1;
    int** nmat;
    if(!(nmat = (int**)malloc(uu*sizeof(int*))))
    {
        puts("Ошибка выделения памяти");
    }
    else
    {
        int k = 0;
        for (i = 0; i < kn; i++)
        {
            for (j = 0; j < km-1; j++)
                if (b[i][j+1] >= b[i][j])
                    k++;
            if (k == (km-1))
            {
                uu++;
                if(!(nmat = (int**)realloc(nmat,uu*sizeof(int*))))
                {
                    puts("Ошибка выделения памяти");
                }
                else
                {
                    if(!(nmat[uu-2] = (int*)malloc(km*sizeof(int))))
                    {
                        puts("Ошибка выделения памяти");
                    }
                    else
                    {
                        for (l = 0; l < km; l++)
                            nmat[uu-2][l] = b[i][l];
                    }
                    k = 0;
                }
            }
        }
    }
    return nmat;
}
int main()
{
    setlocale(LC_ALL, "RUS");
    int **a;
    int **c;
    int **d;
    int i, j, n, m, nn;
    puts("Введите кол-во столбцов");
    scanf("%d", &m);
    while (m < 1)
    {
        puts("Некоректный ввод кол-ва столбцов, повторите попытку");
        scanf("%d", &m);
    }
    if(!(a = (int**)malloc(1*sizeof(int*))))
    {
        puts("Ошибка выделения памяти");
    }
    else
    {
        if(!(a[0] = (int*)malloc(m * sizeof(int))))
        {
            puts("Ошибка выделения памяти");
        }
        else
        {
            n = firststr(m, a[0]);
            if(!(a = (int**)realloc(a, n*sizeof(int*))))
            {
                puts("Ошибка выделения памяти");
            }
            else
            {
                nextstr(a, n, m);
                puts("Исходный массив: ");
                for (i = 0; i < n; i++)
                {
                    for (j = 0; j < m; j++)
                        printf("%5d", a[i][j]);
                    puts("");
                }
                c = transp(a, n, m);
                nn = newmatrix(c, m, n, d);
                d = newmatrix2(c, m, n);
                puts("Сформированный массив ");
                for (i = 0; i < nn; i++)
                {
                    for (j = 0; j < n; j++)
                        printf("%5d", d[i][j]);
                    puts("");
                }
                for (i = 0; i < n; i++)
                    free(a[i]);
                for (i = 0; i < m; i++)
                    free(c[i]);
                free(a);
                free(c);
                free(d);
            }
        }
    }
    return 0;
}


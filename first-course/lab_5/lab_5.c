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
    puts("���-�� �����:");
    scanf("%d", &n);
    puts("���-�� ��������:");
    scanf("%d", &m);
    puts("�������� A:");
    scanf("%d", &A);
    puts("�������� B:");
    scanf("%d", &B);
    if(!(a = (int**)malloc(n * sizeof(int*))))
    {
        puts("������ ��������� ������");
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
                puts("������ ��������� ������");
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
                    puts("������ ��������� ������");
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
            printf("������� �������� ����������� �������: %.2f", s);
        }
        else
            printf("������ ����");
    }
    for (i = 0; i < n; i++)
        free(a[i]);
    free(a);
    free(b);
    return 0;
}

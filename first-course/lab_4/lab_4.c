#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <locale.h>
#define N 100
#define M 100
int main()
{
    setlocale(LC_ALL, "Rus");
    int i,j,n,m,stmax,stmin,imin,imax,jmin,jmax;
    int a[N][M];
    scanf("%d",&n);
    scanf("%d",&m);
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &a[i][j]);
    for (i = 0; i < m; i++){
        stmax = INT_MIN;
        stmin = INT_MAX;
        for (j = 0; j < n; j++){
            if (a[j][i] >= stmax){
                stmax = a[j][i];
                imax = j;
                jmax = i;
            }
            if (a[j][i] < stmin){
                stmin = a[j][i];
                imin = j;
                jmin = i;
            }
            }
        printf("Максимальный Элемент в %d столбце: %d; Индексы %d; %d\n", i, stmax, imax, jmax);
        printf("Минимальный Элемент в %d столбце: %d; Индексы %d; %d\n", i, stmin, imin, jmin);
    }
return 0;
}

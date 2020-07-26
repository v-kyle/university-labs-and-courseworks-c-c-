#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define MS 80

int main()
{
    setlocale(LC_ALL, "RUS");
    char st[MS];
    char ar[MS];
    int lw[MS];
    int n, i, j, mx = 0, mxtmp = 0, currentflag, previousflag = 0, currentword = 0, k = 0;

    puts("Введите строку с разделителями");
    fgets(st, MS, stdin);
    st[strlen(st)-1] = '\0';

    puts("Введите кол-во разделителей в строке");
    scanf("%d", &n);
    getchar();

    puts("Введите массив разделителей");
    fgets(ar, n+1, stdin);
    ar[n] = '\0';

    for (i = 0; i < strlen(st); i++)
    {
        previousflag = currentflag;
        currentflag = 1;

        for (j = 0; j < n; j++)
            if (st[i] == ar[j])
                currentflag = 0;

        if (currentflag == 1)
        {
            mxtmp++;
            if (previousflag == 0)
                currentword++;
        }

        if ((currentflag == 0) || (i+1 == strlen(st)))
        {
            if (previousflag == 1)
                lw[currentword] = mxtmp;
            if (mxtmp > mx)
                mx = mxtmp;
            mxtmp = 0;
        }
    }

    i = 0;
    while (i < currentword+1)
    {
        if (lw[i] == mx)
            k++;
        i++;
    }
    printf("Кол-во слов максимальной длины (равной %d): %d", mx, k);
    return 0;
}

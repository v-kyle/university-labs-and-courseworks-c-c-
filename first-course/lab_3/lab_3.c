#include <stdio.h>
#include <stdlib.h>

int main()
{
    char str[20];

    int sum[21] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    for (int i = 0; i< 20;i++)
    {
        scanf("%c", &str[i]);
    }

    getchar();
    for(int i = 1; i< 21;i++)
    {
        sum[i] = (int)str[i-1] - 48;
    }

    for(int i = 0; i< 20;i++)
    {
        scanf("%c", &str[i]);
    }

    for(int i = 1; i< 21;i++)

    {
        sum[i] += (str[i-1] - 48);
        if(sum[i] > 9)
        {
            sum[i-1]++;
            sum[i]-=10;
        }
    }

    for(int i = 0; i < 21;i++)
    {
        if(i == 0 && sum[i] == 0)
        {
        continue;
        }
        else{
         printf("%d", sum[i]);
        }
    }
    return 0;
}

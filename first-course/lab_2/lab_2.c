#include <stdio.h>
#include <stdlib.h>

int main()
{
    int s,a,b,n0,n;
    s=0;
    scanf("%d", &n0);
    n=0;
    b=0;
    a=0;
    while (n<n0)
    {
        scanf("%d",&a);
        if (a*b<0)
        {
            if (n+1 != n0) s=0;
            n=n+1;
        }
        if (a<0) s=s+a;
        b=a;
    }

    printf("%d",s);
    return 0;
}

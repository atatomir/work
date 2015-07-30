#include<stdio.h>
using namespace std;
int n,p,k,n1,putere,i,nr,a,b,c;
int main()
{
    freopen("fractii2.in","r",stdin);
    freopen("fractii2.out","w",stdout);
    scanf("%d %d",&p,&n);
    if(p==1)
    {
        n1=n;
        while(n1>1)
        {
            if(n1%2)
                k=1;
            n1/=2;
            putere++;
        }
        if(!k)
            for(i=1;i<=n;i++)
                printf("%d ",putere);
        else
        {
            nr=1;
            for(i=0;i<=putere;i++)
                nr*=2;
            for(i=1;i<=nr-n;i++)
                printf("%d ",putere);
            for(i=nr-n+1;i<=n;i++)
                printf("%d ",putere+1);
        }
    }
    else
    {
        a=1;
        b=1;
        c=2;
        if(n==2 || n==3)
            printf("%d",a);
        else
            if(n==4)
                printf("%d",c);
            else
            {
                while(n>4)
                {
                    a=b%100003;
                    b=c%100003;
                    c=(a+b)%100003;
                    n--;
                }
                printf("%d",c);
            }
    }
    printf("\n");
    return 0;
}

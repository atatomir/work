#include <iostream>
#include <cstdio>

using namespace std;

long v[1000],a[150][400];
long n,p,s,x,y,i,nr,cer,minim,j;

int main()
{
    freopen("defrag.in","r",stdin);
    freopen("defrag.out","w",stdout);
    scanf("%ld",&cer);
    scanf("%ld%ld",&p,&s);
    scanf("%ld",&n);
    if (cer==1)
    {
        for (i=1;i<=n;i++)
            {
                scanf("%ld%ld",&x,&y);
                if (v[x]==0) v[x]=1;
            }
        nr=p;
        for (i=1;i<=p;i++) if (v[i]==1) nr--;
        printf("%ld\n",nr);
    }
    if (cer==2)
    {
        for (i=1;i<=p;i++)
            for (j=1;j<=s;j++) a[i][j]=1;
        for (i=1;i<=n;i++)
        {
            scanf("%ld%ld",&x,&y);
            a[x][y]=0; a[x][0]++;
        }
        for (i=1;i<=p;i++)
        {
            minim=1000000;
            for (j=1;j<=s;j++) v[j]=0;
            for (j=1;j<=a[i][0];j++) v[1]=v[1]+a[i][j];
            for (j=2;j<=s-a[i][0]+1;j++) v[j]=v[j-1]-a[i][j-1]+a[i][j+a[i][0]-1];
            for (j=1;j<=s-a[i][0]+1;j++) if (minim>v[j]) minim=v[j];
            printf("%ld ",minim);
        }
        printf("\n");
    }
    return 0;
}

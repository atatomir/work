#include <cstdio>

using namespace std;
long aa,bb,cc,c1,c2,c3,b[20],a[1010],tot,n,i,minn,maxx,mij,f,k,c[1010],y,xx;
char x;
int main()
{
freopen("tcif.in","r",stdin);
freopen("tcif.out","w",stdout);
scanf("%ld%ld%ld%ld%ld%ld",&aa,&bb,&cc,&c1,&c2,&c3);
tot=aa+bb+cc;
minn=c1; if (minn>c2) minn=c2; if (minn>c3) minn=c3;
maxx=c1; if (maxx<c2) maxx=c2; if (maxx<c3) maxx=c3;
if ((minn==c1)||(maxx==c1))
    {
    if ((minn==c2)||(maxx==c2))
            mij=c3;
            else mij=c2;
    }
    else mij=c1;
b[c1]=aa; b[c2]=bb; b[c3]=cc;
scanf("%c",&x);
scanf("%c",&x);
while (x>=48)
    {
    n++; a[n]=x-48;
    scanf("%c",&x);
    }
if (tot>n)
    {
    if (minn==0)
        {
        printf("%ld",mij);
        for (i=1; i<=b[minn]; i++)
            printf("%ld",minn);
        for (i=1; i<=b[mij]-1; i++)
            printf("%ld",mij);
        for (i=1; i<=b[maxx]; i++)
            printf("%ld",maxx);
        }
    else
        {
        for (i=1; i<=b[minn]; i++)
            printf("%ld",minn);
        for (i=1; i<=b[mij]; i++)
            printf("%ld",mij);
        for (i=1; i<=b[maxx]; i++)
            printf("%ld",maxx);
        }
    }
    else
    {
    i=1; f=0;
    do{
    k=a[i]; while ((b[k]==0)&&(k<=9)) k++;
    if (k!=10)
    {
    c[i]=k; b[k]--;
    if  (c[i]>a[i]) f=1;
    i++;
    }
    else
    {
    i--;
    while (c[i]==maxx)
        {b[c[i]]++; c[i]=0; i--;}
    if (c[i]==minn)
        {
        if (b[mij]>0)
            {b[minn]++; b[mij]--; c[i]=mij;}
            else
            {b[minn]++; b[maxx]--; c[i]=maxx;}
        }
        else {b[mij]++; b[maxx]--; c[i]=maxx;}
    f=1;
    }
    }while ((f==0)&&(i<=n));
    if (f==1)
        {
        for (y=1; y<=b[minn]; y++)
            {
            i++; c[i]=minn;
            }
        for (y=1; y<=b[mij]; y++)
            {
            i++; c[i]=mij;
            }
        for (y=1; y<=b[maxx]; y++)
            {
            i++; c[i]=maxx;
            }
        }
        else
        {
        i=n-1; while (c[i]>=c[n]) i--;
        xx=c[i]; c[i]=c[n]; c[n]=xx;
        do{
        k=1;
        for (y=i+1; y<n; y++)
            if (c[y]>c[y+1])
                {
                k=0; xx=c[y]; c[y]=c[y+1]; c[y+1]=xx;
                }
        }while (k==0);
        }
    //
    for (y=1; y<=n; y++)
        printf("%ld",c[y]);
    }
return 0;
}

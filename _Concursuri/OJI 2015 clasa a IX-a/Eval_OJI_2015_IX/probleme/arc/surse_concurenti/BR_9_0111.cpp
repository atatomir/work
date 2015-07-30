#include <cstdio>

using namespace std;
long v,n,prev,secv,s[11000],nr[11000],gigel,i,ma,pos,beg,en,tot,y;
int main()
{
freopen("arc.in","r",stdin);
freopen("arc.out","w",stdout);
scanf("%ld",&v);
scanf("%ld",&n);
prev=-1; secv=0;
for (i=1; i<=n; i++)
    {
    scanf("%ld",&gigel);
    if (gigel==prev)
        nr[secv]++;
        else
        {
        secv++;
        s[secv]=gigel;
        nr[secv]=1;
        }
    prev=gigel;
    }
if (v==1)
    printf("%ld",secv);
if (v==2)
    {
    s[0]=-56; s[secv+1]=-96;
    do{
    ma=-5; pos=-1;
    for (i=1; i<=secv; i++)
        if ((nr[i]>2)&&(ma<nr[i]))
            {ma=nr[i]; pos=i;}
    if (pos>=0)
        {
        beg=pos; en=pos;
        while ((s[beg-1]==s[en+1])&&(nr[beg-1]+nr[en+1]>2))
            {
            beg--; en++;
            }
        if (s[beg-1]==s[en+1])
            {
            nr[beg-1]+=nr[en+1];
            en++;
            }
        for (i=beg; i<=secv-(en-beg+1); i++)
            {
            s[i]=s[i+en-beg+1];
            nr[i]=nr[i+en-beg+1];
            }
        secv=secv-(en-beg+1);
        }

    }while (pos>=0);
    tot=0;
    for (i=1; i<=secv; i++)
        tot+=nr[i];
    printf("%ld\n",tot);
    for (i=1; i<=secv; i++)
        for (y=1; y<=nr[i]; y++)
            printf("%ld\n",s[i]);
    }
//
//
//for (i=1; i<=secv; i++)
//    printf("%ld ",s[i]);
//printf("\n");
//
//for (i=1; i<=secv; i++)
//    printf("%ld ",nr[i]);
//
//
//

return 0;
}

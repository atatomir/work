#include <iostream>
#include <cstdio>

using namespace std;

long v[10100],x[10100],y[10100];
long p,n,i,nr,maxim,maxval,rez,j,corect,valcur,scur;

int main()
{
    freopen("arc.in","r",stdin);
    freopen("arc.out","w",stdout);
    scanf("%ld",&p);
    scanf("%ld",&n);
    for (i=1;i<=n;i++) scanf("%ld",&v[i]);
    if (p==1)
    {
        nr=0; v[n+1]=-1;
        for (i=1;i<=n;i++) if (v[i]!=v[i+1]) nr++;
        printf("%ld\n",nr);
    }
    corect=0;
    if (p==2)
    {
        while (corect==0)
        {
            nr=1; v[n+1]=-1; x[1]=1; y[1]=v[1];
            for (i=2;i<=n;i++) if (v[i-1]==v[i]) x[nr]++;
                                   else {nr++; x[nr]=1; y[nr]=v[i];}
            maxim=0; maxval=0;
            for (i=1;i<=nr;i++) if (x[i]>maxim) {maxim=x[i]; maxval=i;}
            while (maxim>=3)
            {
                x[maxval]=-1; y[maxval]=-1;
                while (y[maxval-1]==y[maxval-y[maxval]])
                    {
                        x[maxval-1]=x[maxval-1]+x[maxval-y[maxval]];
                        x[maxval-y[maxval]]=-1; y[maxval-y[maxval]]=-1;
                        x[maxval]=x[maxval]-1; y[maxval]=y[maxval]-1;
                        maxval=maxval-1;
                        if (x[maxval]<3) break;
                        x[maxval]=x[maxval+1]-1; y[maxval]=y[maxval+1]-1;
                    }
                maxim=0;
                for (i=1;i<=nr;i++) if (x[i]>maxim) {maxim=x[i]; maxval=i;}
            }
            corect=1; valcur=10000000; scur=0;
            for (i=1;i<=nr;i++) if (y[i]>0) {if (valcur==y[i]) scur=scur+x[i];
                                                 else {valcur=y[i]; scur=x[i];}
                                             if (scur>=3) {corect=0; break;} }
            if (corect==0)
            {
                n=1;
                for (i=1;i<=nr;i++) if (x[i]>0) {for (j=n;j<=n+x[i]-1;j++) v[j]=y[i]; n=n+x[i];}
                n--;
            }
        rez=0;
        for (i=1;i<=nr;i++) if (x[i]>0) rez=rez+x[i];
        }
        printf("%ld\n",rez);
        for (i=1;i<=nr;i++) if (x[i]>0) for (j=1;j<=x[i];j++) printf("%ld\n",y[i]);
    }
    return 0;
}

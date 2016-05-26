#include <fstream>
#include <algorithm>
#include <deque>
#include<cstdlib>
#include<ctime>
#define GEN 0
using namespace std;
ifstream f("echilibrare.in");
ofstream g("echilibrare.out");
int n,i,j,k,s,d,lo,hi,cap[205][205],cst[205][205],a[105][105],q[205],c[205],T[205],x[105],y[105],p[105],ok,
Hi[105],oo=1000000000,suma,v,m,b[105][105],upd();
deque<int> Q;
int main()
{
    f>>n;
    s=0;
    d=2*n+1;
    for(i=1;i<=n;i++)
    {
        cap[s][i]=1;
        cap[i+n][d]=1;
        for(j=1;j<=n;j++)
        {
            f>>a[i][j];
            cst[i][j+n]=310000-a[i][j];
            cst[j+n][i]=-cst[i][j+n];
            cap[i][j+n]=1;
        }
    }

    for(;;)
    {
        Q.resize(0);Q.push_back(s);q[s]=1;
        for(i=1;i<=d;i++){c[i]=oo;T[i]=0;}
        for(;Q.size();)
        {
            i=Q.front();
            for(j=1;j<=d;j++)
                if(cap[i][j]&&c[j]>c[i]+cst[i][j])
                {
                    c[j]=c[i]+cst[i][j];T[j]=i;
                    if(!q[j]){Q.push_back(j);q[j]=1;}
                }
            Q.pop_front();q[i]=0;
        }
        if(c[d]==oo)break;
        for(i=d;i;i=T[i])
        {
            cap[i][T[i]]=1;cap[T[i]][i]=0;
            if(T[i]<=n)p[T[i]]=i-n;
        }
    }
    k=p[1];
    for(i=2;i<=n;i++)
    {
        j=p[i];
        y[j]=a[1][k]+a[i][j]-a[1][j]-a[i][k];
    }
    ok=0;
    while(!upd())
    {
        x[i]+=a[i][j]-b[i][j];
        y[p[i]]-=a[i][j]-b[i][j];
    }
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
        suma+=b[i][j];
    g<<suma<<'\n';
    for(i=1;i<=n;i++)
    {
        for(j=1;j<n;j++)
            g<<b[i][j]<<' ';
        g<<b[i][j]<<'\n';
    }
    return 0;
}
int upd()
{
    for(j=1;j<=n;j++)b[1][j]=a[1][j]+y[j];
    for(i=2;i<=n;i++)b[i][k]=a[i][k]+x[i];
    for(i=2;i<=n;i++)
        for(j=1;j<=n;j++)
            if(j-k)
            {
                b[i][j]=b[1][j]+b[i][k]-b[1][k];
                if(b[i][j]<a[i][j])
                    return 0;
            }
    return 1;
}

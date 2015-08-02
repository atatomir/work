#include <fstream>
using namespace std;

ifstream f ("biperm.in");
ofstream g("biperm.out");
int n,i,j,v[10001]={0},a1[10001],a2[10001],sol[10001];
int k,c,p,minim=999999999;

int valid(int a1[10001], int a2[10001], int v[10001])
{
    int i,j;
    int k=1;
    for (i=1;i<=n;i++)
    {
        if (v[i]==1)
        {
            int aux=a1[i];
            a1[i]=a2[i];
            a2[i]=aux;
        }
    }
    for (i=1;i<n;i++)
        for (j=i+1;j<=n;j++)
        {
            if (a1[i]==a1[j] || a2[i]==a2[j]) k=0;
        }
    return k;
}

int main()
{
    f>>n;
    for (i=1;i<=n;i++)
        f>>a1[i];
    for (i=1;i<=n;i++)
        f>>a2[i];
    k=0;
    while (v[0]!=1)
    {
        i=n;
        while (v[i]==1)
        {
            v[i]=0;
            i--;
        }
        v[i]=1;
        k=valid(a1,a2,v);
        if (k==1)
        {
            c++;
            p=0;
            for (i=1;i<=n;i++)
                if (v[i]==1) p++;
            if (minim>p) minim=p;
            if (minim==p)
                for (i=1;i<=n;i++)
                    sol[i]=v[i];
            for (i=1;i<=n;i++)
                if (v[i]==1)
                {
                    int aux=a1[i];
                    a1[i]=a2[i];
                    a2[i]=aux;
                }
        }
        else
        {
            for (i=1;i<=n;i++)
                if (v[i]==1)
                {
                    int aux=a1[i];
                    a1[i]=a2[i];
                    a2[i]=aux;
                }
        }
    }
    g<<c<<" "<<minim<<"\n";
    for (i=1;i<=n;i++)
    {
        if (sol[i]==1)
        {
            int aux=a1[i];
            a1[i]=a2[i];
            a2[i]=aux;
        }
    }
    for (i=1;i<=n;i++)
        g<<a1[i]<<" ";
    g<<"\n";
    for (i=1;i<=n;i++)
        g<<a2[i]<<" ";
        g<<"\n";
    f.close();
    g.close();
    return 0;
}

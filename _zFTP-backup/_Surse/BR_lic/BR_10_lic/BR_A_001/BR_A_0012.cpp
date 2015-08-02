#include <fstream>

using namespace std;

ifstream f("triunghi.in");
ofstream g("triunghi.out");

long long x;
int n,k,v,i,j;
long long a[48];

int main()
{
    f>>v;
    f>>n;
    f>>k;

    for(i=1;i<=n;i++)
        f>>a[i];
    f.close();

    int sch,m,aux;
    m=n+1;
    do
    {
        sch=0;
        m--;
        for(i=1;i<m;i++)
        {
            if(a[i]>a[i+1])
                {
                    sch=1;
                    aux=a[i+1];
                    a[i+1]=a[i];
                    a[i]=aux;
                }
        }
    }
    while(sch==1);



    if(v==2)
    {
        int y,ok=1;
        j=n;
        i=1;
        y=n;
        x=a[n]-a[n-i]-1;
        for(int z=0;z<=n;z++)
        if(a[z]==x)
        ok=0;
        if(ok==1)
        {
        a[++y]=x;
        k--;
        }
        else
        x=a[n-i];
        i++;
        ok=0;
    while(k>n&&i<n)
    {
        ok=1;
        x=x-a[n-i]-1;
        for(int z=0;z<=n;z++)
        if(a[z]==x)
        ok=0;

        if(ok==1)
        {
        a[++y]=x;
        k--;
        }
        else
        x=a[n-i];

        i++;
    }
    x=a[n]+a[n-1]+1;
    a[++y]=x;
    --k;
    if(k>n)
    {
    x=a[y]+a[n]+1;
    a[++y]=x;
    --k;
    }
    while(k>n)
    {
         x=a[y]+a[y-1]+1;
         a[++y]=x;
         k--;

    }
        for(i=y;i>0;i--)
            g<<a[i]<<" ";

    }
    else
        {
            int y=2;

            for(i=2;i<=n;i++)
                a[i]=0;
            a[2]=a[1]*2+1;
            k--;
            while(k>1)
            {
                y++;
                a[y]=a[y-1] +a[y-2]+1;
                k--;

            }
            for(i=1;i<=y;i++)
            g<<a[i]<<" ";
        }

    g.close();

    return 0;
}

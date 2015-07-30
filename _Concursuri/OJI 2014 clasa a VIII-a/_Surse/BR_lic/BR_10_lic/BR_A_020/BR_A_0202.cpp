#include <fstream>
using namespace std;
ifstream f("triunghi.in");
ofstream g("triunghi.out");

int v,n,k,i,a[47],b[47],min;

int main()
{
    f>>v; f>>n; f>>k;
    for(i=1;i<=n;i++)
        f>>a[i];

    if(v==1)
    {
        min=a[i];
        for(i=2;i<=n;i++)
            if(a[i]<min)
                min=a[i];
        b[1]=min;

    }
    if(v==2)
    {
        for(i=1;i<=n;i++)
            b[i]=a[i];

    }
    f.close();
    g.close();
    return 0;
}

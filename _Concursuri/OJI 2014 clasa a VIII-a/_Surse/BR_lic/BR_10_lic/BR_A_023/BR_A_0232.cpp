#include <iostream>
#include <fstream>
using namespace std;
ifstream f("triunghi.in");
ofstream g("triunghi.out");
int main()
{
    int v,n,a[20],k,min,b[23],i;
    f>>v>>n>>k;
    for(i=1;i<=n;i++)
    f>>a[i];
    if(v==1)
    {min=a[1];
    for(i=1;i<=n;i++)
    if(min>a[i])
    min=a[i];b[1]=min;
    g<<b[1];
    }
    else
    {
        if(v==2)
        b[1]=a[1];b[2]=a[2];b[3]=a[3];
        g<<b[1]<<" "<<b[2]<<" "<<b[3];
    }
    f.close();
    g.close();
    return 0;
}

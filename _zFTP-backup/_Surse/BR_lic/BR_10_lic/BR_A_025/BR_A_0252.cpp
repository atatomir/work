#include <iostream>
#include <fstream>
using namespace std;
ifstream f("triunghi.in");
ofstream g("triunghi.out");
int main()
{
    int v,n,k,sir[47],siri[46],i,m,c,s;
    f>>v>>n>>k;
    for (i=1;i<=n;i++)
    {
        f>>siri[i];
    }
    c=1;
    while (c!=0)
    {
        c=0;
        for (i=1;i<=n-1;i++)
        {

            if (siri[i]>siri[i+1])
            {
                m=siri[i+1];
                siri[i+1]=siri[i];
                siri[i]=m;
                c=1;
            }
        }
    }
    if (v==1)
    {
    for (i=1;i<=k;i++)
        {
        if ((i==1)||(i==2))
        {
            sir[1]=siri[1];
            sir[2]=siri[1];
            s=sir[1]*2+1;
        }
        else
        {
            sir[i]=s;
            s=sir[i-1]+sir[i]+1;
        }
        g<<sir[i]<<" ";
        }
    }
    if (v==2)
    {
        for (i=1;i<=k;i++)
        {
            if (i<=n)
            {
                sir[i]=siri[i];
                s=sir[i]+sir[i-1]+1;
            }
            else
            {
                sir[i]=s;
                s=sir[i]+sir[i-1]+1;
            }
            g<<sir[i]<<" ";
        }
    }
    f.close();g.close();
    return 0;
}

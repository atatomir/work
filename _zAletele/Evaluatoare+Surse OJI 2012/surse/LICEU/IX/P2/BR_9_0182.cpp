#include <fstream>
using namespace std;
ifstream f("clepsidru.in");
ofstream g("clepsidru.out");
int v[2003],n,b,x,i,k,t,s;
int main()
{

    f>>n>>b;
    x=2*n;
    v[x]=b;
    while(b!=0)
    {
        for (i=2;i<=x;i=i+2)
            while(v[x-i]!=0)
            {
                k++;
                t=2*i;
                v[x-t]++;
            }
        b--;
    }

    s=n-k+2;
    g<<s;
    g<<"\n";
f.close();
g.close();
return 0;
}

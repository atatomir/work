#include <fstream>
using namespace std;
int main()
{ifstream f("defrag.in");
ofstream g("defrag.out");
int z,V,P,S,C,a[36000],b[36000],c[36000],s=0;
f>>V>>P>>S>>C;
if(V==1)
{for(i=1;i<=n,i++)
    f>>a[i]>>b[i];
for(i=1;i<=n;i++)
{z=a[i];
if(b[i]==0 && z==a[i]) c[i]=0;}
for(i=1;i<=n;i++)
    s=s+c[i];
g<<s;}
return 0;
}

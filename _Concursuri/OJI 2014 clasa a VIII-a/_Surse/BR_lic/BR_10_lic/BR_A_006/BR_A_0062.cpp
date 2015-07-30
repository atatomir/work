#include <fstream>

using namespace std;
ifstream f("triunghi.in");
ofstream g("triunghi.out");
int n,k,i,v;
long long x[47],t[47];
int main()
{int min=32000;
f>>v;
f>>n;
f>>k;
if(v==1)
{int p=1;
for(i=1;i<=n;i++)
    {f>>t[i];
    if(t[i]<min)
        min=t[i];}
for(i=1;i<=k;i=i+6)
   {x[i]=min;
    x[i+1]=min+0;
    x[i+2]=(x[i+1]+p)*10;
    p++;
    x[i+3]=x[i+2]+p*10;
    x[i+4]=x[i]+x[i+1]+x[i+2]/10+x[i+3]/10;}

for(i=1;i<=k;i++)
    g<<x[i]<<" ";}
    return 0;
}

#include <fstream>

using namespace std;
ifstream f("triunghi.in");
ofstream g("triunghi.out");

long long v,n,i,a[50],k,nrmax,pt,aux,r,j,s;
long long t,sume[2000001],sir[2000001];
int main()
{
f>>v;
f>>n;
f>>k;
for(i=1;i<=n;i++)
    f>>a[i];
t=a[1];
for(i=1;i<=n;i++)
    if(a[i]<t)
        t=a[i];

nrmax=2;
sir[1]=t;
sir[2]=t;
r=1;
sume[r]=sir[1]+sir[2];
s=3;
while(nrmax!=k)
{
        sir[s]=sume[r]+1;
        nrmax++;
        s++;
        r++;
        sume[r]=sume[r-1]+sir[s-1];
        if(sume[r]>1500000000)
        {
            sume[r]%=1500000000;
        }
    }


if(v==1)
    for(i=1;i<s;i++)
        g<<sir[i]<<" ";
f.close();
g.close();
return 0;
}

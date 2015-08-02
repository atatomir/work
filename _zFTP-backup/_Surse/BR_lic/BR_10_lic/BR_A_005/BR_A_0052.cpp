#include <iostream>
#include<fstream>
using namespace std;

int main()
{int n, k, i, m, a[100],x[100],j,p, v;
ifstream f("triunghi.in");
ofstream g("triunghi.out");
    f>>v>>n>>k;
    for(i=1; i<=n; i++)
    f>>a[i];
p=1;
if (v==1)
{for (i=1; i<=n-1; i++)
if(a[i+1]<a[i])
{m=a[i];
a[i]=a[i+1];
a[i+1]=m;}
x[1]=a[1];
x[2]=a[1];
for(j=3; j<=k; j++)
{x[j]=x[j-1]+x[j-2]+1;}
for (j=3; j<=k; j++)
{if(x[j]<x[j-1]+x[j-2])
    while(x[j]<x[j-1]+x[j-2])
    x[j]=x[j]+1;
}
for(j=1; j<=k; j++)
g<<x[j]<<' ';}
else

{for (i=1; i<=n-1; i++)
if(a[i+1]<a[i])
{m=a[i];
a[i]=a[i+1];
a[i+1]=m;}
for(i=1; i<=n; i++)
x[i]=a[i];
for(j=n+1; j<=k; j++)
{x[j]=a[n]-a[n-1]-p;
p=p+a[1]+1;
n=n-1;
if(x[j]<1)
x[j]=1;}
for(i=1; i<=k; i++)
g<<x[i]<<' ';}
f.close();
g.close();

    return 0;
}

#include <iostream>
#include <fstream>
using namespace std;

ifstream f("cool.in");
ofstream g("cool.out");

int  a[5002];
int main()
{
int n, p, i, k, j, nr=0, t, max=0, ok;
f>>p;
f>>n>>k;
for (i=1;i<=n;i++)
f>>a[i];
if (p==1)   {
for (j=1;j<=k ;j++)  {
 if (a[j]>a[j+1] && (j+1)<=k) {
     t=a[j];
     a[j]=a[j+1];
     a[j+1]=t;
 }
if (a[j]==a[j+1]-1 && (j+1)<=k) {
if (max<a[j+1])
max=a[j+1];
ok=1;
}
else if (a[j]!=a[j+1]-1 && (j+1)<=k)    {
nr++;
ok=0;
}
}
if (ok==0)
g<<nr-1;
else
g<<max;
}
else
g<<k<<endl<<2<<endl;

f.close();
g.close();
    return 0;
}

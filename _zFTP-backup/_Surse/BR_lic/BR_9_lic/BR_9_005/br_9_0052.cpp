#include <iostream>
#include <fstream>
using namespace std;
ifstream f("pseudobil.in");
ofstream g("pseudobil.out");
long a[1501][1501],k,d,m,j,i,n1=0,n,k1,k2,k5,k4,p,v1[5001],v2[5001],ii,nr=0;
int main()
{f>>p;
f>>n;
f>>k;
f>>d;
for(i=1;i<=k;i++)
{f>>k1;
f>>k2;
a[k1][k2]=2;}
f>>m;
for(i=1;i<=m;i++)
 {f>>k4>>k5;
  v1[i]=k4;
  v2[j]=k5;}

if(p==1)
{

n1=((d-1)*(d+1))/2+(d*(d-2))/-((2*d+3)/2);

g<<n1-1<<'\n';

}
if(p==2)
{for(ii=1;ii<=m;ii++)
   {

   for(i=1;i<=n;i++)
    for(j=1;j<=n;j++)
    if(a[i][j]==2)
    {if((i>=v2[ii]&&i<=v2[ii]+d&&j>=v1[ii]&&j<=v1[ii])||i+j==v1[ii]+v2[ii]||(i==j&&i<=v2[ii]+d&&i>=v2[ii]&&j>=v1[ii]&&j<=v1[ii]))nr++;}}
 g<<nr;

}
    f.close();
    g.close();
    return 0;
}

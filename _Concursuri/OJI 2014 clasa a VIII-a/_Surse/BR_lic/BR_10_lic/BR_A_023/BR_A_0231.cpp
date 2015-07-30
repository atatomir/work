#include <iostream>
#include<fstream>
using namespace std;
ifstream f("ferma.in");
ofstream g("ferma.out");
int main()
{
    int n,m,i,j,l,v,r=0;
    char a[20][23],b[400];
    f>>v;
    f>>n;
    f>>m;
    for(i=1;i<=n;i++)
    for(j=1;j<=m;j++)
    f>>a[i][j];
    if(v==1)
    {r=n*m;
    for(i=1;i<=n;i++)
    for(j=1;j<=m;j++)
    {
        for(l=1;l<=r;l++)
      if(i==1&&l==j)
      b[l]=a[i][j];
      else
      {
          if((l-j)/m==(i-1)&&i>=2)
          b[l]=a[i][j];
      }
    }}
    f.close();
    g.close();
    return 0;
}

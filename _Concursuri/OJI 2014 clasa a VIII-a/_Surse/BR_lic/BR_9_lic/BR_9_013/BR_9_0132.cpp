#include <iostream>
#include <fstream>
using namespace std;
int main()
{ int p,n,m,k,d,a,b,i,x,y,j,n1,n2;
  ifstream f("pseudobil.in");
  ofstream g("pseudobil.out");
  f>>p>>n>>k>>d;
  int v[n+1][n+1];
  for(i=1;i<=n;i++)
    for(j=1;j<=n;j++)
      v[i][j]=0;
  for(i=1;i<=k;i++)
      {f>>a>>b;
      v[a][b]==2; //1=bila
      }
  if(p==1)
  for(i=1;i<=m;i++)
        {f>>x>>y;
    v[x][y]=1;
    v[y][x]=1;
    v[d+1][y]=1;
    v[y][d+1]=1;}   //coord. colt sus
  for(i=y;i<=d+1;i++)
    if(v[x][i]!=1)
      n1++;
  for(i=y;i<=d+1;i++)
    if(v[y][i]!=1)
      n1++;
  g<<n1;
  if(p==2)
    i=1;
   while(i<=m)
    {   n2=0;
          f>>x>>y;
          v[x][y]=1;
          v[y][x]=1;
          v[d+1][y]=1;
          v[y][d+1]=1;
      for(i=y;i<=d+1;i++)
        if(v[x][i]==2)
         n2++;
      for(i=y;i<=d+1;i++)
        if(v[y][i]==2)
         n2++;
      g<<n2;g<<'\n';
     i++;
    }
  f.close();
  g.close();
    return 0;
}

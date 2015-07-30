#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream f("pseudobil.in");
    ofstream g("pseudobil.out");
    int n,d,a,b,x,y,p,i,j,nr,l;
    long k,m,c[n][n];
    for (i=1; i<=n; i++)
       for (j=1; j<=n; j++)
          c[i][j]=0;
    f>>p;
    f>>n>>k>>d;
    for (i=1; i<=k; i++)
             {f>>a>>b;
              c[a][b]=1;}
    f>>m;
    for (i=1; i<=m; i++) f>>x>>y;
    if (p==1)
          {   nr=0;
              for (i=d; i>=1; i-2) nr=nr+i;
              g<<nr;
          } nr=0;
    if (p==2)
      {      if (c[x][y]==1) nr++;
      if (c[x+d][y]==1) nr++;
             for (i=1; i<=d/2; i++)
                 {for (l=y-1; l<=y+1; y++)
                   {
                       if (c[x][l]==1) nr++;
                       y++;
                   }
                  x++;
                 }
              for (i=1; i<=d/2-1; i++)
                {
                    for (l=y+1; l<=y-1; l++)
                    {
                        if (c[x][l]==1) nr++;
                        y--;
                    }
                    x++;
                }
                 g<<nr;
      }
    f.close();
    g.close();
    return 0;}



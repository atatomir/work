#include <iostream>
#include <fstream>

using namespace std;
int main ()
{
    int  i,j,n,K,D,m,x,y,a,b, s[150][150],gri=1;
    short int p;

    ifstream f("pseudobil.in");
    ofstream g("pseudobil.out");
    f >> p;
    f >> n >> K >> D;
    for (i=1;i<=n;i++)
         for (j=1;i<=n;i++)             // pt restul am -1
              s[i][j]=-1;
    for (i=1;i<=K;i++)
         {f >> a;
          f >> b;
          s[a][b]=0;}                 // pt bile avem 0
    f >> m;
    for (i=1;i<=m;i++)
         {
             f >> x;
             f >> y;
             s[x][y]=-2;            // pentru coltul de sus avem -2
         }
    if (p==1)
    {
    j=1;
    if (D>4)
    {for (i=4;i<=D;i++)
         {
              if (i%2==0)
              {
                  j=j+2;
                  gri=gri*2+j;
                  if (i!=D) {
                               for (int k=1;k<=i/2-1;k++)
                                   if (k%2!=0) gri=gri-k;
                            }
              }

         }
    g << gri;}     // Raspuns pentru 1 gri
      else g << "1";
    }
    return 0;
}

#include <fstream>
using namespace std;
const int dx[]={-1,0,1,0}, dy[]={0,1,0,-1};
int a[402][402], e[28];
char c[256][256], d[256];
void bordare(int n,int m)
{int i;
    for(i=0;i<=n+1;i++)
       a[i][0]=a[i][m+1]=-1;
    for(i=1;i<=m+1;i++)
       a[0][i]=a[n+1][i]=-1;
}
void fill(int x, int y, int z)
{int xnou,ynou,i;
    for(i=0;i<4;i++)
       {
           xnou=x+dx[i];
           ynou=y+dy[i];
           if(a[xnou][ynou]==z)
             {
                 e[z]++;
                 a[xnou][ynou]=-1;
                 fill(xnou,ynou,z);
             }
       }

}
int main()
{int n,m,i,j,t,k=1,max=0,l,v,lr;
    ifstream f("ferma.in");
    ofstream g("ferma.out");
    f>>v;
    f>>n>>m;
    bordare(n,m);
    for(i=1;i<=n;i++)
       for(j=1;j<=m;j++)
          {
              f>>c[i][j];
              t=0;
              for(l=1;l<=k;l++)
                  if(d[l]==c[i][j])
                    t=1;
              if(t==0)
                {
                    d[k]=c[i][j];
                    k++;
                }
          }
    for(i=1;i<=n;i++)
       for(j=1;j<=m;j++)
          for(l=1;l<=k;l++)
            {
                if(d[l]==c[i][j])
                  {
                      if(a[i][j]!=-1)
                        {
                            a[i][j]=l;
                            fill(i,j,l);
                          if(e[l]!=0&&l!=lr)
                            e[l]--;
                                if(e[l]>max)
                                  {lr=l; max=e[l];}

                        }

                  }

            }
    g<<max+l-lr-1;
    f.close();
    g.close();
    return 0;
}

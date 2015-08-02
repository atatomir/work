#include <fstream>
#include <string.h>
using namespace std;
ifstream f("ferma.in");
ofstream g("ferma.out");

int r, s=-1, a[401][401], dap=0;
void fill(int i, int j)
{
    if (a[i][j]==r)
    {
        dap++;
        a[i][j]=s;
        fill(i-1, j);
        fill(i, j+1);
        fill(i+1, j);
        fill(i, j-1);

    }
}

int main()
{
    char b[27]={"abcdefghijklmnopqrstuvwxyz"}, x;
    int v, m, n, i, j, k, max=0, t, cul, ii, jj;
                                                //citire
    f>>v;
    f>>m;
    f>>n;
    for (i=1; i<=m; i++)
    {
        for (j=1; j<=n; j++)
        {
            f>>x;
            for (k=0; k<=26; k++)
            {
                if (b[k]==x)
                {
                    a[i][j]=k+1;
                    break;
                }
            }
        }
    }
                                                //bordare
    for (i=1; i<=m; i++)
        a[i][0]=a[i][n+1]=-50;
    for (i=1; i<=n; i++)
        a[0][i]=a[m+1][i]=-50;

                                                //primul caz
    if (v==1)
    {
        for (i=1; i<=m; i++)
        {
           for (j=1; j<=n; j++)
           {
               if (a[i][j]>0)
               {
                    dap=0;
                    r=a[i][j];
                    fill(i,j);
                    s--;
                    if (dap>max)
                        max=dap;
               }
           }
        }
        g<<max;
    }

                                            //al doilea caz
    if (v==2)
    {
        for (i=2; i<=m-1; i++)
        {
            for (j=2; j<=n-1; j++)
            {
                if (a[i][j+2]==a[i][j] /*&& a[i][j]!=a[i][j+1]*/)
                {
                    dap=0;
                    r=a[i][j];
                    t=a[i][j+1];
                    a[i][j+1]=a[i][j];
                    fill(i,j);
                    s--;
                    if (dap>max)
                    {
                        max=dap;
                        ii=i;
                        jj=j+1;
                        cul=r;
                    }
                    else a[i][j+1]=t;
                }
                if (a[i+2][j]==a[i][j] && a[i][j]!=a[i+1][j])
                {
                    dap=0;
                    r=a[i][j];
                    t=a[i+1][j];
                    a[i+1][j]=a[i][j];
                    fill(i,j);
                    s--;
                    if (dap>max)
                    {
                        max=dap;
                        ii=i+1;
                        jj=j;
                        cul=r;
                    }
                    else a[i+1][j]=t;
                }
            }
        }
        g<<ii<<" "<<jj<<'\n';
        g<<b[cul-1];
    }

f.close();
g.close();
return 0;
}

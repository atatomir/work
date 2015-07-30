#include <fstream>
using namespace std;
ifstream f("ferma.in");
ofstream g("ferma.out");

char a[401][401],r;

int n,m,nr,i,v,nrmax,j;

void dap(int i, int j)
    {
        if(a[i][j]==r)
        {
            nr++;
            dap(i+1,j);
            dap(i-1,j);
            dap(i,j-1);
            dap(i,j+1);
        }
    };


int main()
{
f>>v;
f>>m;
f>>n;
for(i=1;i<=m;i++)
    for(j=1;j<=n;j++)
        {
            f.get(a[i][j]);

        }
for(i=0;i<=m;i++)
    {
        a[i][0]=-1;
        a[i][n+1]=-1;
    }
for(i=0;i<=n;i++)
    {
        a[0][i]=-1;
        a[m+1][i]=-1;
    }

nrmax=0;
for(i=1;i<=m;i++)
    for(j=1;j<=n;j++)
        {
            if(nrmax<nr)
                nrmax=nr;
            r=a[i][j];
            nr=0;
            if(a[i][j]==r)
                dap(i,j);
        }
if(v==1)
{
g<<nrmax;
f.close();
g.close();
}

return 0;
}

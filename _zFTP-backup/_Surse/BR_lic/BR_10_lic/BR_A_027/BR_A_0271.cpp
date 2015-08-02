#include <fstream>

using namespace std;
ifstream f("ferma.in");
ofstream g("ferma.out");
char a[402][402],r,p[30];
int t,m,n,u,a2[402][402],nr,v,k,b[200];
void fill(int i, int j)
{
if(a2[i][j]==u)
{a2[i][j]=-u;
    nr++;
    fill(i-1,j);
    fill(i,j+1);
    fill(i+1,j);
    fill(i,j-1);
}
}
int main()
{int max=0,i,j;
f>>v;
f>>m;
f>>n;
for(i=1;i<=m;i++)
for(j=1;j<=n;j++)
{f>>a[i][j];
r=a[i][j];
t=int(r);
if(b[t]==0) {b[t]=++k;p[k]=a[i][j];}
}
for(i=1;i<=m;i++)
for(j=1;j<=n;j++)
a2[i][j]=b[(int)a[i][j]];

for(u=1;u<=k;u++)
{for(i=1;i<=m;i++)
for(j=1;j<=n;j++)
if(a2[i][j]==u)
{nr=0;
    fill(i,j);
    if(max<nr) max=nr;
}
}

g<<max;


    return 0;
}

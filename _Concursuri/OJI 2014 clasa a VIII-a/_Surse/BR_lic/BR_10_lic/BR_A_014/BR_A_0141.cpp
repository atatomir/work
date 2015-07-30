#include <fstream>

using namespace std;
ifstream f("ferma.in");
ofstream g ("ferma.out");
struct pozitie
{
int lin;
int col;
}p,ve,c[100001],ps;

int L[401][401];
char A[401][401];

int main()
{int v,i,j,m,n,schimb,prim=0,ultim=0,k,max=0;
int dl[4]={-1,0,1,0},dc[4]={0,1,0,-1};
char x;



f>>v;
f>>m;
f>>n;

for (i=1;i<=m;i++)
    for (j=1;j<=n;j++)
    {
        f>>x;
        A[i][j]=x;
        schimb=x-'a';
        L[i][j]=schimb;
    }
  //bordare
  for (i=1;i<=m+1;i++)
    {
        L[i][0]=-1;
        L[i][n+1]=-1;
    }
    for (j=1;j<=n+1;j++)
    {
        L[0][j]=-1;
        L[m+1][j]=-1;}

for (i=1;i<=m;i++)
    for (j=1;j<=n;j++)
    {if (L[i][j]!=-1)
        {
prim=0;
ultim=0;
ps.lin=i;
ps.col=j;
c[0]=ps;
max=1;
while (prim<=ultim)
 {
p=c[prim];
prim++;
for (k=0;k<4;k++)
    {ve.lin=p.lin+dl[k];
     ve.col=p.col+dc[k];
        if (L[ve.lin][ve.col]==L[p.lin][p.col])
        {
       // L[v.lin][v.col]=L[p.lin][p.col];
        ultim++;
        c[ultim]=ve;
        max++;

        }
    }
L[p.lin][p.col]=-1;
 }
}
}



if (v==1)
   g<<max;
f.close();
g.close();
    return 0;
}

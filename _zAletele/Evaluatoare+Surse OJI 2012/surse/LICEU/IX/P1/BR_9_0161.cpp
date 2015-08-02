#include <fstream>
#include <math.h>

using namespace std;

//PROBLEMA 1 1 1 1 1 1
int v[1002][1002];
int main()

{int n,d,k,i,rand,col,q=1,j=1,dis=0,l,o,p,z,m,max=0,u=0;

ifstream f("betasah.in");
ofstream g("betasah.out");
f>>n;  // n randuri si n coloane
f>>d;  //numarul de dame
f>>k;  //k patratre gri
z=n;
m=1;
for (i=1;i<=n;i++)
{m++;
    for (j=m;j<=m+2;j++)
v[i][j]=9;}
v[n][n+1]=9;
v[0][1]=9;
v[0][2]=9;
for (i=1;i<=n+2;i++)
v[n+1][i]=9;


for (i=1;i<=d;i++)
        {f>>rand;
        f>>col;
        v[rand][col]=1;}

for (i=1;i<=k;i++)
    {f>>rand;
    f>>col;
    v[rand][col]=2;}


for (i=1;i<=n+1;i++)
{ if(u>max)
    {max=u;}
    u=0;


    for (j=1;j<=n+1;j++)
        if (v[i][j]==0)
            u++;
}



for (i=1;i<=n;i++)
{
    for (j=1;j<=n;j++)

            if (v[i][j]==1)
               for (l=i-1;l<=i+1;l++)
                 for (p=j-1;p<=j+1;p++)
                        if (v[l][p]==0)
                            {v[l][p]=9;
                            dis++;}}





g<<max;
g<<'\n';
g<<dis;
f.close();
g.close();
return 0;}


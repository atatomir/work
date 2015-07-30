#include <iostream>
#include <fstream>
using namespace std;
ifstream in("ferma.in");
ofstream out("ferma.out");
int v,S=1,m,n;
int check[401][401];
char ferma[401][401];
struct maxx {int val; int x; int y;};
maxx max1;
maxx arii[160001];
void arie(int x, int y)
{check[x][y]=1;
    if(ferma[x][y]==ferma[x+1][y])
{S++;
arie(x+1,y);}
if(ferma[x][y]==ferma[x-1][y])
{S++;
arie(x-1,y);}
if(ferma[x][y]==ferma[x][y+1])
{S++;
arie(x,y+1);}
if(ferma[x][y]==ferma[x][y-1])
{S++;
arie(x,y-1);}}
void cmma()
{int k=1,i,j;
    for(i=1;i<=m;i++)
    for(j=1;j<=n;j++)
    if(check[i][j]==0)
    arie(i,j);
    arii[k].val=S;
    k++;
    S=1;
for(i=1;i<k;i++)
if(arii[i].val>max1.val)
{max1.val=arii[i].val;
max1.x=arii[i].x;
max1.y=arii[i].y;
}}
int main()
{int i,j,sw=0;
    in>>v;
    in>>m>>n;
    for(i=1;i<=m;i++)
    for(j=1;j<=n;j++)
    in>>ferma[i][j];

        cmma();

    if(v==2)
    {
for(i=1;i<=m;i++)
for(j=1;j<=n;j++)
if(ferma[i+1][j]==ferma[i-1][j])
{arie(i,j);
if(S>max1.val)
{out<<i<<" "<<j<<'\n'<<ferma[i][j];
sw=1;}}
if (sw==0)
{
    i=max1.x;
    j=max1.y;
    if(ferma[i][j]!=ferma[i+1][j])
   out<<i+1<<" "<<j<<'\n'<<ferma[i][j];
    if(ferma[i][j]!=ferma[i-1][j])
out<<i-1<<" "<<j<<'\n'<<ferma[i][j];
    if(ferma[i][j]!=ferma[i][j-1])
out<<i<<" "<<j-1<<'\n'<<ferma[i][j];
    if(ferma[i][j]!=ferma[i][j+1])
out<<i<<" "<<j+1<<'\n'<<ferma[i][j];
}
    }
if(v==1)
    out<<max1.val;
    return 0;
}

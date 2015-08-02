#include <iostream>
#include<fstream>
using namespace std;

int main()
{int x, y, n, l,k, i,d[100], j,a[100][100];
int dx[]={-1,0,1,0};
int dy[]={0,1,0,-1};
int p=1,u=1;
struct zona{int l;int c;};
zona z[100], x1,y1;
ifstream f("zona.in");
ofstream g("zona.out");
f>>x>>y>>n>>l;
for(i=1;i<=l;i++)
    f>>d[i];

for(i=1;i<=n;i++)
    for(j=1;j<=n;j++)
        a[i][j]=0;
for(i=0;i<=n+1;i++)
    {a[i][0]=1;
    a[i][n+1]=1;
    a[0][i]=1;
    a[n+1][i]=1;}
x1.l=x;
x1.c=y;
a[x1.l][x1.c]=1;
z[p]=x1;
while( p<=u)
    {z[p].l=x1.l;
    z[p].c=x1.c;

        for(k=1;k<=l;k++)
            for(i=1;i<=4;i++)
            {
            if(d[k]==i)
            {
            y1.l=x1.l+dx[i];
            y1.c=x1.c+dy[i];
            if(a[y1.l][y1.c]==0)
                {
                a[y1.l][y1.c]=a[x1.l][x1.c]+1;
                u++;
                z[u].l=y1.l;
                z[u].c=y1.c;
               }

            }}
       /* else

        if(d[k]==2)
            { y1.l=x1.l+dx[2];
            y1.c=x1.c+dy[2];
            if(a[y1.l][y1.c]==0)
                {
                a[y1.l][y1.c]=a[x1.l][x1.c]+1;
                u++;
                z[u].l=y1.l;
                z[u].c=y1.c; a[x1.l][x1.c]=1;}
            }
            else
        if(d[k]==3)
            {
            y1.l=x1.l+dx[3];
            y1.c=x1.c+dy[3];
            if(a[y1.l][y1.c]==0)
                {
                a[y1.l][y1.c]=a[x1.l][x1.c]+1;
                u++;
                z[u].l=y1.l;
                z[u].c=y1.c; a[x1.l][x1.c]=1;}
            }
            else
        if(d[k]==4)
            {
            y1.l=x1.l+dx[4];
            y1.c=x1.c+dy[4];
            if(a[y1.l][y1.c]==0)
                {
                a[y1.l][y1.c]=a[x1.l][x1.c]+1;
                u++;
                z[u].l=y1.l;
                z[u].c=y1.c;
                a[x1.l][x1.c]=1;}

            }}*/

    p++;}
    g<<'\n'<<a[y1.l][y1.c];
return 0;
f.close();
g.close();
}

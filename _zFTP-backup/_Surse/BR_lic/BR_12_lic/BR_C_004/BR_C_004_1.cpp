#include <fstream>
#include <cstdlib>

using namespace std;

ifstream in("cartite.in");
ofstream out("cartite.out");

struct vulpe
{
    int x,y,r;
}v[50];

struct galerii
{
    int x,y;
}b[200];

int p,m,n,xc,yc,k,g,a[200][200],x,y,i,nr,c[100],j=1,ok,aux,d[100][100],x1,y1;


void intrare(int x,int y, int j)
{
    nr++;
    if (a[x][y]==1)
        c[j++]=nr;
    a[x][y]=-1;
    b[i].x=x;
    b[i].y=y;
    i++;
    if (a[x-1][y]!=-1)
        intrare(x-1, y,j);
    if (a[x+1][y]!=-1)
        intrare(x+1, y,j);
    if (a[x][y-1]!=-1)
        intrare(x ,y-1,j);
    if (a[x][y+1]!=-1)
        intrare(x ,y+1,j);
}
int main()
{
    in>>p;
    in>>m>>n;
    in>>xc>>yc;
    in>>k;
    for (int i=0;i<k;i++)
        in>>v[i].x>>v[i].y>>v[i].r;
        in>>g;
    for (int i=1;i<=g;i++)
    {
        in>>x>>y;
        a[x][y]=1;
        in>>x1>>y1;
        a[x1][y1]=1;
        d[x][y]=1;
    }
    for (int i=1;i<=n;i++)
        a[0][i]=a[m+1][i]=-1;
    for (int i=0;i<=m;i++)
        a[i][0]=a[i][n+1]=-1;
    for (int i=0;i<k;i++)
    {
        for (int j=-v[i].x;j<=v[i].r;j++)
            for(int l=abs(j)-v[i].r;l<=v[i].r-abs(j);l++)
                a[v[i].x+j][v[i].y+l]=-1;
    }
    i=1;
    intrare(xc,yc,j);
    i=1;
    do
    {
        ok=1;
        for (i=1;i<j-1;i++)
            if (c[i]>c[i]+1)
            {
                aux=c[i];
                c[i]=c[i+1];
                c[i+1]=aux;
                ok=0;
            }
    }
    while(k==0);
    if (p==1)
        out<<b[c[1]].x<<" "<<b[c[1]].y<<" "<<c[1]-1;
    else
        for (i=1;i<=m;i++)
        {
            for (j=1;j<=n;j++)
                if (d[i][j]==1)
                    out<<i<<" "<<j;
                out<<'\n';
        }
    in.close();
    out.close();
    return 0;
}

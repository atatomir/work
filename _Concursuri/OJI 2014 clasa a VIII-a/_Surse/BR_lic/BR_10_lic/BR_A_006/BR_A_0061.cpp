#include <fstream>
#include <string.h>

using namespace std;
ifstream f("ferma.in");
ofstream g("ferma.out");
int v,m,i,n,t[100][100],j,prim,ultim,k,r[100],o;
int dl[]={-1,1,0,0},dc[]={0,0,-1,1};
char a[100][100];
struct pozitie{
    int lin;
    int col;}c[100],V,p,ps;
/*void fill(int i ,int j, int k, int r[100])
{
    a[i][j]=-1;
    r[k]++;int min=32000
    fill(i,j-1);
    fill(i-1,j);
    fill(i+1,j);
    fill(i,j+1);
}*/
int main()
{ int x=1;
f>>v;
f>>m;
f>>n;
for(i=1;i<=m;i++)
    for(j=1;j<=n;j++)
        {f>>a[i][j];
        if(a[i][j]=='r')
            t[i][j]=1;
        if(a[i][j]=='m')
            t[i][j]=2;
        if(a[i][j]=='g')
            t[i][j]=3;
        if(a[i][j]=='a')
            t[i][j]=4;
        if(a[i][j]=='v')
            t[i][j]=5;}
for(i=0;i<=n+1;i++)
    t[0][i]=t[m+1][i]=0;
for(i=0;i<=m+1;i++)
    t[n+1][i]=t[i][n+1]=0;
for(i=0;i<=m+1;i++)
    for(j=0;j<=n+1;j++)
       {if(t[i][j]==1)
            {t[i][j]=-1;
            ultim=prim=0;
            ps.lin=i;
            ps.col=j;
            c[0]=ps;}

            while(prim<=ultim)
            {p=c[prim];
            prim++;
            for(k=1;k<=4;k++)
                {
                V.lin=p.lin+dl[k];
                V.col=p.col+dc[k];
                if(t[V.lin][V.col]==1)
                   {t[V.lin][V.col]=-1;
                    o++;
                    ultim++;
                    c[ultim]=V;}
                }
                }
                r[x]=o;
            x++;

        if(t[i][j]==2)
            {t[i][j]=-2;
            ultim=prim=0;
            ps.lin=i;
            ps.col=j;
            c[0]=ps;}

            while(prim<=ultim)
            {p=c[prim];
            prim++;
            for(k=1;k<=4;k++)
                {
                V.lin=p.lin+dl[k];
                V.col=p.col+dc[k];
                if(t[V.lin][V.col]==2)
                   {t[V.lin][V.col]=-2;
                    o++;
                    ultim++;
                    c[ultim]=V;}
                }
                }
                r[x]=o;
            x++;
                if(t[i][j]==3)
            {t[i][j]=-3;
            ultim=prim=0;
            ps.lin=i;
            ps.col=j;
            c[0]=ps;}

            while(prim<=ultim)
            {p=c[prim];
            prim++;
            for(k=1;k<=4;k++)
                {
                V.lin=p.lin+dl[k];
                V.col=p.col+dc[k];
                if(t[V.lin][V.col]==3)
                   {t[V.lin][V.col]=-3;
                    o++;
                    ultim++;
                    c[ultim]=V;}
                }
                }
                r[x]=o;
            x++;
            if(t[i][j]==4)
            {t[i][j]=-4;
            ultim=prim=0;
            ps.lin=i;
            ps.col=j;
            c[0]=ps;}

            while(prim<=ultim)
            {p=c[prim];
            prim++;
            for(k=1;k<=4;k++)
                {
                V.lin=p.lin+dl[k];
                V.col=p.col+dc[k];
                if(t[V.lin][V.col]==4)
                   {t[V.lin][V.col]=-4;
                    o++;
                    ultim++;
                    c[ultim]=V;}
                }
                }
                r[x]=o;
            x++;
                if(t[i][j]==5)
            {t[i][j]=-5;
            ultim=prim=0;
            ps.lin=i;
            ps.col=j;
            c[0]=ps;}

            while(prim<=ultim)r[x]=o;
            x++;
            {p=c[prim];
            prim++;
            for(k=1;k<=4;k++)
                {
                V.lin=p.lin+dl[k];
                V.col=p.col+dc[k];
                if(t[V.lin][V.col]==5)
                   {t[V.lin][V.col]=-5;
                    o++;
                    ultim++;
                    c[ultim]=V;}
                }
                }
                r[x]=o;
            x++;}

    for(i=0;i<=m+1;i++)
        {for(j=0;j<=n+1;j++)
            {g<<t[i][j];}g<<endl;}
    int maxi=0;
    for(i=1;i<=x;i++)
        if(r[i]>maxi)
            maxi=r[i];

    return 0;
}

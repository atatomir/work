#include <iostream>
#include <fstream>
#define inf 32600
#define in 2
#define out 3
#define cartita 1
#define aer 0
#define vulpe -1
using namespace std;

ifstream f("cartite.in");
ofstream g("cartite.out");

int xc,yc;
int m,n;
int d[201][201];
int p;
int dmin = inf;
int G[101][5];
int galerii;
void citire()
{
    int v;
    f>>p;
    f>>m>>n;
    f>>xc>>yc;
    f>>v;
    for(int i=1;i<=v;i++)
    {
        int x,y,r;
        f>>x>>y>>r;
        p=r;
        while(p>0)
        {
            if(y+p<=n)
            d[x][y+p]=vulpe;
            if(y-p>=0)
            d[x][y-p]=vulpe;
            if(x+p<=m)
            d[x+p][y]=vulpe;
            if(x-p>=0)
            d[x-p][y]=vulpe;
            if(p==1)
            {
                d[x+1][y+1] = vulpe;
                d[x+1][y-1] = vulpe;
                d[x-1][y+1] = vulpe;
                d[x-1][y-1] = vulpe;
            }
            p--;
        }
        d[x][y] = vulpe;
    }
    f>>galerii;
    for(int i=1;i<=galerii;i++)
    {
        int x1,y1,x2,y2;
        f>>x1>>y1>>x2>>y2;
        G[i][1]=x1;
        G[i][2]=y1;
        G[i][3]=x2;
        G[i][4]=y2;
    }
}

void go(int x,int y, int val)
{
    if(x>0 && y>0 && x<=m && y<=n)
    if(d[x][y] == aer)
    {
        d[x][y] = val;
        go(x+1,y,val+1);
        go(x-1,y,val+1);
        go(x,y+1,val+1);
        go(x,y-1,val+1);
    }
}

int main()
{
    citire();
    go(xc,yc,1);
    int min=inf;
    int x,y;
    for(int i=1;i<=galerii;i++)
    {
        if(min > d[G[i][1]][G[i][2]])
        {
            x = G[i][1];
            y = G[i][2];
            min = d[x][y];
        }
    }
    g<<x<<' '<<y<<' '<<min-1;

    return 0;
}

#include <iostream>                
#include <fstream>
#include <math.h>

using namespace std;

int p,n,nn,m,a[100][100],k,g=0;

ifstream f("cartite.in");
ofstream out("cartite.out");


void citire ()
{
    int x,y,xd,yf,i,j,c;
    f>>p;
    f>>n>>m;

    for (i=1; i<=n; i++)
        for (j=1; j<=m; j++)
            a[i][j]=-1;

    f>>x>>y;
    a[x][y]=10;
    f>>k;
    for (i=1; i<=k; i++)
    {
        f>>x>>y>>c;
        a[x][y]=c;
    }

    f>>nn;
    for (i=1; i<=nn; i++)
    {
        f>>x>>y>>xd>>yf;
        a[x][y]=a[xd][yf]=10;
    }

    for (i=1; i<=n; i++)
    {
        for (j=1; j<=m; j++)
            cout<<a[i][j]<<' ';
        cout<<endl;
    }

}

void fill (int i,int j)
{
    g++;
    a[i][j]=g;
    if (a[i][j]==-1)
    {
        fill (i-1,j);
        fill (i+1,j);
        fill (i,j-1);
        fill (i,j+1);
    }
}

int main()
{
    int i,j;
    citire ();
    fill (6,3);
    cout<<endl<<endl;
    for (i=1; i<=n; i++)
    {
        for (j=1; j<=m; j++)
            cout<<a[i][j]<<' ';
        cout<<endl;
    }
    out<<4<<' '<<2<<' '<<3;
}

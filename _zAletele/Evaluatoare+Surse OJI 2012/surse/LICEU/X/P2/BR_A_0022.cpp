#include <iostream>
#include<fstream>

using namespace std;
int x,y,l,n,c[100],a[100][100],pasi=0;
ofstream g("zona.out");

void citire ()
{
    int i;
    ifstream f("zona.in");
    f>>x>>y>>n>>l;
    for (i=1;i<=l;i++)
        f>>c[i];
}

void afisare ()
{
    int i,j;
    for (i=1;i<=n;i++)
    {
        for (j=1;j<=n;j++)
            cout<<a[i][j]<<' ';
        cout<<endl;
    }
}

int  verific (int i,int j)
{
    if (a[i][j]==0)
        return 1;
    else
        return 0;
}

void matrice ()
{
    int i,j;
    for (i=1;i<=n;i++)
        for (j=1;j<=n;j++)
            a[i][j]=0;
    a[x][y]=1;
}

void coor ()
{
    int i;
    matrice ();
    //afisare ();
    for (i=1;i<=l;i++)
        {
            if (c[i]==1)
            {
               x--;
               if (verific(x,y)==1)
                   a[x][y]=pasi++;
            }
            if (c[i]==2)
            {
                y++;
                if (verific(x,y)==1)
                   a[x][y]=pasi++;
            }
            if (c[i]==3)
            {
                x++;
                if (verific(x,y)==1)
                   a[x][y]=pasi++;
            }
            if (c[i]==4)
            {
                y--;
                if (verific(x,y)==1)
                   a[x][y]=pasi++;
            }
        }
        afisare ();
        cout<<endl<<pasi-1;
        g<<pasi-1;
}

int main()
{
    int i;
    citire ();
    coor ();
}

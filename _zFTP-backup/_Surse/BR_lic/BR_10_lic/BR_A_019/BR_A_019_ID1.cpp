#include <iostream>
#include <fstream>

using namespace std;

ifstream in("ferma.in");
ofstream out("ferma.out");

int varianta=0,m,n;
char lit[402][402];
int cif[402][402];
int max,Smax,maxi;
int SSmax[400];
int SSSmax;

int apa[27];

int xi,yi;
int searchx(int x)
{
    xi = yi = 0;
    int i=1,j=1;
    while(i<=n)
    {
        if(cif[i][j]==x)
        {
            xi = i;
            yi = j;
            return 1;
        }
        j++;
        if(j==m)
        {
                j = 1;
                i ++;
        }
    }
    return 0;
}

int xs;

void show()
{
    int i,j;
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=m;j++)
            out<<cif[i][j]<<" ";

        out<<'\n';
    }
    out<<"\n\n";

}


void fillit(int x, int y, int val)
{
    if(cif[x][y] == val&&x<n&&y<m)
    {
        cif[x][y] = -1;
        xs++;
        fillit(x+1,y,val);
        fillit(x,y+1,val);
        fillit(x,y,val);
        fillit(x,y-1,val);

    }
}

int sortit()
{
    int xc=0;
    for(int i = 1;i<=Smax;i++)
        if(SSmax[i]>xc && SSmax[i]<SSSmax)
            xc = SSmax[i];
    return xc;
}



void maxs()
{
    int i=1,j;
    for(i = 1;i<=n+1;i++)
        for(j = 1;j<=m+1;j++)
            if(searchx((int)lit[i][j]-'a'))
            {
                xs = 0;
                fillit(i,j,(int)lit[i][j]-'a');
                if(xs>SSmax[Smax])
                    {xi = i; yi = j;SSmax[Smax] = xs; SSSmax = xs;}

            }
}

void fill2(int x, int y)
{

}

int main()
{
    in>>varianta;
    in>>n>>m;
    maxi=1;
    char last;
    int i,j;
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
        {
            in>>lit[i][j];
            cif[i][j] = (int)lit[i][j]-'a';
        }



    //show();
   Smax = 1;


    switch(varianta)
    {
        case 1:
            maxs();
            out<<SSSmax<<'\n';
            //show();
        break;

        case 2:
            fill2(xi, yi);
        break;
    }
}

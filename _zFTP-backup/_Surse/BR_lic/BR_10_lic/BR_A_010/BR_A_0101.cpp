#include <fstream>
using namespace std;
ifstream fin("ferma.in");
ofstream fout("ferma.out");
struct poz
{
    int x, y;
};
poz maxpoz, dpoz[27];
const int MAX=420;
int n, m, v, mx, nr, ct, sw, sw2, cdpoz=0, k, l;
char a[MAX][MAX], b[MAX][MAX], c[MAX][MAX], r[MAX][MAX], crct, mxcrct;
void citire();
void umplea(int, int, int, char);
void umpleb(int, int, int, char);
void scriemx();
void scriesol();
int main()
{
    int i, j;
    citire();
    switch(v)
    {
        case 1:
        {
            mx=0;
            for(i=1; i<=m; i++)
                for(j=1; j<=n; j++)
                    if(a[i][j])
                    {
                        ct=0;
                        umplea(i, j, nr, a[i][j]);
                        if(ct>mx) mx=ct;
                    }
            scriemx();
        } break;
        case 2:
        {
            mx=0;
            for(k=1; k<=m; k++)
                for(l=1; l<=n; l++)
                    r[k][l]=a[k][l];
            for(i=1; i<=m; i++)
                for(j=1; j<=n; j++)
                    if(a[i][j])
                    {
                        for(k=1; k<=m; k++)
                            for(l=1; l<=n; l++)
                                c[k][l]=r[k][l];
                        ct=0;
                        nr++;
                        sw=true;
                        umplea(i, j, nr, c[i][j]);
                        ct=0;
                        umpleb(i, j, nr, c[i][j]);
                        if(ct>mx){
                            mx=ct;
                            maxpoz=dpoz[cdpoz-1];
                            mxcrct=crct;
                        }
                    }
            scriesol();
        }
    }
    fout.close();
    return 0;
}
void citire()
{
    int i;
    fin>>v>>m>>n;
    for(i=1; i<=m; i++)
        fin>>a[i];
    fin.close();
}
void scriemx()
{
    fout<<mx<<"\n";
}
void scriesol()
{
    fout<<maxpoz.x<<' '<<maxpoz.y<<'\n'<<mxcrct<<"\n";
}
void umplea(int x, int y, int nr, char ch)
{
    if(a[x][y]==ch)
    {
        ct++;
        a[x][y]=0;
        b[x][y]=nr;
        umplea(x+1, y, nr, ch);
        umplea(x-1, y, nr, ch);
        umplea(x, y+1, nr, ch);
        umplea(x, y-1, nr, ch);
    }
}
void umpleb(int x, int y, int nr, char ch)
{
    if(c[x][y]==ch)
    {
        ct++;
        c[x][y]=0;
        b[x][y]=nr;
        umpleb(x+1, y, nr, ch);
        umpleb(x-1, y, nr, ch);
        umpleb(x, y+1, nr, ch);
        umpleb(x, y-1, nr, ch);
    } else if(sw && x!=0 && y!=0)
    {
        int i;
        sw2=true;
        for(i=0; i<cdpoz; i++)
            if(dpoz[i].x==x && dpoz[i].y==y)
                sw2=false;
        if(sw2)
        {
            if(c[x+1][y]==ch && b[x+1][y]!=nr)
            {
                sw=false;
                ct++;
                dpoz[cdpoz].x=x;
                dpoz[cdpoz++].y=y;
                crct=ch;
                umpleb(x+1, y, b[x+1][y], ch);
            } else if(c[x-1][y]==ch && b[x-1][y]!=nr)
            {
                sw=false;
                ct++;
                dpoz[cdpoz].x=x;
                dpoz[cdpoz++].y=y;
                crct=ch;
                umpleb(x-1, y, b[x-1][y], ch);
            } else if(c[x][y+1]==ch && b[x][y+1]!=nr)
            {
                sw=false;
                ct++;
                dpoz[cdpoz].x=x;
                dpoz[cdpoz++].y=y;
                crct=ch;
                umpleb(x, y+1, b[x][y+1], ch);
            } else if(c[x][y-1]==ch && b[x][y-1]!=nr)
            {
                sw=false;
                ct++;
                dpoz[cdpoz].x=x;
                dpoz[cdpoz++].y=y;
                crct=ch;
                umpleb(x, y-1, b[x][y-1], ch);
            }
        }
    }
}

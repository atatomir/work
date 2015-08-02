#include <fstream>

using namespace std;


ifstream f("zona.in");
ofstream g("zona.out");

int x,y,n,l,i,j,a[54][54],d,s,nr,sta,sto,k;

int main()
{
    f>>x>>y>>n>>l;
    for (i=1;i<=n;i++)
        for (j=1;j<=n;j++)
            a[i][j]=0;
    for (i=1;i<=l;i++)
    {
        f>>d;
        if (d==1) {x--; a[x][y]=a[x+1][y]+1-a[x][y]; }
        if (d==2) {y++; a[x][y]=a[x][y-1]+1-a[x][y]; }
        if (d==3) {x++; a[x][y]=a[x-1][y]+1-a[x][y]; }
        if (d==4) {y--; a[x][y]=a[x][y+1]+1-a[x][y]; }
    }

    g<<a[x][y]<<endl;
    nr=l-a[x][y];
    s=0;
    k=0;
    for (i=1;i<=n;i++)
        {
            sta=0;
            sto=0;
            for (j=1;j<=n;j++)
            {
                if (a[i][j]>nr && sta==0) { sta=j; k++; }
                if (a[i][j]>nr && sta!=0) sto=j;
            }
            if (k==1) s=0;
                else s=s+sto-sta;

        }
    g<<s;
    f.close();
    g.close();
    return 0;
}




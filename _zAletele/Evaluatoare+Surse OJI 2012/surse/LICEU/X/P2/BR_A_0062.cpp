#include <fstream>

using namespace std;
#define LNG 2502
#define N 52

int main()
{
    ifstream f("zona.in");
    ofstream g("zona.out");
    int x,y,n,l,v[LNG],contor=0,i,j,a[N][N];
    f>>x>>y>>n>>l;
    for(i=0;i<=n+1;i++) a[0][i]=a[i][n+1]=a[i][0]=a[n+1][i]=-1;
    for(i=1;i<=l;i++)
    {
        f>>v[i];
        if(v[i]==1)
        {
            if(a[x-1][y]==1) break;
            a[x-1][y]=1;
            x=x-1;
            contor++;
        }
        else
        {
            if(v[i]==2)
            {
                if( a[x][y+1]==1) break;
                a[x][y+1]=1;
                y=y+1;
                contor++;
            }
            else
            {
                if(v[i]==3)
                {
                    if(a[x+1][y]==1) break;
                    a[x+1][y]=1;
                    x=x+1;
                    contor ++;
                }
                else
                {
                    if(v[i]==4)
                    {
                        if(a[x][y-1]==1) break;
                        a[x][y-1]=1;
                        y=y-1;
                        contor++;
                    }
                }
            }
        }
    }
    g<<contor-1;
    int imin,imax,jmin,jmax;
    imin=imax=jmin=jmax=0;
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            if(a[i][j]==1)
            {
                if(i<imin) imin=i;
                if(i>imax) imax=i;
                if(j<jmin) jmin=j;
                if(j>jmax) jmax=j;
            }
        }
    }
    g<<'\n'<<((jmax-jmin)*(imax-imin))/2;
}

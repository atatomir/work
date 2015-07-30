#include <fstream>
using namespace std;
ifstream f("ferma.in");
ofstream g("ferma.out");

int n,m,v,i,j,d,dmax,y;
char x,s[401][401];

void fill(int i,int j)
{
    if(s[i][j]==x)
    {
        d++;
        s[i][j]=s[i][j]-32;
        fill(i-1,j);
        fill(i+1,j);
        fill(i,j-1);
        fill(i,j+1);
    }
    if(d>dmax)
        dmax=d;
}

int main()
{
    f>>v;
    f>>m; f>>n;
    for(i=1;i<=m;i++)
        for(j=1;j<=n;j++)
            f>>s[i][j];
    if(v==1)
    {
            for(i=1;i<=m;i++)
        for(j=1;j<=n;j++)
            if(s[i][j]>='a' && s[i][j]<='z')
                {
                    d=0;
                    x=s[i][j];
                    fill(i,j);
                }
        g<<dmax;

    }
    if(v==2)
    {
        for(i=1;i<=m;i++)
            for(j=1;j<=n;j++)
                {

                    d=0;
                    x=s[i][j];
                    fill(i,j);
                }
    }

    f.close();
    g.close();
    return 0;
}

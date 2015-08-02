#include <fstream>
#include<iostream>
using namespace std;
ifstream f("betasah.in");
ofstream g("betasah.out");
int s[1001][1001],n,d,k,m,p,nr,x,y,z,t;

void declarare()
{
    int i,j;
    f>>n>>d>>k;
    for(i=1;i<=d;i++)
        {
            f>>x>>y;
            s[x][y]=2;
        }

     for(j=1;j<=k;j++)
        {
            f>>z>>t;
            s[z][t]=1;
        }
    for(i=1;i<=n-1;i++)
        for(j=i+1;j<=n;j++)
            s[i][j]=1;
}

void schimbare()
{
    int i,j;
     for(i=1;i<=n;i++)
        for(j=1;j<=i;j++)
            if(s[i][j]==2)
                {
                    if(s[i-1][j-1]==0)
                        s[i-1][j-1]=3;
                    if(s[i-1][j]==0)
                        s[i-1][j]=3;
                    if(s[i-1][j+1]==0)
                        s[i-1][j+1]=3;
                    if(s[i][j-1]==0)
                        s[i][j-1]=3;
                    if(s[i][j+1]==0)
                        s[i][j+1]=3;
                    if(s[i+1][j-1]==0)
                        s[i+1][j-1]=3;
                    if(s[i+1][j]==0)
                        s[i+1][j]=3;
                    if(s[i+1][j+1]==0)
                        s[i+1][j+1]=3;
                }

}

int main()
{
    int i,j;
    declarare();
    for(i=1;i<=n;i++)
        {
            for(j=1;j<=i;j++)
                if(s[i][j]==0 || s[i][j]==2) nr++;
            if(nr>=m)
                m=nr;
            nr=0;
        }
        g<<m<<'\n';

    schimbare();
    for(i=1;i<=n;i++)
        for(j=1;j<=i;j++)
            if(s[i][j]==3) p++;
    g<<p;
    f.close();
    g.close();
    return 0;
}

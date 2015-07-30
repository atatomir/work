#include <iostream>
#include<fstream>
using namespace std;

int main()
{int p,n,k,d,m,i,j,a[1500][1500]={0},x,y,nr;
ifstream f("pseudobil.in");
ofstream g("pseudobil.out");
f>>p;f>>n>>k>>d;
if(p==1)
g<<d+1;

else { for(i=1;i<=k;i++) {f>>x>>y; a[x][y]=1;}
        f>>m; x=0; y=0;
        for(i=1;i<=m;i++)
        {nr=0;
            f>>x>>y;
            a[x][y]=2;
            for(i=x;i<=n;i++)
             if(a[i][y]==1) nr++;
             for(i=y;i<=n;i++)
             if(a[x][i]==1) nr++;
             cout<<nr<<'\n';   }
        }


f.close(); g.close();



    return 0;
}

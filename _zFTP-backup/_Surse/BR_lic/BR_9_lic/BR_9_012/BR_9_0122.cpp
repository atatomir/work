#include <iostream>
#include <fstream>

using namespace std;

int c[1502][1502];

int main()
{
    ifstream f ("pseudobil.in");
    ofstream g ("pseudobil.out");
    int p,n,k,d,m,i,j,cnt=1,x,y,t,nrbile=0,a,b;
    f>>p>>n>>k>>d;
    if (p==1) {
        g<<d*d/2-d+1;
    }

    else {
        for (i=0;i<k;i++) {
            f>>a>>b; c[a][b]=1;
        }
        f>>m;
        for (t=0;t<m;t++) {
            f>>x>>y;
            cnt=1;
            nrbile=0;
            for(i=x;i<=d+x;i++){
                for (j=y-(cnt-1)/2;j<=y+(cnt-1)/2;j++) {
                    if (c[i][j]==1) nrbile++;
                }
                if (i<x+d/2) cnt+=2;
                else cnt-=2;
            }
            g<<nrbile<<"\n";
        }
    }
    f.close();
    g.close();

    return 0;
}

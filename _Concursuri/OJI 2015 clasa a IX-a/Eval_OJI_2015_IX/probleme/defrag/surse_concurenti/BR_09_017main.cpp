#include <fstream>
using namespace std;
int main()
{
int v,p,s,c,i,n,m,j,k=0,w[50][50];
ifstream f("defrag.in");
ofstream g("defrag.out");
f>>v>>p>>s>>c;
n=10;m=2;
if(v==1){
for(i=1;i<=p;i++)
    for(j=1;j<=s;j++) if(i==1&&j==1) k++;
g<<k;}
else{
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++) f>>w[i][j];
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++) if(w[i][j]<w[i+1][j+1]) {w[i][j]=w[i+1][j+1]-w[i][j];
        g<< w[i][j]<<' ';}}
f.close();
g.close();
return 0;
}

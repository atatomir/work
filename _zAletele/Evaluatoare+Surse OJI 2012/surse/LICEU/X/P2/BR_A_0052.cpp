#include <fstream>

using namespace std;

int main()
{

    ifstream f("zona.in");
    ofstream g("zona.out");

int a[100][100];
int x,y, n, p,i,j,s;
int nr=0;
f>>x;
f>>y;
f>>n;
f>>p;
for(i=x;i<=n;i++)
for(j=y;j<=n;j++)
{
if(p==1)
a[i][j]=a[i-1][j];
if(p==2)
a[i][j]=a[j][n+1];
if(p==3)
a[i][j]=a[i+1][j];
if{p==4)
a[i][j]=a[i][j-1];
}

s=a[i+1[j-1];
g<<s;
    f.close();
    g.close();
    return 0;
}

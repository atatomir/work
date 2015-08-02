#include <iostream>
#inlcude <fstream>
using namespace std;
int main()
{
    ifstream f("pseudobil.in");
    ofstream g("pseudobil. out");
    int p, n, k, d, a[n][n];
    f>>p;
    f>>n>>k>>d;
    for (i=1; i<=n; i++)
       for (j=1; j<=n; j++)
          a[i][j]=0;
    for (i=1; i<=k; i++)
    {
        f>>x>>y;
        a[x][y]=1;
    }
    f>>m;
    if (p==1)
    {
        for (i=1; i<=m; i++)
        {
            f>>x>>y;
        }
    }
    f.close(); g.close();
    return 0;
}

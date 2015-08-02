#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ifstream in("ferma.in");
    ofstream out("ferma.out");
    char a[200][200];
    int m,n,v,i,j,s=0,max=0;
    in>>v;
    in>>m;
    in>>n;
    for (i=1;i<=m;i++)
        for (j=1;j<=n;j++)
            in>>a[i][j];

    for (i=1;i<=m;i++)
        for (j=1;j<=n;j++)

    return 0;
}

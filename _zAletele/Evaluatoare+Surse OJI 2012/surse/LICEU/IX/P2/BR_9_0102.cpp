#include <iostream>
#include <fstream>
using namespace std;
int s[100],p[100];
int main()
{
    ifstream f("clepsidru.in");
    ofstream g("clepsidru.out");
    int n,b,i,j,k;
    f>>n;f>>b;
    f>>k;
    for (i=1;i<=k;i++)
        f>>s[i];
    for (i=1;i<=k;i++)
        f>>p[i];
    return 0;
}

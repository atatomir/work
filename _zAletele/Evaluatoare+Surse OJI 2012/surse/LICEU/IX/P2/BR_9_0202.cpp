#include <fstream>
using namespace std;
int n,i,k,p[1001],s[1001];
long b;
int main()
{
    ifstream in("clepsidru.in");
    ofstream out("clepsidru.out");
    in>>n>>b>>k;
    for(i=1;i<=k;i++)
        in>>s[i]>>p[i];
    out<<n+b-1;
}

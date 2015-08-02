#include <fstream>

using namespace std;
ifstream f("clepsidru.in");
ofstream g("clepsidru.out");
long b;
int n,k,s;
int main()
{f>>n>>b;
s=n+b-1;
g<<s<<"\n";
g<<1<<" "<<1<<"\n";
g<<0<<" "<<1;
    f.close();
    g.close();
    return 0;
}

#include <fstream>

using namespace std;
ifstream f("clepsidru.in");
ofstream g("clepsidru.out");

int main()
{
    long b,x;
    int k,n;
f>>n; f>>b;
x=b+n-1;
g<<x;
f.close();
g.close();

    return 0;
}

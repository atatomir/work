#include <fstream>
#include <iostream>
using namespace std;
int t,n;
long b;
int main()
{
    ifstream f("clepsidru.in");
    ofstream g("clepsidru.out");
    f>>n>>b;
    t=n+b-1;
    g<<t;
    f.close();
    g.close();
    return 0;
}

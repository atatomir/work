#include <iostream>
#include <fstream>
using namespace std;
int main()
{
    ifstream f("clepsidru.in");
    ofstream g("clepsidru.out");
    int n,b;
    f>>n>>b;
    g<<n+b-1<<'\n';
    f.close();
    g.close();
    return 0;
}

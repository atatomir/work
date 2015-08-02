#include <fstream>
#include <iostream>
using namespace std;

int main()
{int n,d,k,p;
    ifstream f("betasah.in");
    ofstream g("betasah.out");
    f>>n>>d>>k;
    p=n*(n+1)/2-k-d-1;
    g<<p;
    g.close();
    f.close();
    return 0;
}

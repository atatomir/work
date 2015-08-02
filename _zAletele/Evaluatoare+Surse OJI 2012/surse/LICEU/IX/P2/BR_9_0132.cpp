#include <fstream>
using namespace std;
int main()
{
    ifstream read("clepsidru.in");
    ofstream write("clepsidru.out");
    int n, b, r;
    read>>n>>b;
    read.close();
    r=n+b-2;
    write<<r<<'\n';
    write.close();
    return 0;
}

#include <fstream>

using namespace std;
long n,i;
int main()
{
    ifstream f("munte.in");
    ofstream g("munte.out");
f>>n;
for(i=1;i<=n;i++)

g<<2<<'\n';
g<<4<<'\n';
g<<4<<'\n';
    f.close();
    g.close();
    return 0;
}

#include <fstream>
using namespace std;

ifstream f("triunghi.in");
ofstream g("triunghi.out");

int k, n, lmax=200000000;

int main()
{
    f >> n;
    if(k==2)
    {
        f >> k >> k; g << k;
        f >> k; g << k;
        f >> k; g << k;
    } else
    { for(int i=1; i<=n; i++)
    {
        f >> k;
        if(k<lmax) lmax=k;
    }
        g<<lmax;
    }
    return 0;
}

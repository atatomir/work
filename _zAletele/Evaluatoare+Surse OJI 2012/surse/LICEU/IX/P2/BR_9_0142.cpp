#include <fstream>
using namespace std;

ifstream f("clepsidru.in");
ofstream g("clepsidru.out");

int n, b, k, s, j, i, bb, t, v[1000000];

int main()
{
    f >> n >> b >> k;
    for(i=1; i<=k; i++)
    {
        f >> s >> bb;
        t+=s;
        if(bb%2)
            for(i=1; i<=s; i++)
                v[i]=i;
        else
        {
            j=0;
            for(i=s; i>=1; i--)
                v[i]=++j;
        }
    }
    g << t+1 << '\n';
    for(i=1; i<=n*n; i++){
            if(v[i]) v[i]=1;
            g << v[i] << " ";
            if(i==n) g << '\n';
    }
    g << '\n';
    return 0;
}

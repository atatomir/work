#include <fstream>

using namespace std;
long xk,n,i,v[10001],s,p,w[10001],k;
int main()
{
    ifstream f("munte.in");
    ofstream g("munte.out");
        f>>n;
    for(i=1;i<=n;i++)
        {f>>v[i];
    for(k=1;k<=n;k++)
    f>>w[k];
    if(w[k]%1000==s)
    s=w[k];}


        {g<<xk<<'\n';
        g<<s<<'\n';
        g<<w[k]<<'\n';
        }

    f.close();
    g.close();

    return 0;
}

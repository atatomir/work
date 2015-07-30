#include <fstream>
#include <iostream>
using namespace std;

ifstream f("fractii2.in");
ofstream g("fractii2.out");

int p,n,i,v[5000],nr=1,ok=1,m,j;

int main()
{

    f>>p;
    f>>n;
    //cout<<p<<" "<<n;
    if (p==1)
    {
    for (i=1;i<n;i++) { g<<i; g<<" "; }
    g<<n-1;
    }
    for (i=1;i<=n-1;i++) v[i]=1;
    v[n-1]++;
    if (p==2) {
            ok=1;
            m=n-1;
            while (ok==1)
            {
                ok=0;
                for (i=m-1;i>1;i--)
                {
                    if (ok==0)
                    if (v[i+1]>1 && v[i-1]>0) {v[i-1]--; v[i]=v[i]+3; v[i+1]=v[i+1]-2; ok=1;
                                nr++;
                                if (v[m]==0) m--;
                                }
                }

            }
            g<<nr;
            }
    f.close();
    g.close();
    return 0;
}

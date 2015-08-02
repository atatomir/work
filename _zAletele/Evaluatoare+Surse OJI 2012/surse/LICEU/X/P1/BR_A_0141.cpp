#include <iostream>
#include <fstream>

using namespace std;

fstream f("calcule.in",ios::in);
fstream g("calcule.out",ios::out);

int n,i,j,a[100001];
unsigned short int s[100000],k;
long long nr;

int main()
{
    f>>n>>k;
    s[0]=0;
    g<<endl;
    for (i=1;i<=n;i++) {
                        f>>a[i];
                        s[i]=(s[i-1]+a[i])%k;
    }
    nr=0;
    for (i=1;i<=n;i++)
    {
        for (j=i;j<=n;j++)
        {
         if (s[j]-s[i-1]==0) nr++;
        }
    }
    g<<nr;
    f.close();g.close();
    return 0;
}

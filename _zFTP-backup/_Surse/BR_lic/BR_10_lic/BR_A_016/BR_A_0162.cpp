#include <fstream>
using namespace std;
ifstream f("triunghi.in");
ofstream g("triunghi.out");

int main()
{
    int v, n, k, i, j;
    long long a[50], min=0;
    f>>v;
    if (v==1)
    {
        f>>n;
        f>>k;
        for (i=1; i<=n; i++)
        {
            f>>a[i];
            if (i==1) min=a[i];
            else
                if (a[i]<min)
                    min=a[i];
        }
        for (i=0; i<=k-2; i++)
            if (i==0)
            {
                g<<min+i<<' ';
                g<<min+i<<' ';
            }
            else g<<(min+i)*10<<' ';
    }
f.close();
g.close();
return 0;
}

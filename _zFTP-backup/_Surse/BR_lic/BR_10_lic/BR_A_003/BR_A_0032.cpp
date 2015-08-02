#include <fstream>
#include <algorithm>
using namespace std;
int v, n, k;
long long a[50];
void read ()
{
    int i;
    ifstream in ("triunghi.in");
    in >> v >> n >> k;
    for (i = 1; i <= n; ++i)
    in >> a[i];
    in.close ();
}
int min ()
{
    int i, minx = a[1];
    for (i = 2; i <= n; ++i)
    if (a[i] < minx)
    minx = a[i];
    return minx;
}
void solve ()
{
    int i, minx;
    ofstream out ("triunghi.out");
    if (v == 1)
    {
        minx = min ();
        a[1] = a[2] = minx;
        out << minx << ' ' << minx << ' ';
        for (i = 3; i <= k; ++i)
        {
            a[i] = a[i - 1] + a[i - 2] + 1;
            out << a[i] << ' ';
        }
    }
    else
    {
        sort (a + 1, a + n + 1);
        out << a[1] << ' ' << a[2] << ' ' << a[3] << ' ';
        for (i = 4; i <= k; ++i)
        {
            a[i] = a[i - 1] + a[i - 2] + 1;
            out << a[i] << ' ';
        }
    }
    out.close ();
}
int main()
{
    read ();
    solve ();
    return 0;
}

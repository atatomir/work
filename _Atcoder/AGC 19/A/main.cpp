#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

ll a, b, c, d, n;
ll ans;

int main()
{
    freopen("test.in","r",stdin);

    cin >> a >> b >> c >> d >> n;
    c = min(c, 2LL * b);
    c = min(c, 4LL * a);
    d = min(d, 2LL * c);

    ans = (n / 2) * d + (n % 2) * c;
    cout << ans;



    return 0;
}

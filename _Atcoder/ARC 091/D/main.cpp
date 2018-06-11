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

ll n, k, a, b, c, r;
ll ans;

int main()
{
    freopen("test.in","r",stdin);

    cin >> n >> k;
    for (b = k + 1; b <= n; b++) {
        c = n / b;

        ans += c * (b - k);
        ans += max(0LL, (n % b) - k + 1);
    }

    if (k == 0) ans -= n;

    cout << ans;


    return 0;
}

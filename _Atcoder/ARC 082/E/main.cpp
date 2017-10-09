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

#define maxN 211
#define mod 998244353

int n, i, j, k;
pair<int, int> P[maxN];
vector< pair<int, int> > ord;

ll pows[maxN];
ll ans, dx, dy, d;

ll gcd(ll a, ll b) {
    if (a < 0) a *= -1;
    if (b < 0) b *= -1;
    if (a < b) swap(a, b);

    while (b > 0) {
        a %= b;
        swap(a, b);
    }

    return a;
}

int main()
{
    freopen("test.in","r",stdin);

    cin >> n;
    for (i = 1; i <= n; i++)
        cin >> P[i].first >> P[i].second;

    pows[0] = 1;
    for (i = 1; i <= n; i++)
        pows[i] = (pows[i - 1] * 2) % mod;

    ans = pows[n];

    for (i = 1; i <= n; i++) {
        ord.clear();
        for (j = i + 1; j <= n; j++) {
            dx = P[i].first - P[j].first;
            dy = P[i].second - P[j].second;

            if (dx < 0) {
                dx *= -1;
                dy *= -1;
            }

            if (dx == 0 && dy < 0)
                dy *= -1;

            d = gcd(dx, dy);
            dx /= d;
            dy /= d;
            ord.pb(mp(dx, dy));
        }

        sort(ord.begin(), ord.end());
        for (j = 0; j < ord.size(); j = k) {
            for (k = j; k < ord.size(); k++)
                if (ord[j] != ord[k])
                    break;

            ans += mod - pows[k - j] + 1;
            ans %= mod;
        }

        ans += mod - 1;
        ans %= mod;
    }

    ans += mod - 1;
    ans %= mod;

    cout << ans;

    return 0;
}

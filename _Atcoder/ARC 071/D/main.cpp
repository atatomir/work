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

#define mod 1000000007
#define maxN 100011

int n, m, i;
ll x[maxN], y[maxN];

ll solve(int dim, ll *data) {
    ll ans = 0;
    ll sum = 0;
    ll i;

    sort(data + 1, data + dim + 1);

    for (i = 1; i <= dim; i++) {
        ans += (i - 1) * data[i] + mod - sum;
        ans %= mod;

        sum += data[i];
        sum %= mod;
    }

    return ans;
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) scanf("%lld", &x[i]);
    for (i = 1; i <= m; i++) scanf("%lld", &y[i]);

    ll ans = (solve(n, x) * solve(m, y)) % mod;
    printf("%lld", ans);

    return 0;
}

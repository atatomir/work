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

#define maxN 300011
#define mod 1000000007

int n, i;
int a[maxN], cnt_set, cnt_other, sum_set[maxN], sum_lower[maxN];
bool is_set[maxN];
ll fact[maxN], prop[maxN];
int aib[maxN];

int zrs(int x) {
    return (x ^ (x - 1)) & x;
}

void add(int pos, int v) {
    while (pos <= n) {
        aib[pos] += v;
        pos += zrs(pos);
    }
}

int sum(int x) {
    int ans = 0;
    while (x > 0) {
        ans += aib[x];
        x -= zrs(x);
    }
    return ans;
}

void solve() {
    int i;
    ll aux;

    cnt_other = n - cnt_set;

    //! set - set
    for (i = n; i > 0; i--) {
        if (a[i] == 0) continue;
        prop[i] = (sum(a[i]) * fact[n - sum_set[n]] ) % mod;
        add(a[i], +1);
    }

    //! ? - ?
    for (i = n; i > 0; i--) {
        if (a[i] != 0) continue;
        aux = (n - sum_set[n]);
        aux = (aux * (aux - 1)) / 2LL;
        aux %= mod;
        aux *= (n - i) - (sum_set[n] - sum_set[i]);
        aux %= mod;
        if (n - sum_set[n] - 2 >= 0)
            aux *= fact[n - sum_set[n] - 2];
        else aux = 0;

        prop[i] = (prop[i] + aux) % mod;
    }

    //! ? - set
    memset(aib, 0, sizeof(aib));
    for (i = 1; i <= n; i++)
        if (!is_set[i])
            add(i, +1);

    aux = 0;
    for (i = n; i > 0; i--) {
        if (a[i] != 0) {
            aux += sum(n) - sum(a[i]);
            aux %= mod;
            continue;
        }
        ll aux2 = aux * fact[n - sum_set[n] - 1];
        prop[i] = (prop[i] + aux2) % mod;
    }

    //! set - ?
    for (i = 1; i <= n; i++)
        sum_lower[i] = sum_lower[i - 1] + (is_set[i] == 0 ? 1 : 0);

    for (i = n; i > 0; i--) {
        if (a[i] == 0) continue;

        aux = (n - i) - (sum_set[n] - sum_set[i]);
        aux *= sum_lower[a[i]];
        aux %= mod;

        if (n - sum_set[n] - 1 >= 0)
            aux *= fact[n - sum_set[n] - 1];
        else
            aux = 0;
        prop[i] = (prop[i] + aux) % mod;
    }
}

int main()
{
    freopen("test.in","r",stdin);
    freopen("test.out","w",stdout);

    cin >> n;
    fact[0] = 1;

    for (i = 1; i <= n; i++) {
        cin >> a[i];
        is_set[a[i]] = true;
        if (a[i] != 0) cnt_set++;

        fact[i] = fact[i - 1] * i;
        fact[i] %= mod;

        sum_set[i] = sum_set[i - 1] + (a[i] > 0 ? 1 : 0);
    }

    solve();

    ll ans = 0;
    for (i = 1; i <= n; i++)
        ans = (ans + fact[n - i] * prop[i]) % mod;

    ans = (ans + fact[n - sum_set[n]]) % mod;
    cout << ans;

    return 0;
}

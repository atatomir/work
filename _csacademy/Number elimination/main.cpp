#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 100011
#define mod 1000000007LL
#define ll long long

ll fact[maxN << 1];
ll inv_fact[maxN << 1];

int n, i, j, pos;
int v[maxN];
int how[maxN];

ll op_done;
ll dp[maxN];

ll my_pow(ll a, ll b) {
    ll ans = 1;

    while (b) {
        if (b & 1) ans = (ans * a) % mod;
        b >>= 1;
        a = (a * a) % mod;
    }

    return ans;
}

void preprocess() {
    int i;
    int limit = 200000;

    fact[1] = inv_fact[1] = 1;
    fact[0] = inv_fact[0] = 1;
    for (i = 2; i <= limit; i++) {
        fact[i] = (fact[i - 1] * i) % mod;
        inv_fact[i] = my_pow(fact[i], mod - 2);
    }
}

ll comb(ll n, ll k) {
    return (((fact[n] * inv_fact[k]) % mod) * inv_fact[n - k])% mod;
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++)
        scanf("%d", &v[i]);
    sort(v + 1, v + n + 1);

    for (i = 1; i <= n; i++) {
        how[++pos] = 1;

        for (j = i + 1; j <= n && v[i] == v[j]; j++)
            how[pos]++;
        i = j - 1;
    }

    n = pos;
    preprocess();

    dp[0] = 1;
    op_done = 1;

    for (i = 1; i <= n; i++) {
        dp[i] = 0;

        ll battles = (fact[how[i] - 1] * fact[ how[i] ]) % mod;
        battles = (battles * my_pow( my_pow(2, how[i] - 1) , mod - 2)  ) % mod;

        if (i == 1) {
            dp[1] = battles;
            op_done = how[i] - 1;
            continue;
        }

        for (j = 1; j <= how[i]; j++) {
            //! j stored until the end
            int k = (how[i] - j);

            ll aux = (battles * j) % mod;
            aux = (aux * comb(op_done + k, k)) % mod;

            dp[i] += aux;
            if (dp[i] >= mod)
                dp[i] -= mod;
        }

        dp[i] = (dp[i] * dp[i - 1]) % mod;
        op_done += how[i];
    }

    printf("%lld", dp[n]);

    return 0;
}

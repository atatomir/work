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

#define maxN 111

int n, k, i, j, act, rez;
ll dp[maxN][maxN];
ll fact[maxN];
ll ans;

ll last[maxN], bad[maxN], good[maxN];

ll solve(ll n, ll k) {
    ll i, j, p, l;

    memset(dp, 0, sizeof(dp));
    ans = 0;

    for (i = 1; i <= n; i++)
        dp[i][i - 1] = 1;

    for (i = 1; i <= n; i++) {
        for (j = 0; j <= i; j++) {
            if (dp[i][j] == 0) continue;

            for (p = 1; i + p <= n; p++) {
                for (l = 0; l < k && l <= j; l++) {
                    dp[i + p][j + p - l - 1] += dp[i][j] * fact[j] / fact[j - l];
                }
            }
        }
    }

    for (i = 0; i <= n; i++)
        ans += dp[n][i] * fact[i];

    return ans;
}

ll comb(ll a, ll b) {
    return fact[a] / (fact[b] * fact[a - b]);
}

ll solve2(ll n, ll k) {
    ll i, p, ans = 0;

    last[0] = bad[0] = 0;
    good[0] = 1;

    for (i = 1; i <= n; i++) {
        for (p = k; p < i; p++)
            last[i] += (fact[i - 1] / fact[i - 1 - p]) * good[i - p - 1];
        for (p = k + 1; p <= i; p++)
            bad[i] += last[p] * fact[i - p] * comb(i, p);
        good[i] = fact[i] - bad[i];

        if (i != n)
        ans += fact[n - i] * last[i] * comb(n - 1, n - i - 1);
    }

    return ans;
}

int main()
{
    freopen("test.in","r",stdin);
    freopen("test.ok", "w", stdout);

    cin >> n >> k;

    fact[0] = 1;
    for (i = 1; i <= n; i++)
        fact[i] = (fact[i - 1] * i) ;

    cout << facsolve(n, k);

    /*for (i = 1; i <= n; i++) {
        cerr << solve(i, k) << ' ';
        cout << "(" << i << ',' << solve(i, k) << ") ";
    }*/

    /*for (i = 1; i <= n; i++) {
        for (j = 1; j <= k; j++)
            cerr << solve(i, j) << ' ';
        cerr << '\n';
    }*/

    //cerr << solve2(n, k);


    return 0;
}

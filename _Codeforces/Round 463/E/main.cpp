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
#define maxN 5017

const int limit = 100;
const int maxBrute = limit + 11;


ll n, k, i, j;
ll dp[maxN][maxN], ans;

ll comb[maxBrute][maxBrute];
ll poww[maxBrute][maxBrute];

ll powww(ll a, ll b) {
    ll ans = 1;

    while (b > 0) {
        if (b & 1) ans = (ans * a) % mod;
        b >>= 1;
        a = (a * a) % mod;
    }

    return ans;
}

ll brute_compute(ll n, ll k) {
    ll ans = 0;
    ll i;

    for (i = 1; i <= n; i++) {
        ans += comb[n][i] * poww[i][k];
        ans %= mod;
    }

    return ans;
}

void brute() {
    int i, j, k;

    if (n >= 100 || k >= 100) return;

    for (i = 0; i <= limit; i++) {
        comb[i][0] = 1;
        for (j = 1; j <= i; j++) {
            comb[i][j] = comb[i - 1][j] + comb[i - 1][j - 1];
            comb[i][j] %= mod;
        }
    }

    for (i = 1; i <= limit; i++) {
        poww[i][1] = 1;
        for (j = 2; j <= limit; j++) {
            poww[i][j] = poww[i][j - 1] * i;
            poww[i][j] %= mod;
        }
    }

    for (i = 1; i <= 10; i++) cerr << brute_compute(i, 1) << ' '; cerr << '\n';
    for (i = 1; i <= 10; i++) cerr << brute_compute(i, 2) << ' '; cerr << '\n';
    for (i = 1; i <= 10; i++) cerr << brute_compute(i, 3) << ' '; cerr << '\n';
    for (i = 1; i <= 10; i++) cerr << brute_compute(i, 4) << ' '; cerr << '\n';
    for (i = 1; i <= 10; i++) cerr << brute_compute(i, 5) << ' '; cerr << '\n';
    for (i = 1; i <= 10; i++) cerr << brute_compute(i, 6) << ' '; cerr << '\n';
    for (i = 1; i <= 10; i++) cerr << brute_compute(i, 7) << ' '; cerr << '\n';
    for (i = 1; i <= 10; i++) cerr << brute_compute(i, 8) << ' '; cerr << '\n';
}

ll combb(ll n, ll k) {
    if (n < k) return 0;

    ll up = 1;
    ll down = 1;
    ll i;

    for (i = 0; i < k; i++) {
        up *= n - i;
        up %= mod;

        down *= (i + 1);
        down %= mod;
    }

    up *= powww(down, mod - 2);
    up %= mod;

    return up;
}

int main()
{
    //freopen("test.in","r",stdin);

    cin >> n >> k;
    //brute();

    dp[1][1] = 1;
    for (i = 1; i <= k; i++) {
        for (j = 1; j <= i; j++) {
            dp[i + 1][j + 1] += dp[i][j] * (j + 1);
            dp[i + 1][j + 1] %= mod;

            dp[i + 1][j] += dp[i][j] * j;
            dp[i + 1][j] %= mod;
        }
    }

    for (i = 1; i <= k; i++) {
        ll aux = dp[k][i] * powww(2, n - i);
        aux %= mod;

        aux *= combb(n, i);
        aux %= mod;

        ans += aux;
        ans %= mod;
    }

    cout << ans;


    return 0;
}

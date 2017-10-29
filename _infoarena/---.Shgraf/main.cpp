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

#define maxN 255
#define mod 30011

int n, k, i, j, act;
int dp[maxN][maxN], cnt[maxN];
int dp2[maxN];

int comb[maxN][maxN], aux;
int fact[maxN];
int trees[maxN];

int poww(int a, int b) {
    int ans = 1;

    while (b > 0) {
        if (b & 1) ans = (ans * a) % mod;
        b >>= 1;
        a = (a * a) % mod;
    }

    return ans;
}

int main()
{
    freopen("shgraf.in","r",stdin);
    freopen("shgraf.out","w",stdout);

    cin >> n >> k;

    for (i = 0; i <= n; i++) {
        comb[i][0] = 1;

        for (j = 1; j <= i; j++)
            comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % mod;
    }

    fact[0] = 1;
    fact[1] = fact[2] = 1;
    for (i = 3; i <= n; i++)
        fact[i] = (fact[i - 1] * i) % mod;

    trees[0] = 1;
    trees[1] = 1;
    trees[2] = 1;
    for (i = 3; i <= n; i++)
        trees[i] = poww(i, i - 2);

    dp[0][0] = 1;
    for (i = 0; i <= n; i++) {
        for (j = 0; i + j <= n; j++) {
            if (dp[i][j] == 0) continue;

            if (i >= k) {
                aux = (dp[i][j] * fact[i - 1]) % mod;
                aux = (aux * comb[i + j][i]) % mod;

                cnt[i + j] += aux;
                cnt[i + j] %= mod;
            }

            for (act = 0; i + 1 + j + act <= n; act++) {
                aux = (dp[i][j] * trees[act + 1]) % mod;
                aux = (aux * comb[j + act][act]) % mod;

                dp[i + 1][j + act] = (dp[i + 1][j + act] + aux);
                if (dp[i + 1][j + act] >= mod) dp[i + 1][j + act] -= mod;
            }
        }
    }

    dp2[0] = 1;
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= i; j++) {
            aux = (dp2[i - j] * cnt[j]) % mod;
            aux = (aux * comb[i - 1][j - 1]) % mod;

            dp2[i] += aux;
            if (dp2[i] >= mod) dp2[i] -= mod;
        }
    }

    cout << dp2[n];



    return 0;
}

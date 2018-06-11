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

const int maxN = 71;

ll n, k, i;
char data[maxN];
ll dp[maxN], pr[maxN];

bool can(int p1, int p2, int cnt) {
    while (cnt > 0) {
        cnt--;
        if (data[p1] == 'a' && data[p2] == 'b') return false;
        if (data[p1] == 'b' && data[p2] == 'a') return false;
        p1++; p2++;
    }

    return true;
}

ll count_borderless(ll must) {
    ll i, u, same, aux;

    dp[1] = 1;
    u = 0;
    for (i = 2; i <= must; i++) {
        while (u != 0 && data[u + 1] != data[i]) u = pr[u];
        if (data[u + 1] == data[i]) u++;
        pr[i] = u;

        dp[i] = 1;
        if (u > 0) dp[i] = 0;
    }

    for (i = must + 1; i <= n; i++) {
        dp[i] = 1LL << (i - must);

        for (same = 1; 2 * same <= i; same++) {
            if (!can(1, i - same + 1, same)) continue;
            aux = dp[same] << max(0LL, i - same - max(same, must));
            dp[i] -= aux;
        }
    }

    return dp[n];
}

void solve() {
    ll i, aux;

    for (i = 0; i <= n + 1; i++) data[i] = '.';
    for (i = 1; i <= n; i++) {
        data[i] = 'a';
        aux = count_borderless(i);
        if (aux < k) {
            k -= aux;
            data[i] = 'b';
        }

        printf("%c", data[i]);
    }
    printf("\n");
}

int main()
{
    freopen("borderless.in","r",stdin);
    freopen("borderless.out","w",stdout);

    while (true) {
        cin >> n >> k;
        if (n == 0) return 0;

        solve();
    }


    return 0;
}

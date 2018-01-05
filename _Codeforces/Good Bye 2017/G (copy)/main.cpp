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

#define maxN 711
#define mod 1000000007

int n, i, j;
char s[maxN];
ll poww[maxN], sum[maxN];
int alrdn[11];
ll ans;

ll comb[maxN][maxN];
ll dp[maxN][11], cnt[maxN][11], aux, ss[11];
ll last;

void add(ll& data, ll b) {
    data += b;
    if (data >= mod) data -= mod;
}

void solve() {
    int i, j, k;
    ll aux, aux2, aux3, aux4;

    memset(dp, 0, sizeof(dp));
    memset(cnt, 0, sizeof(cnt));

    ss[0] = alrdn[0];
    for (i = 1; i <= 9; i++) ss[i] = ss[i - 1] + alrdn[i];

    for (i = alrdn[0]; i <= n; i++) {
        dp[i][0] = 0;
        cnt[i][0] = 1;
    }

    for (i = alrdn[0]; i <= n; i++) {
        for (j = 0; j < 9; j++) {
            if (cnt[i][j] == 0) continue;

            for (k = alrdn[j + 1]; i + k + ss[9] - ss[j + 1] <= n; k++) {
                aux = comb[i + k - ss[j + 1]][k - alrdn[j + 1]];
                aux2 = (dp[i][j] * aux) % mod;
                aux3 = (cnt[i][j] * aux) % mod;

                aux4 = (aux3 * (j + 1)) % mod;
                aux4 = (aux4 * (mod + sum[i + 1] - sum[i + k + 1])) % mod;
                add(aux4, aux2);

                add(dp[i + k][j + 1], aux4);
                add(cnt[i + k][j + 1], aux3);
            }
        }
    }

    last = dp[n][9];
    add(ans, dp[n][9]);
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%s", s + 1);
    n = strlen(s + 1);

    //n = 100;
    //for (i = 1; i <= n; i++) s[i] = '8';

    for (i = n; s[i] == '9'; i--);
    if (i == 0) {
        for (i = 2; i <= n + 1; i++) s[i] = '0';
        s[1] = '1';
        n++;
    } else {
        s[i]++;
        for (i++; i <= n; i++) s[i] = '0';
    }

    poww[n] = 1;
    sum[n] = 1;
    for (i = n - 1; i > 0; i--) {
        poww[i] = (poww[i + 1] * 10) % mod;
        sum[i] = (sum[i + 1] + poww[i]) % mod;
    }

    for (i = 0; i <= n; i++) {
        comb[i][0] = 1;
        for (j = 1; j <= i; j++)
            comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % mod;
    }

    for (i = 1; i <= n; i++) {
        for (j = 0; j < s[i] - '0'; j++) {
            alrdn[j]++;
            solve();
            alrdn[j]--;
        }

        alrdn[s[i] - '0']++;
    }

    printf("%lld", ans);


    return 0;
}

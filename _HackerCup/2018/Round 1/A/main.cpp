#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

const int maxN = 1024;
const int mod = 1000000007;

int t, ti;
int n, i, j;
char s[5][maxN];
ll dp[5], aux[5];

void add(ll& a, ll b) {
    a += b;
    if (a >= mod) a -= mod;
}

ll solve() {
    int i, j;

    if (s[1][1] == '#' || s[3][n] == '#') return 0;
    dp[1] = 1;
    dp[2] = dp[3] = 0;

    for (j = 2; j <= n; j++) {
        for (i = 1; i <= 3; i++) {
            aux[i] = dp[i];
            dp[i] = 0;
        }

        if (s[2][j - 1] == '.' && s[2][j] == '.') {
            add(dp[2], aux[1]);
            add(dp[2], aux[3]);
        }

        if (s[1][j - 1] == '.' && s[1][j] == '.')
            add(dp[1], aux[2]);

        if (s[3][j - 1] == '.' && s[3][j] == '.')
            add(dp[3], aux[2]);
    }

    return dp[2];
}

int main()
{
    freopen("input.in","r",stdin);
    freopen("output.out", "w", stdout);

    scanf("%d", &t);
    cerr << "Solve " << t << " tests\n";

    for (ti = 1; ti <= t; ti++) {
        cerr << "#" << ti << '\n';

        scanf("%d\n", &n);
        for (i = 1; i <= 3; i++) scanf("%s\n", s[i] + 1);

        printf("Case #%d: %lld\n", ti, solve());
    }


    return 0;
}

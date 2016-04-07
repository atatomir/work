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

#define maxN 1024
#define maxVal 70

int n, i, j, col;
int v[maxN];
int dp[maxN][maxN];
int ans;

int compute(int l, int r) {
    if (dp[l][r]) return dp[l][r];

    if (l == r) {
        dp[l][r] = v[l];
        return dp[l][r];
    }

    dp[l][r] = -1;
    for (int k = l; k < r; k++)
        if (compute(l, k) == compute(k + 1, r) && compute(l, k) != -1)
            {dp[l][r] = compute(l, k) + 1; break; }

    return dp[l][r];
}

int main()
{
    freopen("262144.in","r",stdin);
    freopen("262144.ok","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) scanf("%d", &v[i]);

    if (n >= maxN) return 7 / 0;

    for (i = 1; i <= n; i++)
        for (j = i; j <= n; j++)
            ans = max(ans, compute(i, j));

    printf("%d", ans);


    return 0;
}

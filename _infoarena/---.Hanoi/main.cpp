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

#define maxN 256
#define inf 1000000000000000


int n, m, i, j;
ll dp[maxN][maxN];

int dim;
int ans[111];


void print_for_three(int n) {
    dim = ans[1] = 1;

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= dim; j++) ans[j] *= 2;
        for (j = 1; j <= dim; j++) {
            ans[j + 1] += ans[j] / 10;
            ans[j] %= 10;
        }
        if (ans[dim + 1]) dim++;
    }

    ans[1]--;
    for (i = dim; i > 0; i--) printf("%d", ans[i]);
}

ll compute(int pg, int di) {
    if (dp[pg][di]) return dp[pg][di];

    if (di >= 50)
        dp[pg][di] = inf;
    else
        dp[pg][di] = (1LL << di) - 1;

    if (pg == 3) return dp[pg][di];

    for (int k = 1; k < di; k++)
        dp[pg][di] = min(dp[pg][di], compute(pg, k) + compute(pg - 1, di - k) + compute(pg, k));

    return dp[pg][di];
}

int main()
{
    freopen("hanoi.in","r",stdin);
    freopen("hanoi.out","w",stdout);

    scanf("%d%d", &n, &m);
    if (m == 3) {
        print_for_three(n);
        return 0;
    }

    printf("%lld\n", compute(m, n));



    return 0;
}

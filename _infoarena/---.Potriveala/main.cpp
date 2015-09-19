#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 250011

int n, m, i, dim;
char big[maxN];
char small[maxN << 1];
char work[maxN << 2];
int ans;

int dp[2][maxN << 2];
//! le - 0
//! ri - 1

void solve(int id) {
    int start = 0;
    int last = 0;

    for (int i = 2; i <= dim; i++) {
        if (i <= last) dp[id][i] = min(last - i + 1, dp[id][i - start + 1]);
        while (work[ dp[id][i] + 1 ] == work[ i + dp[id][i] ]) dp[id][i]++;

        if (i + dp[id][i] - 1 > last) {
            start = i;
            last = i + dp[id][i] - 1;
        }
    }
}

int main()
{
    freopen("potriveala.in","r",stdin);
    freopen("potriveala.out","w",stdout);

    scanf("%s\n%s", big + 1, small + 1);
    n = strlen(big + 1);
    m = strlen(small + 1);

    int how = (n / m) + 1;
    int aux = m;
    while(--how > 0)
        for (i = 1; i <= aux; i++) small[++m] = small[i];

    for (i = 1; i <= m; i++) work[i] = small[i];
    work[m + 1] = '@';
    for (i = 1; i <= n; i++) work[m + 1 + i] = big[i];
    work[n + m + 2] = '#';

    dim = n + m + 1;

    solve(1);

    reverse(work + 1, work + m + 1);
    reverse(work + m + 2, work + dim + 1);
    solve(0);
    reverse(dp[0] + m + 2, dp[0] + dim + 1);

    for (i = 1; i < n; i++) {
        int aux = dp[0][m + 1 + i] + dp[1][m + 1 + i + 1];
        ans = max(ans, aux);
    }

    printf("%d", ans);

    return 0;
}

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stack>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 153

int n, m, i, j, l1, l2;
int a[maxN][maxN], sum[maxN][maxN], up[maxN][maxN];
short dp[2][maxN][maxN][maxN];
stack< pair<int, int> > S;
int l[maxN], r[maxN];
int ans;

void pre(int id) {
    int i, j, ln, dim;

    if (id == 0) {
        for (i = 1; i <= m; i++)
            for (j = 1; j <= m; j++)
                dp[0][0][i][j] = - n * m;

        for (i = 1; i <= n + 1; i++)
            memcpy(dp[0][i], dp[0][0], sizeof(dp[0][0]));

        memcpy(dp[1], dp[0], sizeof(dp[1]));
    }

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            up[i][j] = 0;
            if (a[i][j] == 0)
                up[i][j] = 1 + up[i - 1][j];
        }
    }

    for (ln = 1; ln <= n; ln++) {
        // from left
        while (!S.empty()) S.pop();
        S.push(mp(-1, 0));

        for (i = 1; i <= m; i++) {
            while (S.top().first >= up[ln][i])
                S.pop();
            l[i] = S.top().second + 1;
            S.push(mp(up[ln][i], i));
        }

        // from right
        while (!S.empty()) S.pop();
        S.push(mp(-1, m + 1));

        for (i = m; i > 0; i--) {
            while (S.top().first >= up[ln][i])
                S.pop();
            r[i] = S.top().second - 1;
            S.push(mp(up[ln][i], i));
        }

        // conclude

        for (i = 1; i <= m; i++)
            if (up[ln][i] && l[i] + 1 <= r[i] - 1)
                dp[id][ln][l[i] + 1][r[i] - 1] = max((int)dp[id][ln][l[i] + 1][r[i] - 1], (r[i] - l[i] + 1) * up[ln][i]);

        for (dim = m - 1; dim >= 0; dim--)
            for (i = 1; i + dim <= m; i++)
                dp[id][ln][i][i + dim] = max(dp[id][ln][i][i + dim], max(dp[id][ln][i - 1][i + dim], dp[id][ln][i][i + dim + 1]));

    }
}

inline bool good(int ln, int j1, int j2) {
    return sum[ln][j2] - sum[ln][j1 - 1] == 0;
}

void solve(int l1, int l2, int j1, int j2) {
    static int i;
    static pair<int, int> best;

    for (i = l1; i <= l2; i++) {
        l[i] = dp[0][i - 1][j1][j2];
        r[i] = dp[1][n - (i + 1) + 1][j1][j2];
    }


    best = mp(-1000000, -1);
    for (i = l1; i <= l2; i++) {
        best = max(best, mp(l[i], i));
        best.first += j2 - j1 + 1;

        ans = max(ans, best.first + r[i]);
    }
}

int main()
{
    freopen("imax.in","r",stdin);
    freopen("imax.out","w",stdout);


    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            scanf("%d", &a[i][j]);

    pre(0);
    for (i = 1; 2 * i <= n; i++)
        for (j = 1; j <= m; j++)
            swap(a[i][j], a[n - i + 1][j]);
    pre(1);

    for (i = 1; 2 * i <= n; i++)
        for (j = 1; j <= m; j++)
            swap(a[i][j], a[n - i + 1][j]);

    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            sum[i][j] = a[i][j] + sum[i][j - 1];

    for (int j1 = 2; j1 < m; j1++) {
        for (int j2 = j1; j2 < m; j2++) {
            for (l1 = 2; l1 < n; l1 = l2) {
                if (!good(l1, j1, j2)) {
                    l2 = l1 + 1;
                    continue;
                }

                for (l2 = l1; good(l2, j1, j2) && l2 <= n; l2++);
                solve(l1, l2 - 1, j1, j2);
            }
        }
    }

    printf("%d", ans);
    cerr << ans;




    return 0;
}

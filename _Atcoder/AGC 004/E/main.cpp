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

#define maxN 101
#define act dp[l][r][u][d]

int n, m, i, j, ex, ey;
char s[maxN][maxN];
short dp[maxN][maxN][maxN][maxN];
int sum[maxN][maxN];
int l, r, u, d;
short ans;

inline short get_sum(int x1, int y1, int x2, int y2) {
    return max(0, sum[x2][y2] - sum[x1 - 1][y2] - sum[x2][y1 - 1] + sum[x1 - 1][y1 - 1]);
}

void upd(short& dest, short sour) {
    if (sour > dest) dest = sour;
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d\n", &n, &m);
    for (i = 1; i <= n; i++) {
        scanf("%s\n", s[i] + 1);
        for (j = 1; j <= m; j++) {
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
            if (s[i][j] == 'o') sum[i][j]++;
            if (s[i][j] == 'E') ex = i, ey = j;
        }
    }

    for (l = 0; l < ey; l++) {
        for (r = 0; ey + r <= m; r++) {
            for (u = 0; u < ex; u++) {
                for (d = 0; ex + d <= n; d++) {

                    ans = max(ans, act);

                    // go right
                    if (ey + r + 1 <= m - l) {
                        upd(dp[l][r + 1][u][d], act + get_sum(max(d + 1, ex - u), ey + r + 1,
                                                              min(n - u, ex + d), ey + r + 1));
                    }

                    // go left
                    if (ey - l - 1 > r) {
                        upd(dp[l + 1][r][u][d], act + get_sum(max(d + 1, ex - u), ey - l - 1,
                                                              min(n - u, ex + d), ey - l - 1));
                    }

                    // go up
                    if (ex - u - 1 > d) {
                        upd(dp[l][r][u + 1][d], act + get_sum(ex - u - 1, max(r + 1, ey - l),
                                                              ex - u - 1, min(m - l, ey + r)));
                    }

                    // go down
                    if (ex + d + 1 <= n - u) {
                        upd(dp[l][r][u][d + 1], act + get_sum(ex + d + 1, max(r + 1, ey - l),
                                                              ex + d + 1, min(m - l, ey + r)));
                    }
                }
            }
        }
    }

    printf("%d", ans);


    return 0;
}

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

#define maxN 55

int t, ti;
int n, m, i, j, cnt;
char mat[maxN][maxN];
int sum[maxN][maxN];

ll ans, down;


int in_sq(int l1, int l2, int c1, int c2) {
    if (l1 > l2 || c1 > c2) return 0;
    return sum[l2][c2] - sum[l1 - 1][c2] - sum[l2][c1 - 1] + sum[l1 - 1][c1 - 1];
}

void solve() {
    int i1, i2, j1, j2;
    int i, j;

    int inside;
    int up, down, le, ri;
    int c1, c2, c3, c4;
    ll aux;

    //! mat of size 1x1
    ans = cnt;

    //! mat of size 1xl
    for (i = 1; i <= n; i++)
        for (j1 = 1; j1 <= m; j1++)
            for (j2 = j1 + 1; j2 <= m; j2++)
                if (mat[i][j1] == '1' && mat[i][j2] == '1')
                    ans += 1LL * (j2 - j1 + 1) * (1LL << in_sq(i, i, j1 + 1, j2 - 1));

    //! mat of size lx1
    for (i1 = 1; i1 <= n; i1++)
        for (i2 = i1 + 1; i2 <= n; i2++)
            for (j = 1; j <= m; j++)
                if (mat[i1][j] == '1' && mat[i2][j] == '1')
                    ans += 1LL * (i2 - i1 + 1) * (1LL << in_sq(i1 + 1, i2 - 1, j, j));

    //! mat of size lxr
    for (i1 = 1; i1 <= n; i1++) {
        for (i2 = i1 + 1; i2 <= n; i2++) {
            for (j1 = 1; j1 <= m; j1++) {
                for (j2 = j1 + 1; j2 <= m; j2++) {
                    inside = in_sq(i1 + 1, i2 - 1, j1 + 1, j2 - 1);
                    up = in_sq(i1, i1, j1 + 1, j2 - 1);
                    down = in_sq(i2, i2, j1 + 1, j2 - 1);
                    le = in_sq(i1 + 1, i2 - 1, j1, j1);
                    ri = in_sq(i1 + 1, i2 - 1, j2, j2);

                    for (c1 = 0; c1 <= mat[i1][j1] - '0'; c1++) {
                        for (c2 = 0; c2 <= mat[i1][j2] - '0'; c2++) {
                            for (c3 = 0; c3 <= mat[i2][j2] - '0'; c3++) {
                                for (c4 = 0; c4 <= mat[i2][j1] - '0'; c4++) {
                                    aux = 1;
                                    aux *= (1LL << up) - (c1 == 0 && c2 == 0);
                                    aux *= (1LL << ri) - (c2 == 0 && c3 == 0);
                                    aux *= (1LL << down) - (c3 == 0 && c4 == 0);
                                    aux *= (1LL << le) - (c4 == 0 && c1 == 0);

                                    ans += 1LL * (i2 - i1 + 1) * (j2 - j1 + 1) * aux * (1LL << inside);
                                }
                            }
                        }
                    }
                }
            }
        }
    }


}

int main()
{
    freopen("boundingbox.in","r",stdin);
    freopen("boundingbox.out","w",stdout);

    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++) {
        scanf("%d%d\n", &n, &m);
        for (i = 1; i <= n; i++) {
            scanf("%s\n", mat[i] + 1);
            for (j = 1; j <= m; j++)
                sum[i][j] = mat[i][j] - '0' + sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
        }

        cnt = sum[n][m];
        ans = 0; down = 1LL << cnt;
        solve();

        while ( (ans & 1) == 0 && (down & 1) == 0 ) ans >>= 1, down >>= 1;
        printf("%lld/%lld\n", ans, down);
    }


    return 0;
}

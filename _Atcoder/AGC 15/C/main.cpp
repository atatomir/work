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

#define maxN 2024
#define right cool

int n, m, q, i, j;
char mat[maxN][maxN];
int down[maxN][maxN], right[maxN][maxN], sum[maxN][maxN];
int x, y, xx, yy;

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d%d\n", &n, &m, &q);
    for (i = 1; i <= n; i++) scanf("%s\n", mat[i] + 1);

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            sum[i][j] = (mat[i][j] == '1' ? 1 : 0);
            down[i][j] = (sum[i][j] && mat[i + 1][j] == '1' ? 1 : 0);
            right[i][j] = (sum[i][j] && mat[i][j + 1] == '1' ? 1 : 0);

            sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
            down[i][j] += down[i - 1][j] + down[i][j - 1] - down[i - 1][j - 1];
            right[i][j] += right[i - 1][j] + right[i][j - 1] - right[i - 1][j - 1];
        }
    }

    for (i = 1; i <= q; i++) {
        scanf("%d%d%d%d", &x, &y, &xx, &yy);
        int ans = sum[xx][yy] - sum[x - 1][yy] - sum[xx][y - 1] + sum[x - 1][y - 1];
        ans -= down[xx - 1][yy] - down[x - 1][yy] - down[xx - 1][y - 1] + down[x - 1][y - 1];
        ans -= right[xx][yy - 1] - right[x - 1][yy - 1] - right[xx][y - 1] + right[x - 1][y - 1];

        printf("%d\n", ans);
    }


    return 0;
}

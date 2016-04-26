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

#define maxN 177

int n, m, i, j, x, y, k;
int roy[maxN][maxN];
int ans = maxN;




int main()
{
    freopen("apdm.in","r",stdin);
    freopen("apdm.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            if (i != j)
                roy[i][j] = maxN;

    for (i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        roy[x][y] = roy[y][x] = 1;
    }

    for (k = 1; k <= n; k++)
        for (i = 1; i <= n; i++)
            for (j = 1; j <= n; j++)
                if (i != j)
                    roy[i][j] = min(roy[i][j], roy[i][k] + roy[k][j]);

    for (i = 1; i <= n; i++) {
        for (j = i; j <= n; j++) {
            if (roy[i][j] > 1) continue;

            int tmp = 0;
            for (k = 1; k <= n; k++)
                tmp = max(tmp, min(roy[i][k], roy[k][j]));

            ans = min(ans, 2 * tmp + (i != j));
        }
    }

    printf("%d", ans);




    return 0;
}

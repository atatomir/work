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

#define maxN 33

int n, i, j, lvl;
int pct[maxN][maxN][maxN], id[maxN][maxN][maxN], cnt;
int dp[maxN][maxN][maxN];

void get_way(int lvl, int i, int j) {
    printf("%d ", id[lvl][i][j]);
    if (lvl == n) exit(0);

    int need = dp[lvl][i][j] - pct[lvl][i][j];

    if (dp[lvl + 1][i][j + 1] == need)
        get_way(lvl + 1, i, j + 1);

    if (dp[lvl + 1][i + 1][j] == need)
        get_way(lvl + 1, i + 1, j);

    if (dp[lvl + 1][i + 1][j + 1] == need)
        get_way(lvl + 1, i + 1, j + 1);
}

int main()
{
    freopen("drum2.in","r",stdin);
    freopen("drum2.out","w",stdout);

    scanf("%d", &n);
    for (lvl = 1; lvl <= n; lvl++)
        for (i = 1; i <= lvl; i++)
            for (j = 1; j <= lvl; j++)
                scanf("%d", &pct[lvl][i][j]), id[lvl][i][j] = ++cnt;

    memcpy(dp[n], pct[n], sizeof(pct[n]));
    for (lvl = n - 1; lvl > 0; lvl--) {
        for (i = 1; i <= lvl; i++) {
            for (j = 1; j <= lvl; j++) {
                dp[lvl][i][j] = max(max(dp[lvl + 1][i + 1][j], dp[lvl + 1][i][j + 1]), dp[lvl + 1][i + 1][j + 1]);
                dp[lvl][i][j] += pct[lvl][i][j];
            }
        }
    }

    printf("%d\n", dp[1][1][1]);
    get_way(1, 1, 1);


    return 0;
}

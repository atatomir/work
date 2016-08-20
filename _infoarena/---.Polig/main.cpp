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

#define maxN 111
#define inf (1 << 30)

struct Point {
    int x, y;
    int c;

    bool operator<(const Point& who)const  {
        return x * who.y - y * who.x > 0;
    }
};

int n, i, j, k;
Point P[maxN];
int dp[maxN][maxN];

bool good(int a, int b, int c) {
    return (P[b].x - P[a].x) * (P[c].y - P[a].y) - (P[b].y - P[a].y) * (P[c].x - P[a].x) > 0;
}

int main()
{
    freopen("polig.in","r",stdin);
    freopen("polig.out","w",stdout);

    scanf("%d", &n);
    n += 2;

    for (i = 2; i < n; i++)
        scanf("%d%d%d", &P[i].x, &P[i].y, &P[i].c);

    sort(P + 2, P + n);

    for (i = 2; i <= n; i++) {
        dp[i][1] = P[i].c;
        for (j = 2; j <= i; j++) {
            dp[i][j] = -inf;
            for (k = 1; k < j; k++)
                if (dp[j][k] >= 0)
                    if (good(k, j, i))
                        dp[i][j] = max(dp[i][j], dp[j][k] + P[i].c);
        }
    }

    int ans = 0;
    for (i = 2; i < n; i++)
        ans = max(ans, dp[n][i]);

    printf("%d", ans);

    return 0;
}

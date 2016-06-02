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
#define inf 1000000
#define state dp[xlow][xhigh][ylow]

int n, m, i, j, k, A;
pair<int, int> P[maxN];
int yy[maxN];

int dp[maxN][maxN][maxN]; //! x-low, x-high, y-low

int compute(int xlow, int xhigh, int ylow) {
    int i;
    int xx1, xx2;

    if (state != inf)
        return state;

    xx1 = xlow; xx2 = xhigh;
    while (xx1 <= xx2 && P[xx1].second < yy[ylow]) xx1++;
    while (xx1 <= xx2 && P[xx2].second < yy[ylow]) xx2--;

    if (xx1 > xx2)
        return state = 0;

    for (i = xx1; i < xx2; i++)
        state = min(state, compute(xx1, i, ylow) + compute(i + 1, xx2, ylow));

    if (P[xx1].first == P[xx2].first) return state = 1;

    int new_lim = A / (P[xx2].first - P[xx1].first);
    if (new_lim >= yy[ylow]) {
        if (new_lim >= yy[n]) return state = 1;

        int pos = upper_bound(yy + 1, yy + n + 1, new_lim) - yy;
        return state = min(state, 1 + compute(xx1, xx2, pos));
    }

    return state;
}

int main()
{
    freopen("photo.in","r",stdin);
    freopen("photo.out","w",stdout);

    scanf("%d%d", &n, &A);
    for (i = 1; i <= n; i++) {
        scanf("%d%d", &P[i].first, &P[i].second);
        yy[i] = P[i].second;
    }

    sort(P + 1, P + n + 1);
    sort(yy + 1, yy + n + 1);

    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            for (k = 1; k <= n; k++)
                dp[i][j][k] = inf;

    printf("%d", compute(1, n, 1));

    return 0;
}

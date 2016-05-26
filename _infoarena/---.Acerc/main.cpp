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

#define maxN 311
#define eps 0.0000001
#define inf 1e30

const double PI = acos(-1);

int n, i, j;
pair<double, double> P[maxN];
double dp[maxN];
double cost[maxN][maxN];

int g_st, g_en;

double dist(double x1, double y1, double x2, double y2) {
    x1 -= x2;
    y1 -= y2;
    return sqrt(x1 * x1 + y1 * y1);
}

void add_circle(double O, double R) {
    int l, r;

    if (R < 0) R = -R;

    l = 0;
    r = n + 1;

    for (i = 1; i <= n; i++) {
        if (dist(O, 0, P[i].first, P[i].second) <= R + eps) continue;

        if (P[i].first <= O + eps)
            l = max(l, i);

        if (P[i].first >= O - eps)
            r = min(r, i);
    }

    l++; r--;
    cost[l][r] = min(cost[l][r], PI * R * R);
}

void precomp() {
    int i, j;
    double y1, y2, x, O, R;

    for (i = 0; i <= n + 1; i++)
        for (j = 0; j <= n + 1; j++)
            cost[i][j] = inf;

    for (i = 1; i <= n; i++)
        add_circle(P[i].first, P[i].second);

    for (i = 1; i <= n; i++) {
        y1 = P[i].second;

        for (j = i + 1; j <= n; j++) {
            y2 = P[j].second;
            x = P[j].first - P[i].first;

            if (x == 0)
                O = 0;
            else
                O = (x * x - y1 * y1 + y2 * y2) / (2 * x);

            O += P[i].first;
            R = max( y1 * y1 + (O - P[i].first) * (O - P[i].first),  y2 * y2 + (O - P[j].first) * (O - P[j].first));
            R = sqrt(R);

            add_circle(O, R);
        }
    }


    for (i = 1; i <= n; i++)
        for (j = n; j >= i; j--)
            cost[i][j] = min(cost[i][j], min(cost[i - 1][j], cost[i][j + 1]));
}


int main()
{
    freopen("acerc.in","r",stdin);
    freopen("acerc.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) scanf("%lf%lf", &P[i].first, &P[i].second);
    sort(P + 1, P + n + 1);

    precomp();

    for (j = 1; j <= n; j++) {
        dp[j] = inf;

        for (i = 1; i <= j; i++)
            dp[j] = min(dp[j], dp[i - 1] + cost[i][j]);
    }

    printf("%.4lf", dp[n]);


    return 0;
}

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

const int maxN = 2018;

int n, a, b, i;
double p[maxN], u[maxN];
pair<double, int> dp[maxN][maxN];

int check(double cost) {
    int i, j;

    memset(dp, 0, sizeof(dp));
    for (i = 0; i < n; i++) {
        for (j = 0; j <= i; j++) {
            dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
            dp[i + 1][j + 1] = max(dp[i + 1][j + 1], mp(dp[i][j].first + p[i + 1], dp[i][j].second));
            dp[i + 1][j] = max(dp[i + 1][j], mp(dp[i][j].first + u[i + 1] - cost, dp[i][j].second + 1));
            dp[i + 1][j + 1] = max(dp[i + 1][j + 1], mp(dp[i][j].first + 1.00 - (1.00 - p[i + 1]) * (1.00 - u[i + 1]) - cost, dp[i][j].second + 1));
        }
    }

    return dp[n][a].second;
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d%d%d", &n, &a, &b);
    for (i = 1; i <= n; i++) scanf("%lf", &p[i]);
    for (i = 1; i <= n; i++) scanf("%lf", &u[i]);

    double lo = 0.00;
    double hi = 1.00;

    for (int iter = 1; iter <= 60; iter++) {
        double mid = (lo + hi) / 2.00;

        if (check(mid) >= b)
            lo = mid;
        else
            hi = mid;
    }

    double mid = (lo + hi) / 2.00;
    check(mid);
    printf("%.10lf", dp[n][a].first + mid * b);


    return 0;
}

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 3016

int t, test;
int n, k, i;
double p, non_p;

double chance[maxN][maxN];
double good[maxN];
double dp[maxN];

void compute_good() {
    int i, j;

    chance[0][0] = 1.00;
    for (i = 1; i <= n; i++) {
        chance[i][0] = chance[i - 1][0] * non_p;

        for (j = 1; j <= n; j++) {
            chance[i][j] = chance[i - 1][j] * non_p + chance[i - 1][j - 1] * p;
            if (j >= k)
                good[i] += chance[i][j];
        }
    }
}

void compute_dp() {
    int i, j;

    dp[0] = 0.00;
    for (i = 1; i <= n; i++)
        for (j = 0; j < i; j++)
            dp[i] = max(dp[i], dp[j] + good[i - j]);
}

int main()
{
    freopen("input.in","r",stdin);
    freopen("output.out","w",stdout);

    scanf("%d", &t);
    for (test = 1; test <= t; test++) {
        cerr << "S" << test << '\n';

        scanf("%d %d %lf", &n, &k, &p);
        non_p = 1 - p;

        memset(chance, 0, sizeof(chance));
        memset(good, 0, sizeof(good));
        memset(dp, 0, sizeof(dp));

        compute_good();
        compute_dp();

        printf("Case #%d: %.9lf\n", test, dp[n]);
    }



    return 0;
}

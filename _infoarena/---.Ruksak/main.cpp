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

#define maxN 3015

int n, G, i, j, x, y, dim;
vector<int> P[maxN];
int ans;

int ss, dd;
int dp[2][maxN];

bool cmp(int a, int b) { return a > b; }

void compute(int g, int p) {
    static int i;

    for (i = 0; i + g <= G; i++)
        dp[dd][i + g] = max(dp[ss][i + g], dp[ss][i] + p);
    swap(ss, dd);
}

int main()
{
    freopen("ruksak.in","r",stdin);
    freopen("ruksak.out","w",stdout);

    scanf("%d%d", &n, &G);
    for (i = 1; i <= n; i++) {
        scanf("%d%d", &x, &y);
        P[x].pb(y);

        if (x == 0) ans += y;
    }

    ss = 0;
    dd = 1;

    for (i = 1; i < maxN; i++) {
        //! remove unuseful objects
        sort(P[i].begin(), P[i].end(), cmp);

        dim = min((int)P[i].size(), G / i);
        for (j = 0; j < dim; j++)
            compute(i, P[i][j]);
    }

    printf("%d", ans + dp[ss][G]);


    return 0;
}

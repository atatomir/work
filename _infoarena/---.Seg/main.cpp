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

#define maxN 17
#define inf 1e50

struct Point {
    double x, y;

    void read() {
        scanf("%lf%lf", &x, &y);
    }

    double dist(const Point& A) {
        return sqrt((x - A.x) * (x - A.x) + (y - A.y) * (y - A.y));
    }
};

int t, ti;
int n, i, j, k, st;
Point P[maxN][2];
double dp[1 << (maxN - 1)][maxN][2];

double pre[maxN][2][maxN][2];




void comp_pre() {
    for (int n1 = 0; n1 < n; n1++)
        for (int k1 = 0; k1 < 2; k1++)
            for (int n2 = 0; n2 < n; n2++)
                for (int k2 = 0; k2 < 2; k2++)
                    pre[n1][k1][n2][k2] = P[n1][k1].dist(P[n2][k2]);
}

void upd(double& dest, double sour) {
    dest = min(dest, sour);
}



int main()
{
    freopen("seg.in","r",stdin);
    freopen("seg.out","w",stdout);

    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++) {
        scanf("%d", &n);
        for (i = 0; i < n; i++) {
            P[i][0].read();
            P[i][1].read();
        }

        comp_pre();

        st = (1 << (n - 1));
        for (i = 0; i < st; i++)
            for (j = 0; j < n; j++)
                dp[i][j][0] = dp[i][j][1] = inf;

        dp[0][0][0] = 0.00;

        for (i = 0; i + 1 < st; i++) {
            for (j = 0; j < n; j++) {
                if (j != 0)
                    if (((i >> (j - 1)) & 1) == 0) continue;

                for (k = 0; k < 2; k++) {

                    for (int to = 1; to < n; to++) {
                        if (((i >> (to - 1)) & 1) != 0) continue;

                        upd(dp[i | (1 << (to - 1))][to][0], dp[i][j][k] + pre[j][k][to][1]);
                        upd(dp[i | (1 << (to - 1))][to][1], dp[i][j][k] + pre[j][k][to][0]);
                    }

                }
            }
        }

        double ans = inf;

        st--;
        for (i = 1; i < n; i++) {
            ans = min(ans, dp[st][i][0] + pre[i][0][0][1]);
            ans = min(ans, dp[st][i][1] + pre[i][1][0][1]);
        }

        printf("%.6lf\n", ans);
    }

    return 0;
}

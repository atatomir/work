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

const int grid = 1201;

#define maxN 222
#define inf 1000000000

int n, k, i, j, x, y;
vector<int> xx, yy;

int ss, dd;
int dp[2][2 * grid + 10][maxN];

inline int abss(int x) {
    if (x < 0) return -x;
    return x;
}

inline void set_inf(int id) {
    static int i, j;

    for (i = 0; i <= 2 * grid + 3; i++)
        for (j = 0; j <= n + 3; j++)
            dp[id][i][j] = inf;
}

int solve(vector<int> pos) {
    int i, j, cnt;

    sort(pos.begin(), pos.end());

    ss = 0; dd = 1;
    set_inf(0); set_inf(1);
    dp[ss][0][0] = 0;

    int ans = inf;

    for (cnt = 0; cnt <= n; cnt++) {
        set_inf(dd);

        for (i = 0; i <= 2 * grid + 1; i++) {
            //if (i == 1201)
            //    cerr << 'd';

            for (j = 0; j <= n; j++) {
                if (dp[ss][i][j] >= inf) continue;

                if (i <= 2 * grid && j < n)
                    dp[dd][i + 1][j + 1] = min(dp[dd][i + 1][j + 1], dp[ss][i][j] + abss(i - pos[j]));
                dp[ss][i + 1][j] = min(dp[ss][i + 1][j], dp[ss][i][j]);
                dp[ss][i][j + 1] = min(dp[ss][i][j + 1], dp[ss][i][j]);
            }
        }

        if (cnt >= k)
            ans = min(ans, dp[ss][2 * grid + 1][n]);

        swap(ss, dd);
    }

    return ans;

}

int main()
{
    freopen("naveplanare.in","r",stdin);
    freopen("naveplanare.out","w",stdout);

    scanf("%d%d", &n, &k);
    for (i = 1; i <= n; i++)  {
        scanf("%d%d", &x, &y);
        xx.pb(x + grid);
        yy.pb(y + grid);
    }

    int sol = solve(xx) + solve(yy);
    printf("%d", sol);


    return 0;
}

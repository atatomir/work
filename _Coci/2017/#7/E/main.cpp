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

#define maxN 511

const int inf = 1000000007;

int n, m, i, x, y;
int need[maxN];
vector<int> list[maxN];
int dp[maxN][maxN][2], down[maxN];
int aux[maxN][2];

void upd(int& a, int b) {
    if (b > a) a = b;
}

void dfs(int node, int root) {
    int i, j, l1, l2;

    down[node] = 1;
    for (i = 0; i < list[node].size(); i++) {
        int to = list[node][i];

        if (to == root) {
            list[node][i] = list[node].back();
            list[node].pop_back();
            i--; continue;
        }

        dfs(to, node);
    }

    for (i = 0; i <= n; i++) dp[node][i][0] = dp[node][i][1] = -inf;
    dp[node][0][0] = dp[node][0][1] = 0;
    dp[node][1][0] = dp[node][1][1] = need[node];

    for (auto to : list[node]) {
        l1 = min(m, 3 * down[node]);
        l2 = min(m, 3 * down[to]);

        for (i = 0; i <= l1; i++) {
            aux[i][0] = dp[node][i][0];
            aux[i][1] = dp[node][i][1];
        }

        for (i = 0; i <= l1; i++) {
            for (j = 0; j <= l2 && i + j <= m; j++) {
                upd(dp[node][i + j + 2][0], aux[i][0] + dp[to][j][0]);
                upd(dp[node][i + j + 2][1], aux[i][1] + dp[to][j][0]);
                upd(dp[node][i + j + 1][1], aux[i][0] + dp[to][j][1]);
            }
        }

        down[node] += down[to];
    }
}

int main()
{
    //freopen("test.in","r",stdin);

    cin >> n >> m;
    for (i = 1; i <= n; i++) cin >> need[i];
    for (i = 1; i < n; i++) {
        cin >> x >> y;
        list[x].pb(y);
        list[y].pb(x);
    }

    dfs(1, 0);

    int ans = 0;
    for (i = 0; i <= m; i++) {
        upd(ans, dp[1][i][0]);
        upd(ans, dp[1][i][1]);
    }

    cout << ans;


    return 0;
}

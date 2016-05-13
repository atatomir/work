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

#define maxN 77
#define inf 77011

int n, i, j, x, y, c, k, m;
vector< pair<int, int> > list[maxN];
int dp[maxN][maxN][maxN]; //! dp[node][accesible][destroyed]
bool us[maxN];

int aux[maxN][maxN];
int nothing[maxN][maxN];

int cnt[maxN];


void solve(int node) {
    int i, j, ii, jj;

    us[node] = true; cnt[node] = 1;
    for (i = 0; i < list[node].size(); i++) {
        int to = list[node][i].first;

        if (us[to]) {
            list[node][i] = list[node].back();
            list[node].pop_back();
            i--; continue;
        }

        solve(to);
        cnt[node] += cnt[to];
    }

    //! clean all
    memcpy(dp[node], nothing, sizeof(nothing));

    if (list[node].empty()) {
        //! leaf
        dp[node][1][0] = 0;

        return;
    }

    //! add first son
    int son = list[node][0].first;
    int add_cost = list[node][0].second;

    list[node][0] = list[node].back();
    list[node].pop_back();

    for (i = 1; i < cnt[node]; i++) /* dont destroy edge node-son */
        for (j = 0; j < cnt[node]; j++)
            dp[node][i + 1][j] = dp[son][i][j];

    for (i = 1; i < cnt[node]; i++) /* Miruna is so evil... she destroyed the edge node-son*/
        for (j = 0; j + 1 < cnt[node]; j++)
            dp[node][1][j + 1] = min(dp[node][1][j + 1], dp[son][i][j] + add_cost);

    //! add another sons
    for (auto act : list[node]) {
        son = act.first;
        add_cost = act.second;

        for (i = 1; i <= cnt[node]; i++)
            for (j = 0; j < cnt[node]; j++)
                aux[i][j] = inf;

        /* dont destroy edge node-son */
        for (i = 1; i <= cnt[node]; i++)
            for (j = 0; j < cnt[node]; j++)
                if (dp[node][i][j] < inf)
                    for (ii = 1; i + ii <= cnt[node] && ii <= cnt[son]; ii++)
                        for (jj = 0; j + jj < cnt[node] && jj < cnt[son]; jj++)
                            aux[i + ii][j + jj] = min(aux[i + ii][j + jj], dp[node][i][j] + dp[son][ii][jj]);

        /* Miruna is so evil... she destroyed the edge node-son*/
        for (i = 1; i <= cnt[node]; i++)
            for (j = 0; j < cnt[node]; j++)
                if (dp[node][i][j] < inf)
                    for (ii = 1; i + ii <= cnt[node] && ii <= cnt[son]; ii++)
                        for (jj = 0; j + jj + 1 < cnt[node] && jj < cnt[son]; jj++)
                            aux[i][j + jj + 1] = min(aux[i][j + jj + 1], dp[node][i][j] + dp[son][ii][jj] + add_cost);

        /* copy aux to dp[node] */
        for (i = 1; i <= cnt[node]; i++)
            for (j = 0; j < cnt[node]; j++)
                dp[node][i][j] = aux[i][j];

    }
}


int main()
{
    freopen("ktree.in","r",stdin);
    freopen("ktree.out","w",stdout);

    scanf("%d%d%d", &n, &m, &k);
    for (i = 1; i < n; i++) {
        scanf("%d%d%d", &x, &y, &c);
        list[x].pb(mp(y, c));
        list[y].pb(mp(x, c));
    }

    for (i = 1; i <= n; i++)
        for (j = 0; j < n; j++)
            nothing[i][j] = inf;

    solve(1);

    cerr << dp[1][k][m];
    printf("%d", dp[1][k][m]);


    return 0;
}

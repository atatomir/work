#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 301
#define maxK 201


int n, m, k, i, x, y, c, k1, k2;
vector< pair<int, int> > list[maxN];
int dim[maxN], rez[maxN];
int gr[maxN];

queue<int> Q;
vector< vector<int> > dp[maxN];
int ans = -1;

void set_dims() {
    memcpy(rez, gr, sizeof(rez));
    for (i = 1; i <= n; i++)
        if (rez[i] == 0)
            Q.push(i), dim[i] = 1;

    while (!Q.empty()) {
        int node = Q.front();
        Q.pop();

        dp[node] = vector< vector<int> >(dim[node] + 1, vector<int>(dim[node] + 1, 0));

        for (auto to : list[node]) {
            dim[to.first] = max(dim[node] + 1, dim[to.first]);
            if (--rez[to.first] == 0)
                Q.push(to.first);
        }
    }

}

void upd(int& d, int s) {
    if (d == 0)
        d = s;
    else
        d = max(s, d);
}

int main()
{
    freopen("kgraf.in","r",stdin);
    freopen("kgraf.out","w",stdout);

    scanf("%d%d%d", &n, &m, &k);
    for (i = 1; i <= m; i++) {
        scanf("%d%d%d", &x, &y, &c);
        list[x].pb(mp(y, c));
        gr[y]++;
    }

    set_dims();

    for (i = 1; i <= n; i++)
        if (gr[i] == 0)
            dp[i][0][0] = 1, Q.push(i);

    while (!Q.empty()) {
        int node = Q.front(); Q.pop();

        if (dim[node] >= k)
            if (dp[node][k][k] != 0)
                ans = max(dp[node][k][k] - 1, ans);

        for (auto to : list[node]) {
            if (--gr[to.first] == 0)
                Q.push(to.first);

            int lim = min(k, dim[node]);
            for (k1 = 0; k1 <= lim; k1++) {
                for (k2 = 0; k2 <= lim; k2++) {
                    if (dp[node][k1][k2] == 0) continue;
                    upd(dp[to.first][k1][k2], dp[node][k1][k2]);

                    if (k1 < k)
                        upd(dp[to.first][k1 + 1][k2], dp[node][k1][k2] - to.second);
                    if (k2 < k)
                        upd(dp[to.first][k1][k2 + 1], dp[node][k1][k2] + to.second);

                    if (k1 < k && k2 < k)
                        upd(dp[to.first][k1 + 1][k2 + 1], dp[node][k1][k2]);

                }
            }
        }

    }


    printf("%d", ans);

    return 0;
}

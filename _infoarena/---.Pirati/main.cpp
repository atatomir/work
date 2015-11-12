#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <unordered_map>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 1024
#define maxNodes (maxN * maxN) / 4
#define mod 666013

const int defX[8] = {1, 0, 1, 1, -1, 0, -1, -1};
const int defY[8] = {0, 1, 1, -1, 0, -1, -1, 1};

int n, m, i, j, q, xx1, xx2, yy1, yy2;
char s[maxN][maxN];
int id[maxN][maxN];
int dim;

char target;
vector<int> list[maxNodes];
bool us[maxNodes];
int dad[maxNodes];
int lvl[maxNodes];
queue< pair<int, int> > Q;

struct myhash {
    size_t operator()(const pair<int, int> who)const {
        return (who.first * 17 + who.second) % mod;
    }
};

unordered_map< pair<int, int>, bool, myhash> H;

void bfs(int x, int y) {
    while (!Q.empty()) Q.pop();

    Q.push(mp(x, y));
    id[x][y] = dim;

    while (!Q.empty()) {
        auto act = Q.front(); Q.pop();

        for (int i = 0; i < 8; i++) {
            int xx = act.first + defX[i];
            int yy = act.second + defY[i];

            if (s[xx][yy] == target && id[xx][yy] == 0) {
                id[xx][yy] = dim;
                Q.push(mp(xx, yy));
            }
            else
            if (id[xx][yy] != dim && id[xx][yy] != 0) {
                auto aux = mp(dim, id[xx][yy]);
                if (H[aux] == false) {
                    H[aux] = true;
                    H[mp(id[xx][yy], dim)] = true;

                    list[dim].pb(id[xx][yy]);
                    list[id[xx][yy]].pb(dim);
                }
            }
        }
    }
}

void dfs(int node) {
    us[node] = true;

    for (auto to : list[node]) {
        if (us[to]) continue;

        dad[to] = node;
        lvl[to] = lvl[node] + 1;
        dfs(to);
    }
}

int main()
{
    freopen("pirati.in","r",stdin);
    freopen("pirati.out","w",stdout);

    scanf("%d%d%d\n", &n, &m, &q);
    for (i = 1; i <= n; i++) {
        scanf("%s\n", s[i] + 1);
        s[i][0] = s[i][m + 1] = '@';
    }
    for (i = 0; i <= m + 1; i++) s[0][i] = s[n + 1][i] = '@';

    H.clear();
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            if (id[i][j] != 0) continue;

            dim++;
            target = s[i][j];
            bfs(i, j);
        }
    }

    dfs(1);
    for (i = 1; i <= q; i++) {
        scanf("%d%d%d%d", &xx1, &yy1, &xx2, &yy2);

        int id1 = id[xx1][yy1];
        int id2 = id[xx2][yy2];

        int ans = 1;

        if (lvl[id1] > lvl[id2]) swap(id1, id2);
        while (lvl[id2] != lvl[id1]) {
            ans++;
            id2 = dad[id2];
        }

        while (id1 != id2) {
            ans += 2;
            id1 = dad[id1];
            id2 = dad[id2];
        }

        printf("%d\n", ans / 2);
    }

    return 0;
}

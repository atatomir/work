#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stack>
#include <queue>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 1502
#define maxLog 23

const int defX[4] = {-1, 1, 0, 0};
const int defY[4] = {0, 0, -1, 1};

int n, m, q, i, j, groups, ax, ay, bx, by, x, y, xi[50011], yi[50011];
bool ans[50011];
char mat[maxN][maxN];
int id[maxN][maxN];
vector<int> list[maxN * maxN];
int lvl[maxN * maxN];
int low[maxN * maxN];
stack< pair<int, int> > S;
vector<int> wh[maxN * maxN];
int dad[maxLog][maxN * maxN];
int connex_group[maxN * maxN], connex_id;

bool win[maxN][maxN];
bool reach[maxN][maxN][4];
queue< pair<int, int> > Q, Q2;

//bool us[maxN][maxN];
bool rez[maxN][maxN];


void extract_group(int n1, int n2) {
    bool frs = true;

    groups++;

    while (!S.empty()) {
        auto act = S.top(); S.pop();
        wh[act.first].pb(groups);
        //if (frs) {
            wh[act.second].pb(groups);
            //frs = false;
        //}
        if (act == mp(n1, n2)) break;
    }
}

void dfs(int node) {
    low[node] = lvl[node] + 1;
    connex_group[node] = connex_id;
    for (auto to : list[node]) {
        if (lvl[to] == 0) {
            S.push(mp(node, to));
            lvl[to] = lvl[node] + 1;
            dad[0][to] = node;
            dfs(to);
            low[node] = min(low[node], low[to]);

            if (low[to] >= lvl[node])
                extract_group(node, to);

        } else {
            if (lvl[to] >= lvl[node] - 1) continue;
            low[node] = min(low[node], lvl[to]);
        }
    }
}

int go_up(int x, int cnt) {
    for (int i = 0; cnt > 0; i++, cnt >>= 1)
        if (cnt & 1)
            x = dad[i][x];
    return x;
}

int get_lca(int x, int y) {
    if (lvl[x] < lvl[y]) swap(x, y);
    x = go_up(x, lvl[x] - lvl[y]);
    if (x == y) return x;

    for (int i = maxLog - 1; i >= 0; i--)
        if (dad[i][x] != dad[i][y])
            x = dad[i][x], y = dad[i][y];

    return dad[0][x];
}

bool common(vector<int>& a, vector<int>& b) {
    for (auto e1 : a)
        for (auto e2 : b)
            if (e1 == e2)
                return true;
    return false;
}

/*void brute(int x, int y) {
    us[x][y] = true;
    for (int i = 0; i < 4; i++) {
        int xx = x + defX[i];
        int yy = y + defY[i];

        if (us[xx][yy] || mat[xx][yy] == '#') continue;
        brute(xx, yy);
    }
}*/

bool good_way(int x, int y, int xx, int yy, int dx, int dy) {
    int id1 = id[x][y];
    int id2 = id[xx][yy];
    int id_deny = id[dx][dy];

    if (id1 == id2) return true;

    /*memset(us, 0, sizeof(us));
    char bef = mat[dx][dy];
    mat[dx][dy] = '#';
    brute(x, y);
    mat[dx][dy] = bef;
    return us[xx][yy];
    */
    //! ------------------------------------------------------------------------------

    if (common(wh[id1], wh[id2])) return true;

    int lca = get_lca(id1, id2);
    //if (lca == 0) exit(-1);
    if (lvl[id1] + lvl[id2] - 2 * lvl[lca] + 1 == 2) return true;

    if (lvl[lca] <= lvl[id_deny] && lvl[id_deny] <= lvl[id1]) {
        int aux = go_up(id1, lvl[id1] - lvl[id_deny]);
        if (aux == id_deny) {
            //return false;

            int prev = go_up(id1, lvl[id1] - lvl[id_deny] - 1);
            int nxt = dad[0][id_deny];
            if (id_deny == lca) nxt = go_up(id2, lvl[id2] - lvl[id_deny] - 1);
            if (common(wh[prev], wh[nxt]) == false) return false;
        }
    }
    if (lvl[lca] <= lvl[id_deny] && lvl[id_deny] <= lvl[id2]) {
        int aux = go_up(id2, lvl[id2] - lvl[id_deny]);
        if (aux == id_deny) {
            //return false;

            int prev = go_up(id2, lvl[id2] - lvl[id_deny] - 1);
            int nxt = dad[0][id_deny];
            if (id_deny == lca) nxt = go_up(id1, lvl[id1] - lvl[id_deny] - 1);
            if (common(wh[prev], wh[nxt]) == false) return false;
        }
    }

    return true;
}

void run() {
    int i, px, py;

    while (!Q.empty()) {
        int x = Q.front().first;
        int y = Q.front().second >> 2;
        int dir = Q.front().second & 3;
        Q.pop();
        win[x][y] = true;

        for (i = 0; i < 4; i++) {
            int xx = x + defX[i];
            int yy = y + defY[i];

            if (reach[xx][yy][i]) continue;
            if (mat[xx][yy] == '#') continue;

            px = x - defX[i];
            py = y - defY[i];

            if (mat[px][py] == '#') continue;
            if (connex_group[id[x - defX[dir]][y - defY[dir]]] != connex_group[id[px][py]]) continue;

            if (good_way(x - defX[dir], y - defY[dir], px, py, x, y)) {
                reach[xx][yy][i] = true;
                Q.push(mp(xx, yy * 4 + i));
            }
        }
    }
}

int main()
{
    freopen("pushabox.in","r",stdin);
    freopen("pushabox.out","w",stdout);

    scanf("%d%d%d\n", &n, &m, &q);
    for (i = 1; i <= n; i++) {
        scanf("%s\n", mat[i] + 1);
        for (j = 1; j <= m; j++) {
            id[i][j] = (i - 1) * m + j;

            if (mat[i][j] == 'A') ax = i, ay = j;
            if (mat[i][j] == 'B') bx = i, by = j;
        }
    }

    for (i = 0; i <= n + 1; i++)
        mat[i][0] = mat[i][m + 1] = '#';
    for (i = 0; i <= m + 1; i++)
        mat[0][i] = mat[n + 1][i] = '#';

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            if (mat[i][j] == '#') continue;
            if (mat[i + 1][j] != '#') {
                list[id[i][j]].pb(id[i + 1][j]);
                list[id[i + 1][j]].pb(id[i][j]);
            }
            if (mat[i][j + 1] != '#') {
                list[id[i][j]].pb(id[i][j + 1]);
                list[id[i][j + 1]].pb(id[i][j]);
            }
        }
    }

    for (i = 1; i <= n * m; i++) {
        if (!lvl[i]) {
            connex_id++;
            lvl[i] = 1;
            dfs(i);
        }
    }

    for (i = 1; i < maxLog; i++)
        for (j = 1; j <= n * m; j++)
            dad[i][j] = dad[i - 1][dad[i - 1][j]];

    rez[ax][ay] = true;
    Q2.push(mp(ax, ay));

    while (!Q2.empty()) {
        int x = Q2.front().first;
        int y = Q2.front().second;
        Q2.pop();

        for (int i = 0; i < 4; i++) {
            int xx = x + defX[i];
            int yy = y + defY[i];

            if (mat[xx][yy] == '#') continue;
            if (mat[xx][yy] == 'B') continue;
            if (rez[xx][yy]) continue;
            rez[xx][yy] = true;
            Q2.push(mp(xx, yy));
        }
    }

    for (i = 1; i <= q; i++)
        scanf("%d%d", &xi[i], &yi[i]);

    for (i = 0; i < 4; i++) {
        int xx = bx - defX[i];
        int yy = by - defY[i];

        if (mat[xx][yy] == '#') continue;

        memset(reach, 0, sizeof(reach));
        while (!Q.empty()) Q.pop();
        reach[bx][by][i] = true;
        Q.push(mp(bx, by * 4 + i));

        memset(win, 0, sizeof(win));
        run();

        for (j = 1; j <= q; j++) {
            int xx = bx - defX[i];
            int yy = by - defY[i];

            if (mat[xx][yy] == '#') continue;
            if (rez[xx][yy] == false) continue;
            ans[j] |= win[xi[j]][yi[j]];
        }
    }


    for (i = 1; i <= q; i++) {
        if (xi[i] == bx && yi[i] == by)
            ans[i] = true;
        if (ans[i])
            printf("YES\n");
        else
            printf("NO\n");
    }


    return 0;
}

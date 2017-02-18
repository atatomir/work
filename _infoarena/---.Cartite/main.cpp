#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 222

const int defX[4] = {-1, 1, 0, 0};
const int defY[4] = {0, 0, -1, 1};

int op, n, m, i, j;
int xc, yc;
int k, g, x, y, xx, yy, tp;

int data[maxN][maxN];
queue< pair<int, int> > Q;
int id[maxN][maxN];

vector< pair<int, int> > ids;
vector< pair<int, int> > list[maxN];

bool dead[maxN];
stack<int> S;
vector<int> ord;


int abss(int x) {
    if (x < 0) return -x;
    return x;
}

void add_fox() {
    int i, j;

    for (i = max(1, x - tp); i <= min(n, x + tp); i++) {
        for (j = max(1, y - tp); j <= min(m, y + tp); j++) {
            if (abss(i - x) + abss(j - y) <= tp) {
                data[i][j] = -1;
            }
        }
    }
}

void euler(int node) {

    S.push(node);
    while (!S.empty()) {
        node = S.top();

        while (!list[node].empty()) {
            if (dead[list[node].back().second] == false) break;
            list[node].pop_back();
        }

        if (list[node].empty()) {
            ord.pb(node);
            S.pop();
            continue;
        }

        auto to = list[node].back();
        list[node].pop_back();

        dead[to.second] = true;
        S.push(to.first);
    }

}

int main()
{
    freopen("cartite.in","r",stdin);
    freopen("cartite.out","w",stdout);

    scanf("%d", &op);
    scanf("%d%d", &n, &m);
    scanf("%d%d", &xc, &yc);

    for (i = 0; i <= n + 1; i++)
        data[i][0] = data[i][m + 1] = -1;

    for (i = 0; i <= m + 1; i++)
        data[0][i] = data[n + 1][i] = -1;

    scanf("%d", &k);
    for (i = 1; i <= k; i++) {
        scanf("%d%d%d", &x, &y, &tp);
        add_fox();
    }

    scanf("%d", &g);
    for (i = 1; i <= g; i++) {
        scanf("%d%d%d%d", &x, &y, &xx, &yy);

        if (id[x][y] == 0) {
            id[x][y] = ids.size() + 1;
            ids.pb(mp(x, y));
        }

        swap(xx, x); swap(yy, y);

        if (id[x][y] == 0) {
            id[x][y] = ids.size() + 1;
            ids.pb(mp(x, y));
        }

        list[ id[x][y] ].pb( mp(id[xx][yy], i) );
        list[ id[xx][yy] ].pb( mp(id[x][y], i) );
    }

    data[xc][yc] = 1;
    Q.push(mp(xc, yc));

    while (!Q.empty()) {
        auto act = Q.front(); Q.pop();

        if (id[act.first][act.second]) {
            xc = act.first;
            yc = act.second;
            break;
        }

        for (i = 0; i < 4; i++) {
            int xx = act.first + defX[i];
            int yy = act.second + defY[i];

            if (data[xx][yy] == 0) {
                data[xx][yy] = data[act.first][act.second] + 1;
                Q.push(mp(xx, yy));
            }
        }
    }

    if (op == 1) {
        printf("%d %d %d", xc, yc, data[xc][yc] - 1);
        return 0;
    }

    euler(id[xc][yc]);
    for (auto e : ord)
        printf("%d %d\n", ids[e - 1].first, ids[e - 1].second);


    return 0;
}

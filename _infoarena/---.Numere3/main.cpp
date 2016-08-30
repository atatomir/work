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

#define maxN 15

const int defX[4] = {-1, 1, 0, 0};
const int defY[4] = {0, 0, -1, 1};

int n, m, k, i, j, x, y;
int tp[maxN][maxN], aux[maxN][maxN];
int ch[maxN][maxN];

bool on_edge[maxN][maxN];
bool deny[maxN][maxN];
bool sel[maxN][maxN];

int best = 100 * 100;
vector< pair<int, int> > sol, act;


void set_position(int x, int y) {
    static int i, xx, yy;

    for (i = 0; i < 4; i++) {
        xx = x + defX[i];
        yy = y + defY[i];

        aux[xx][yy] ^= 1;
    }

    if (on_edge[x][y])
        aux[x][y] ^= 1;
}

void try_target(int target) {
    int i;


    for (int conf = (1 << m) - 1; conf >= 0; conf--) {
        memset(sel, 0, sizeof(sel));
        memcpy(aux, tp, sizeof(aux));

        for (i = 0; i < m; i++) {
            if ( ((conf >> i) & 1) == 0 ) continue;
            sel[1][i + 1] = true;
            set_position(1, i + 1);
        }

        for (i = 2; i <= n; i++) {
            for (j = 1; j <= m; j++) {
                if (aux[i - 1][j] != target) {
                    sel[i][j] = true;
                    set_position(i, j);
                }
            }
        }


        bool ok = true;

        act.clear();
        for (i = 1; i <= n && ok; i++) {
            for (j = 1; j <= m && ok; j++) {
                if (sel[i][j] && deny[i][j]) ok = false;
                if (aux[i][j] != target) ok = false;
                if (sel[i][j]) act.pb(mp(i, j));
            }
        }

        if (ok && act.size() < best) {
            best = act.size();
            sol = act;
        }
    }

}

int main()
{
    freopen("numere3.in","r",stdin);
    freopen("numere3.out","w",stdout);

    scanf("%d%d%d", &n, &m, &k);
    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            scanf("%d", &tp[i][j]), tp[i][j] &= 1;

    for (i = 2; i < n; i++) on_edge[i][1] = on_edge[i][m] = true;
    for (i = 2; i < m; i++) on_edge[1][i] = on_edge[n][i] = true;

    for (i = 1; i <= k; i++) {
        scanf("%d%d", &x, &y);
        deny[x][y] = true;
    }

    try_target(0);
    try_target(1);

    if (best == 100 * 100) {
        printf("-1");
        return 0;
    }

    printf("%d\n", best);
    for (auto e : sol)
        printf("%d %d\n", e.first, e.second);


    return 0;
}

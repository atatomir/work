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

#define maxN 444

int defX[4] = {-1, 1, 0, 0};
int defY[4] = {0, 0, -1, 1};
int dead_place = maxN * maxN - 1;

int n, m, i, op, j, how, best;
char s[maxN][maxN];
int id[maxN][maxN];
int how_big[maxN * maxN];

int ans_x, ans_y;
char ans_col;

vector<int> aux;


void dfs(int x, int y) {
    id[x][y] = how;
    how_big[how]++;

    for (int i = 0; i < 4; i++) {
        int xx = x + defX[i];
        int yy = y + defY[i];

        if (s[xx][yy] == s[x][y] && id[xx][yy] == 0)
            dfs(xx, yy);
    }
}

void promote(int _x, int _y, char _c, int act) {
    ans_x = _x;
    ans_y = _y;
    ans_col = _c;

    best = act;
}

bool _try(int x, int y) {
    int i, j;
    int act;

    for (i = 0; i < 4; i++) {
        int xx = x + defX[i];
        int yy = y + defY[i];

        if (id[xx][yy] == id[x][y]) continue;
        aux.clear();

        for (j = 0; j < 4; j++) {
            int xxx = x + defX[j];
            int yyy = y + defY[j];

            if (s[xx][yy] == s[xxx][yyy]) aux.pb(id[xxx][yyy]);
        }

        sort(aux.begin(), aux.end());
        aux.resize(unique(aux.begin(), aux.end()) - aux.begin());

        act = 1;
        for (auto e : aux)
            act += how_big[e];

        if (act > best)
            promote(x, y, s[xx][yy], act);
    }

}

int main()
{
    freopen("ferma3.in","r",stdin);
    freopen("ferma3.out","w",stdout);

    scanf("%d%d%d\n", &op, &n, &m);
    for (i = 1; i <= n; i++)
        scanf("%s\n", s[i] + 1);

    for (i = 0; i <= n + 1; i++)
        id[i][0] = id[i][m + 1] = dead_place;
    for (i = 0; i <= m + 1; i++)
        id[0][i] = id[n + 1][i] = dead_place;

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            if (id[i][j] == 0) {
                how++;
                dfs(i, j);
            }
        }
    }

    if (op == 1) {
        best = how_big[1];
        for (i = 2; i <= how; i++)
            best = max(best, how_big[i]);

        printf("%d", best);

        return 0;
    }

    how_big[dead_place] = -1000;
    best = 0;

    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            _try(i, j);

    printf("%d %d\n%c\n", ans_x, ans_y, ans_col);

    return 0;
}

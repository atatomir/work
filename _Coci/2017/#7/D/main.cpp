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

#define maxN 1024
#define maxCnt maxN * maxN

struct rect {
    int lmin, lmax, cmin, cmax;
};

int defX[4] = {-1, 1, 0, 0};
int defY[4] = {0, 0, -1, 1};

int n, m, i, j, cnt, p;
char mat[maxN][maxN];
int prov[maxN][maxN];
string s[maxCnt];

int lmin, lmax, cmin, cmax;
rect R[maxCnt];

void solve(int id);

bool is_digit(char c) {
    return '0' <= c && c <= '9';
}

bool is_way(char c) {
    if (c == '+') return true;
    if (c == '-') return true;
    if (c == '|') return true;
    return false;
}

void dfs(int x, int y) {
    int i, xx, yy;

    lmin = min(lmin, x);
    lmax = max(lmax, x);
    cmin = min(cmin, y);
    cmax = max(cmax, y);
    prov[x][y] = cnt;

    for (i = 0; i < 4; i++) {
        xx = x + defX[i];
        yy = y + defY[i];

        if (prov[xx][yy] != 0) continue;
        if (mat[xx][yy] != '.' && !is_digit(mat[xx][yy])) continue;
        dfs(xx, yy);
    }
}

void set_prov() {
    int i, j;

    lmin--; lmax++;
    cmin--; cmax++;

    for (i = lmin; i <= lmax; i++)
        for (j = cmin; j <= cmax; j++)
            prov[i][j] = cnt;

    R[cnt] = {lmin, lmax, cmin, cmax};
}

void get_way(int id, int x, int y) {
    while (true) {
        prov[x][y] = id;

        if (mat[x][y] == '-' || mat[x][y] == '+') {
            if (prov[x][y - 1] == 0 && is_way(mat[x][y - 1])) {
                y--;
                continue;
            }
            if (prov[x][y + 1] == 0 && is_way(mat[x][y + 1])) {
                y++;
                continue;
            }
        }

        if (mat[x][y] == '|' || mat[x][y] == '+') {
            if (prov[x + 1][y] == 0 && is_way(mat[x + 1][y])) {
                x++;
                continue;
            }
            if (prov[x + 1][y] != 0 && is_way(mat[x + 1][y])) {
                solve(prov[x + 1][y]);
                return;
            }
        }
    }
}

void solve(int id) {
    int i, j;

    for (i = R[id].lmax; i >= R[id].lmin; i--) {
        if (mat[i][R[id].cmax + 1] == '-') get_way(id, i, R[id].cmax + 1);
        if (mat[i][R[id].cmin - 1] == '-') get_way(id, i, R[id].cmin - 1);
    }

    cout << s[id] << '\n';
}

int main()
{
   // freopen("test.in","r",stdin);

    scanf("%d%d\n", &n, &m);
    for (i = 1; i <= n; i++) scanf("%s\n", mat[i] + 1);

    for (i = 0; i <= n + 1; i++)
        mat[i][0] = mat[i][m + 1] = '#';

    for (i = 0; i <= m + 1; i++)
        mat[0][i] = mat[n + 1][i] = '#';

    //! find containers
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            if (prov[i][j] != 0) continue;
            if (!is_digit(mat[i][j])) continue;

            cnt++;
            for (p = j; is_digit(mat[i][p]); p++)
                s[cnt] = s[cnt] + mat[i][p];

            lmin = lmax = i;
            cmin = cmax = j;
            dfs(i, j);

            set_prov();
        }
    }

    solve(1);


    return 0;
}

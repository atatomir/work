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

struct coup {
    int dim, i;
    vector<int> list[maxN];
    int l[maxN], r[maxN];
    bool us[maxN];
    bool deny[maxN];

    void init(int _n) {
        dim = _n;
        for (i = 1; i <= dim; i++) list[i].clear();
        memset(l, 0, sizeof(l));
        memset(r, 0, sizeof(r));
        memset(deny, 0, sizeof(deny));
    }

    bool pairUp(int node) {
        if (deny[node]) return false;
        if (us[node]) return false;
        us[node] = true;

        for (auto to : list[node]) {
            if (r[to]) continue;
            l[node] = to;
            r[to] = node;
            return true;
        }

        for (auto to : list[node]) {
            if (!pairUp(r[to])) continue;
            l[node] = to;
            r[to] = node;
            return true;
        }


        return false;
    }

    void run() {
        int i;
        bool ok;

        ok = true;
        while (ok) {
            memset(us, 0, sizeof(us));
            ok = false;

            for (i = 1; i <= dim; i++) {
                if (l[i]) continue;
                ok |= pairUp(i);
            }
        }
    }
};

int t, ti;
int n, m, i, j, x, y;
char c;
coup work;
char data[maxN][maxN], rez[maxN][maxN];
vector< pair<char, pair<int, int> > > ch;

void solve_lines() {
    int i, j;

    work.init(2 * n);
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (data[i][j] != 'x' && data[i][j] != 'o') {
                work.list[i].pb(j);
            } else {
                work.deny[i] = true;
                work.l[i] = j;
                work.r[j] = i;
            }
        }
    }

    work.run();
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (work.l[i] != j) continue;
            if (data[i][j] == '.') data[i][j] = 'x';
            if (data[i][j] == '+') data[i][j] = 'o';
        }
    }
}

void solve_diag() {
    int i, j;

    work.init(2 * n);
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (data[i][j] != '+' && data[i][j] != 'o') {
                work.list[i + j].pb(n + i - j);
            } else {
                work.deny[i + j] = true;
                work.l[i + j] = n + i - j;
                work.r[n + i - j] = i + j;
            }
        }
    }

    work.run();
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (work.l[i + j] != n + i - j) continue;
            if (data[i][j] == '.') data[i][j] = '+';
            if (data[i][j] == 'x') data[i][j] = 'o';
        }
    }
}

int main()
{
    freopen("test.in","r",stdin);
    freopen("test.out","w",stdout);

    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++) {
        scanf("%d%d\n", &n, &m);

        for (i = 1; i <= n; i++)
            for (j = 1; j <= n; j++)
                data[i][j] = '.';

        for (i = 1; i <= m; i++) {
            scanf("%c%d%d\n", &c, &x, &y);
            data[x][y] = c;
        }

        memcpy(rez, data, sizeof(data));
        solve_lines();
        solve_diag();

        int pts = 0;
        ch.clear();

        for (i = 1; i <= n; i++) {
            for (j = 1; j <= n; j++) {
                if (data[i][j] == '+') pts++;
                if (data[i][j] == 'x') pts++;
                if (data[i][j] == 'o') pts += 2;

                if (rez[i][j] != data[i][j])
                    ch.pb(mp(data[i][j], mp(i, j)));
            }
        }

        printf("Case #%d: %d %d\n", ti, pts, ch.size());
        for (auto e : ch)
            printf("%c %d %d\n", e.first, e.second.first, e.second.second);
    }


    return 0;
}

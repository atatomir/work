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

const int maxN = 611;

ll n, d1, d2, i, j, need;
vector< pair<ll, ll> > comb;
int col[maxN][maxN], gr[maxN][maxN];
queue< pair<int, int> > Q;
vector< pair<int, int> > wh[4];

void run(int val) {
    int x, y;

    y = 0;
    for (x = 0; x * x <= val; x++) {
        while (x * x + (y + 1) * (y + 1) <= val) y++;
        while (x * x + y * y > val) y--;

        if (x * x + y * y == val) comb.pb(mp(x, y));
    }
}

void bfs(int x, int y) {
    vector<ll> vx, vy;

    Q.push(mp(x, y));
    while (!Q.empty()) {
        x = Q.front().first;
        y = Q.front().second;
        Q.pop();

        for (auto e : comb) {
            vx = {e.first, -e.first};
            vy = {e.second, -e.second};

            for (auto dx : vx) {
                for (auto dy : vy) {
                    int xx = x + dx;
                    int yy = y + dy;

                    if (xx < 0 || xx >= 2 * n) continue;
                    if (yy < 0 || yy >= 2 * n) continue;
                    if (col[xx][yy] != 0) continue;
                    col[xx][yy] = -col[x][y];
                    Q.push(mp(xx, yy));
                }
            }
        }
    }
}

void solve(ll D, ll df) {
    ll i, j;

    memset(col, 0, sizeof(col));
    comb.clear();

    run(D);
    for (i = 0; i < 2 * n; i++) {
        for (j = 0; j < 2 * n; j++) {
            if (col[i][j] == 1) gr[i][j] |= df;
            if (col[i][j] != 0) continue;
            col[i][j] = 1;
            bfs(i, j);
            if (col[i][j] == 1) gr[i][j] |= df;
        }
    }
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%lld%lld%lld", &n, &d1, &d2);
    solve(d1, 1);
    solve(d2, 2);

    for (i = 0; i < 2 * n; i++) {
        for (j = 0; j < 2 * n; j++) {
            wh[gr[i][j]].pb(mp(i, j));
        }
    }

    int tp = 0;
    while (wh[tp].size() < n * n) tp++;
    wh[tp].resize(n * n);
    for (auto e : wh[tp])
        printf("%d %d\n", e.first, e.second);

    return 0;
}

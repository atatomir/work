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

#define maxN 111
#define mod 1000000007
#define cos vraja_muntelui_in_marea_albastra

ll defX[4] = {-1, 1, 0, 0};
ll defY[4] = {0, 0, -1, 1};

ll H, W, i, j, n;
pair<ll, ll> P[maxN];
vector<ll> xx, yy;
ll ans;

ll lns, cos;
ll coef_ln[maxN], coef_co[maxN];

bool deny[maxN][maxN];
ll dist[maxN][maxN];
ll coef[maxN][maxN];
queue< pair<ll, ll> > Q;

void compress_line(int ln) {
    ll up, down;
    int i;

    up = ln * W;
    down = (H - ln) * W;

    for (i = 1; i <= n; i++) {
        if (P[i].first <= ln)
            up--;
        else
            down--;
    }

    up %= mod;
    down %= mod;
    ans += up * down;
    ans %= mod;
}

void compress_column(int co) {
    ll le, ri;
    int i;

    le = co * H;
    ri = (W - co) * H;

    for (i = 1; i <= n; i++) {
        if (P[i].second <= co)
            le--;
        else
            ri--;
    }

    le %= mod;
    ri %= mod;
    ans += le * ri;
    ans %= mod;
}

void add_black_cell(int x, int y) {
    int i, x_comp, y_comp;

    for (x_comp = 1; coef_ln[x_comp] < x; x -= coef_ln[x_comp++]);
    for (y_comp = 1; coef_co[y_comp] < y; y -= coef_co[y_comp++]);

    deny[x_comp][y_comp] = true;
}

void run_bfs() {
    int i, x, y, xx, yy;

    while (!Q.empty()) {
        x = Q.front().first;
        y = Q.front().second;
        Q.pop();

        for (i = 0; i < 4; i++) {
            xx = x + defX[i];
            yy = y + defY[i];

            if (deny[xx][yy] || (dist[xx][yy] != 0)) continue;
            dist[xx][yy] = dist[x][y] + 1;
            Q.push(mp(xx, yy));
        }
    }
}

void brute() {
    int i, j, k, l;

    for (i = 1; i <= lns; i++) {
        for (j = 1; j <= cos; j++) {
            if (deny[i][j]) continue;

            memset(dist, 0, sizeof(dist));
            Q.push(mp(i, j));
            dist[i][j] = 1;

            run_bfs();

            for (k = 1; k <= lns; k++)
                for (l = 1; l <= cos; l++)
                    if (!deny[k][l])
                        ans += ((coef[i][j] * coef[k][l]) % mod) * (dist[k][l] - 1), ans %= mod;
        }
    }
}

int main()
{
    freopen("test.in","r",stdin);

    cin >> H >> W >> n;
    for (i = 1; i <= n; i++) {
        cin >> P[i].first >> P[i].second;
        P[i].first++;
        P[i].second++;
        xx.pb(P[i].first);
        yy.pb(P[i].second);
    }

    xx.pb(0);
    xx.pb(H + 1);

    yy.pb(0);
    yy.pb(W + 1);

    sort(xx.begin(), xx.end());
    xx.resize(unique(xx.begin(), xx.end()) - xx.begin());

    sort(yy.begin(), yy.end());
    yy.resize(unique(yy.begin(), yy.end()) - yy.begin());

    for (i = 0; i + 1 < xx.size(); i++) {
        if (i != 0) coef_ln[++lns] = 1;

        if (xx[i + 1] - xx[i] >= 2) {
            coef_ln[++lns] = xx[i + 1] - xx[i] - 1;

            for (j = xx[i] + 1; j + 1 < xx[i + 1]; j++)
                compress_line(j);
        }
    }

    for (i = 0; i + 1 < yy.size(); i++) {
        if (i != 0) coef_co[++cos] = 1;

        if (yy[i + 1] - yy[i] >= 2) {
            coef_co[++cos] = yy[i + 1] - yy[i] - 1;

            for (j = yy[i] + 1; j + 1 < yy[i + 1]; j++)
                compress_column(j);
        }
    }

    for (i = 0; i <= cos; i++)
        deny[0][i] = deny[lns + 1][i] = true;

    for (i = 0; i <= lns; i++)
        deny[i][0] = deny[i][cos + 1] = true;

    for (i = 1; i <= n; i++)
        add_black_cell(P[i].first, P[i].second);

    for (i = 1; i <= lns; i++)
        for (j = 1; j <= cos; j++)
            coef[i][j] = (coef_ln[i] * coef_co[j]) % mod;

    ans *= 2;
    brute();
    ans = (ans * ( (mod + 1) / 2 )) % mod;

    cout << ans;

    return 0;
}

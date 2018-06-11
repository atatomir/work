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

const int maxN = 2018 * 2;

int n, m, i, j;
char s[maxN][maxN];

int d[maxN], dist[maxN][maxN];
pair<int, int> to_l[maxN], to_r[maxN];
pair<int, int> le, ri;
queue<int> Q;

vector< pair<int, int> > Points;

void run() {
    int i;

    for (i = 1; i <= n + m; i++) d[i] = 0;

    while (!Q.empty()) {
        int act = Q.front(); Q.pop();
        if (act <= n) {
            if (ri.first > ri.second) {
                ri.first = to_l[act].second + 1;
                ri.second = to_l[act].second;
            }

            while (to_l[act].first < ri.first) Q.push((--ri.first) + n), d[ri.first + n] = d[act] + 1;
            while (to_l[act].second > ri.second) Q.push((++ri.second) + n), d[ri.second + n] = d[act] + 1;
        } else {
            act -= n;
            if (le.first > le.second) {
                le.first = to_r[act].second + 1;
                le.second = to_r[act].second;
            }

            while (to_r[act].first < le.first) Q.push(--le.first), d[le.first] = d[act+ n] + 1;
            while (to_r[act].second > le.second) Q.push(++le.second), d[le.second] = d[act + n] + 1;
        }
    }
}

int get_dist(int x, int y, int xx, int yy) {
    int ans1 = min(dist[x][xx], dist[x][n + yy]);
    int ans2 = min(dist[n + y][xx], dist[n + y][n + yy]);
    return min(ans1, ans2);
}

void solve() {
    int i, j, p1, p2;

    Points.clear();
    for (i = 1; i <= n; i++) {
        for (p1 = 1; p1 <= m && s[i][p1] == '.'; p1++);
        for (p2 = m; p2 >= 1 && s[i][p2] == '.'; p2--);
        to_l[i] = mp(p1, p2);

        if (p1 <= p2) {
            Points.pb(mp(i, to_l[i].first));
            Points.pb(mp(i, to_l[i].second));
        }
    }

    for (i = 1; i <= m; i++) {
        for (p1 = 1; p1 <= n && s[p1][i] == '.'; p1++);
        for (p2 = n; p2 >= 1 && s[p2][i] == '.'; p2--);
        to_r[i] = mp(p1, p2);

        if (p1 <= p2) {
            Points.pb(mp(to_r[i].first, i));
            Points.pb(mp(to_r[i].second, i));
        }
    }

    for (i = 1; i <= n; i++) {
        le = mp(i, i);
        ri = mp(m + 1, 0);
        Q.push(i);
        d[i] = 0;
        run();

        for (j = 1; j <= n + m; j++) dist[i][j] = d[j];
    }

    for (i = 1; i <= m; i++) {
        le = mp(n + 1, 0);
        ri = mp(i, i);
        Q.push(n + i);
        d[n + i] = 0;
        run();

        for (j = 1; j <= n + m; j++) dist[n + i][j] = d[j];
    }

    sort(Points.begin(), Points.end());
    Points.resize(unique(Points.begin(), Points.end()) - Points.begin());

    int ans = 0;
    for (auto p1 : Points) {
        for (auto p2 : Points) {
            if (p1 < p2) break;
            ans = max(ans, get_dist(p1.first, p1.second, p2.first, p2.second));
        }
    }

    printf("%d\n", ans);
}

int main()
{
    freopen("jinxiety.in","r",stdin);
    freopen("jinxiety.out","w",stdout);

    while (true) {
        scanf("%d%d\n", &n, &m);
        if (n == 0) return 0;
        for (i = 1; i <= n; i++) scanf("%s\n", s[i] + 1);

        solve();
    }



    return 0;
}

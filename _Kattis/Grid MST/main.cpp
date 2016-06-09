#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <map>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 100011
#define maxSize 1024

const int defX[4] = {-1, 1, 0, 0};
const int defY[4] = {0, 0, -1, 1};

struct edge {
    int x, y, dist;

    bool operator<(const edge& who)const {
        return dist < who.dist;
    }
};



int n, i;
pair<int, int> P[maxN];

int color[maxSize][maxSize];
queue< pair<int, int> > Q;
map< pair<int, int>, bool > M;

vector< edge > E;
int dad[maxN];

int ans;



int dist(pair<int, int> a, const pair<int, int> b) {
    a.first -= b.first;
    a.second -= b.second;

    return (a.first < 0 ? -a.first : a.first) + (a.second < 0 ? -a.second : a.second);
}

void lee() {
    int i, x, y;

    M.clear();

    for (i = 1; i <= n; i++) {
        color[P[i].first][P[i].second] = i;
        Q.push(P[i]);
    }

    while (!Q.empty()) {
        auto p = Q.front(); Q.pop();

        for (i = 0; i < 4; i++) {
            x = p.first + defX[i];
            y = p.second + defY[i];

            if (color[x][y] == -1) continue;
            if (color[x][y] != 0) {
                int c1 = color[p.first][p.second];
                int c2 = color[x][y];

                if (c1 > c2) swap(c1, c2);

                if (c1 != c2 && M[mp(c1, c2)] == false) {
                    E.pb({c1, c2, dist(P[c1], P[c2])});
                    M[mp(c1, c2)] = true;
                }
            } else {
                color[x][y] = color[p.first][p.second];
                Q.push(mp(x, y));
            }
        }
    }
}

int Find(int x) {
    if (dad[x] == x) return x;
    dad[x] = Find(dad[x]);
    return dad[x];
}

bool Merge(int x, int y) {
    x = Find(x);
    y = Find(y);

    if (x == y) return false;

    dad[y] = x;
    return true;
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) scanf("%d%d", &P[i].first, &P[i].second), P[i].first++, P[i].second++;

    for (i = 0; i <= 1010; i++)
        color[0][i] = color[1010][i] = color[i][0] = color[i][1010] = -1;

    lee();
    sort(E.begin(), E.end());

    for (i = 1; i <= n; i++) dad[i] = i;
    for (auto e : E) {
        if (Merge(e.x, e.y))
            ans += e.dist;
    }

    printf("%d", ans);


    return 0;
}

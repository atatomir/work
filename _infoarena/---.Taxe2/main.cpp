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
#define pii pair<int, pair<int, int>>
#define fixed vraja_marii

struct cmp {
    bool operator()(const pii &a, const pii &b) {
        return a > b;
    }
};

int defX[4] = {-1, 1, 0, 0};
int defY[4] = {0, 0, -1, 1};

int n, i, j, s;
int pay[maxN][maxN];

int fixed[maxN][maxN];
priority_queue< pii, vector<pii>, cmp> H;

int main()
{
    freopen("taxe2.in","r",stdin);
    freopen("taxe2.out","w",stdout);

    scanf("%d%d", &s, &n);
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            scanf("%d", &pay[i][j]);

    for (i = 0; i <= n + 1; i++)
        fixed[0][i] = fixed[n + 1][i] = fixed[i][0] = fixed[i][n + 1] = -1;

    H.push(mp(1 + pay[1][1], mp(1, 1)));
    while (!H.empty()) {
        int now = H.top().first;
        auto wh = H.top().second;
        H.pop();

        if (fixed[wh.first][wh.second]) continue;
        fixed[wh.first][wh.second] = now;

        for (i = 0; i < 4; i++) {
            int xx = wh.first + defX[i];
            int yy = wh.second + defY[i];

            if (!fixed[xx][yy])
                H.push(mp(fixed[wh.first][wh.second] + pay[xx][yy], mp(xx, yy)));
        }
    }

    /*for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++)
            cerr << fixed[i][j] << ' ';
        cerr << '\n';
    }*/

    int v = fixed[n][n] - 1;
    printf("%d", max(-1, s - v));


    return 0;
}

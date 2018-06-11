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

typedef pair<int, pair<int, int> > conf;

const int maxN = 1024;
const int inf = 100000000;

const int defX[4] = {-1, 1, 0, 0};
const int defY[4] = {0, 0, -1, 1};

int n, m, i, j, ans;
char mat[maxN][maxN];
pair<int, int> S, F, D;

vector< vector<int> > dist_S, dist_D, dist_F, dist_forw, dist_backw;
queue< pair<int, int > > Q;

priority_queue< conf, vector<conf>, greater<conf> > H;

void compute_distance(pair<int, int> orig, vector< vector<int> >& data, char src) {
    int i, j, x, y, xx, yy;

    data = vector< vector<int> >(n + 3, vector<int>(m + 3, inf));
    data[orig.first][orig.second] = 0;
    while (!Q.empty()) Q.pop();
    Q.push(orig);

    while (!Q.empty()) {
        x = Q.front().first;
        y = Q.front().second;
        Q.pop();

        for (i = 0; i < 4; i++) {
            xx = x + defX[i];
            yy = y + defY[i];

            if (mat[xx][yy] != src) continue;
            if (data[xx][yy] > data[x][y] + 1) {
                data[xx][yy] = data[x][y] + 1;
                Q.push(mp(xx, yy));
            }
        }
    }
}

void dijkstra(vector< vector<int> >& data, char src) {
    int i, j, cc, x, y, xx, yy;

    while (!H.empty()) H.pop();
    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            if (data[i][j] < inf)
                H.push(mp(data[i][j], mp(i, j)));

    while (!H.empty()) {
        cc = H.top().first;
        x = H.top().second.first;
        y = H.top().second.second;
        H.pop();

        if (data[x][y] != cc) continue;
        for (i = 0; i < 4; i++) {
            xx = x + defX[i];
            yy = y + defY[i];

            if (mat[xx][yy] != src) continue;
            if (data[xx][yy] > data[x][y] + 1) {
                data[xx][yy] = data[x][y] + 1;
                H.push(mp(data[xx][yy], mp(xx, yy)));
            }
        }
    }
}

void solve() {
    int i, j, x, y, xx, yy;

    //! hai pe uscat...
    ans = min(ans, dist_S[F.first][F.second]);

    //! hai pe apa... doar o data
    dist_forw = dist_backw = vector< vector<int> >(n + 3, vector<int>(m + 3, inf));
    for (x = 1; x <= n; x++) {
        for (y = 1; y <= m; y++) {
            if (mat[x][y] != '0') continue;

            for (i = 0; i < 4; i++) {
                xx = x + defX[i];
                yy = y + defY[i];

                if (mat[xx][yy] != '1') continue;
                dist_forw[x][y] = min(dist_forw[x][y], max(dist_S[xx][yy] + 1, dist_D[x][y]));
                dist_backw[x][y] = min(dist_backw[x][y], dist_F[xx][yy] + 1);
            }
        }
    }

    dijkstra(dist_forw, '0');
    //dijkstra(dist_backw, '0'); //! nu mai e nevoie de asta ...

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            if (mat[i][j] != '0') continue;
            ans = min(ans, dist_forw[i][j] + dist_backw[i][j]);
        }
    }
}

int main()
{
    freopen("delfin.in","r",stdin);
    freopen("delfin.out","w",stdout);

    scanf("%d%d\n", &n, &m);
    for (i = 1; i <= n; i++) {
        scanf("%s\n", mat[i] + 1);
        for (j = 1; j <= m; j++) {
            if (mat[i][j] == 'S') {
                S = mp(i, j);
                mat[i][j] = '1';
            }

            if (mat[i][j] == 'F') {
                F = mp(i, j);
                mat[i][j] = '1';
            }

            if (mat[i][j] == 'D') {
                D = mp(i, j);
                mat[i][j] = '0';
            }
        }
    }

    for (i = 0; i <= n + 1; i++)
        mat[i][0] = mat[i][m + 1] = '@';

    for (i = 0; i <= m + 1; i++)
        mat[0][i] = mat[n + 1][i] = '@';

    compute_distance(S, dist_S, '1');
    compute_distance(F, dist_F, '1');
    compute_distance(D, dist_D, '0');

    ans = inf;
    solve();

    printf("%d", ans);

    return 0;
}

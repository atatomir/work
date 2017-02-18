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

#define maxN 33

int defX[4] = {-1, 1, 0, 0};
int defY[4] = {0, 0, -1, 1};

struct mv {
    int x1, y1;
    int x2, y2;
};

int n, m, k, i;
pair<int, int> pos[maxN];

int cnt;
vector<mv> ord;
bool mat[maxN][maxN];


void _back() {
    int i, j;
    int xx, yy, k;

    if (cnt == 1) {
        for (auto e : ord)
            printf("%d %d %d %d\n", e.x1 - 1, e.y1 - 1, e.x2 - 1, e.y2 - 1);
        exit(0);
    }


    for (i = 2; i <= n + 1; i++) {
        for (j = 2; j <= m + 1; j++) {
            if (mat[i][j] == false) continue;

            for (k = 0; k < 4; k++) {
                xx = i + defX[k];
                yy = j + defY[k];

                if (mat[xx + defX[k]][yy + defY[k]]) continue;
                if (mat[xx][yy] == false) continue;

                mat[i][j] = mat[xx][yy] = false;
                mat[xx + defX[k]][yy + defY[k]] = true;
                cnt--;

                ord.pb({i, j, xx + defX[k], yy + defY[k]});
                _back();
                ord.pop_back();

                mat[i][j] = mat[xx][yy] = true;
                mat[xx + defX[k]][yy + defY[k]] = false;
                cnt++;
            }
        }
    }
}

int main()
{
    freopen("immortal.in","r",stdin);
    freopen("immortal.out","w",stdout);

    scanf("%d%d%d", &n, &m, &k);
    for (i = 1; i <= k; i++) {
        scanf("%d%d", &pos[i].first, &pos[i].second);
        mat[pos[i].first + 1][pos[i].second + 1] = true;
    }

    ord.reserve(22);
    for (i = 0; i <= n + 1; i++) mat[i][0] = mat[i][1] = mat[i][m + 2] = mat[i][m + 3] = true;
    for (i = 0; i <= m + 1; i++) mat[0][i] = mat[1][i] = mat[n + 2][i] = mat[n + 3][i] = true;

    cnt = k;
    _back();

    return 0;
}

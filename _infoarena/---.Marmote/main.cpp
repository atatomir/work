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

#define maxN 1024

const int defX[4] = {-1, 1, 0, 0};
const int defY[4] = {0, 0, -1, 1};

int n, m, k, l, i, x, y;
bool mat[maxN][maxN];
bool dead[maxN][maxN];
queue< pair<int, int> > Q;

int cnt;

int dist(int x, int y, int xx, int yy) {
    if (x < xx) swap(x, xx);
    if (y < yy) swap(y, yy);
    return x + y - xx - yy;
}

void bfs(int x, int y, int L) {
    int i, j, xx, yy;

    for (i = 0; i <= L && dead[x + i][y] == false; i++) {
        for (j = 0; i + j <= L; j++) {
            if (dead[x + i][y + j]) break;
            mat[x + i][y + j] = true;
        }

        for (j = 0; i + j <= L; j++) {
            if (dead[x + i][y - j]) break;
            mat[x + i][y - j] = true;
        }
    }

    for (i = 0; i <= L && dead[x - i][y] == false; i++) {
        for (j = 0; i + j <= L; j++) {
            if (dead[x - i][y + j]) break;
            mat[x - i][y + j] = true;
        }

        for (j = 0; i + j <= L; j++) {
            if (dead[x - i][y - j]) break;
            mat[x - i][y - j] = true;
        }
    }

}

int main()
{
    freopen("marmote.in","r",stdin);
    freopen("marmote.out","w",stdout);

    scanf("%d%d%d%d", &n, &m, &k, &l);
    for (i = 1; i <= n; i++) dead[i][0] = dead[i][m + 1] = true;
    for (i = 1; i <= m; i++) dead[0][i] = dead[n + 1][i] = true;

    for (i = 1; i <= k; i++) {
        scanf("%d%d", &x, &y);
        if (mat[x][y]) continue;

        printf("%d\n", i);

        bfs(x, y, 2 * l);
    }



    return 0;
}

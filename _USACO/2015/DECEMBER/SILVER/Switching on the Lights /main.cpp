#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 111

int defX[4] = {0, 0, -1, 1};
int defY[4] = {-1, 1, 0, 0};

int n, m, i, j, a, b, x, y;
bool isOn[maxN][maxN];
bool us[maxN][maxN];
vector< pair<int, int> > list[maxN][maxN];

void dfs(int x, int y) {
    us[x][y] = true;

    for (auto to : list[x][y]) {
        int xx = to.first;
        int yy = to.second;

        if (isOn[xx][yy] == false) {
            isOn[xx][yy] = true;

            for (int i = 0; i < 4; i++) {
                int x_leg = xx + defX[i];
                int y_leg = yy + defY[i];

                if (us[x_leg][y_leg]) {
                    dfs(xx, yy);
                    break;
                }
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        int xx = x + defX[i];
        int yy = y + defY[i];

        if (isOn[xx][yy] && us[xx][yy] == false)
            dfs(xx, yy);
    }
}

int main()
{
    freopen("lightson.in","r",stdin);
    freopen("lightson.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; i++) {
        scanf("%d%d%d%d", &x, &y, &a, &b);
        list[x][y].pb(mp(a, b));
    }

    isOn[1][1] = true;
    dfs(1, 1);

    int ans = 0;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            if (isOn[i][j])
                ans++;

    printf("%d", ans);

    return 0;
}

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

#define maxN 61

int defX[5] = {0, -1, 0, +1, 0};
int defY[5] = {0, 0, +1, 0, -1};

int n, i, j, x, y, l, val, how;

int was[maxN][maxN];
int first_time;
bool deny[maxN][maxN][5];

bool us[maxN][maxN];

int def = 3;

void add_deny(int x, int y, int dir) {
    x += def; y += def;

    if (dir == 1)
        deny[x][y + 1][4] = deny[x][y][2] = true;

    if (dir == 2)
        deny[x][y + 1][3] = deny[x + 1][y + 1][1] = true;

    if (dir == 3)
        deny[x + 1][y][2] = deny[x + 1][y + 1][4] = true;

    if (dir == 4)
        deny[x][y][3] = deny[x + 1][y][1] = true;
}

void dfs(int x, int y) {
    us[x][y] = true;
    how++;

    for (int i = 1; i <= 4; i++) {
        int xx = x + defX[i];
        int yy = y + defY[i];

        if (!deny[x][y][i] && us[xx][yy] == false)
            dfs(xx, yy);
    }
}

int main()
{
    freopen("zona.in","r",stdin);
    freopen("zona.out","w",stdout);

    scanf("%d%d%d%d", &x, &y, &n, &l);

    was[x][y] = 1;
    for (i = 1; i <= l; i++) {
        scanf("%d", &val);

        add_deny(x, y, val);

        x += defX[val];
        y += defY[val];

        first_time = was[x][y];
        was[x][y] = i + 1;
    }

    printf("%d\n", was[x][y] - first_time);

    n += def + 2;
    def = 0;
    for (i = 1; i <= n; i++) {
        add_deny(1, i, 2);
        add_deny(n, i, 2);

        add_deny(i, 1, 3);
        add_deny(i, n, 3);
    }


    dfs(2, 2);

    how = 0;
    for (i = 2; i <= n; i++)
        for (j = 2; j <= n; j++)
            if (us[i][j] == false)
                dfs(i, j);

    printf("%d", how);

    return 0;
}

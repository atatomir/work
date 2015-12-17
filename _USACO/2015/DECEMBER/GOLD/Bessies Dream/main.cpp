#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <unordered_map>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 1024

const int defX[4] = {0, 0, 1, -1};
const int defY[4] = {-1, 1, 0, 0};

struct Position {
    int x, y;
    bool smell;
    int dir;
    int my_hash;

    Position(int _x, int _y, int _dir, bool _smell) {
        x = _x; y = _y;
        dir = _dir;
        smell = _smell;
    }

    void set(int _x, int _y, int _dir, bool _smell) {
        x = _x; y = _y;
        dir = _dir;
        smell = _smell;
    }

    int getHash() {
        my_hash = x * 10010 + y * 10 + dir * 2 + smell;
        return my_hash;
    }

    void parseHash(int _hash) {
        x = _hash / 10010;
        _hash %= 10010;

        y = _hash / 10;
        _hash %= 10;

        dir = _hash / 2;
        _hash %= 2;

        smell = _hash;
    }
};

int n, m, i, j;
int mat[maxN][maxN];
//unordered_map<int, int> dp;
int dp[maxN * 10100];
Position aux(0, 0, 0, 0), now(0, 0, 0, 0), to(0, 0, 0, 0);
queue<int> Q;

int ans = 1000000000;
bool anywhere;

int main()
{
    freopen("dream.in","r",stdin);
    freopen("dream.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            scanf("%d", &mat[i][j]);

    //dp.clear();
    aux.set(1, 1, 0, 0);
    dp[aux.getHash()] = 1;
    Q.push(aux.my_hash);

    while (!Q.empty()) {
        int now_hash = Q.front(); Q.pop();
        now.parseHash(now_hash);

        /*cerr << now.x << ' ' << now.y << '\n';
        if (now.x == 1 && now.y == 3) {
            cerr << "1";
        }*/

        anywhere = false;
        if (mat[now.x][now.y] == 4) {
            if (mat[now.x + defX[now.dir]][now.y + defY[now.dir]] == 0)
                anywhere = true;
            if (mat[now.x + defX[now.dir]][now.y + defY[now.dir]] == 3 && now.smell == false)
                anywhere = true;
        }

        for (i = 0; i < 4; i++) {
            to.set(now.x + defX[i], now.y + defY[i], i, now.smell);

            if (mat[to.x][to.y] == 0) continue;
            if (mat[to.x][to.y] == 2) to.smell = true;
            if (mat[to.x][to.y] == 3 && to.smell == false) continue;
            if (mat[now.x][now.y] == 4 && i != now.dir && anywhere == false) continue;

            if (mat[to.x][to.y] == 4) to.smell = false;
            to.getHash();

            if (dp[to.my_hash] != 0) continue;
            dp[to.my_hash] = dp[now_hash] + 1;
            Q.push(to.my_hash);

            if (to.x == n && to.y == m)
                ans = min(ans, dp[to.my_hash]);
        }
    }

    if (ans == 1000000000)
        printf("-1");
    else
        printf("%d", ans - 1);

    return 0;
}

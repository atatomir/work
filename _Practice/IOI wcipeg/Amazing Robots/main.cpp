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

#define maxN 22
#define pii pair<short, short>
#define time_mod 12
#define to_state dp[to.pA.first][to.pA.second][to.pB.first][to.pB.second][to.t]
#define act_state dp[act.pA.first][act.pA.second][act.pB.first][act.pB.second][act.t]
#define from_to_state from[to.pA.first][to.pA.second][to.pB.first][to.pB.second][to.t]
#define from_dir_to_state from_dir[to.pA.first][to.pA.second][to.pB.first][to.pB.second][to.t]

int defX[4] = {-1, 1, 0, 0};
int defY[4] = {0, 0, -1, 1};
char defDir[4] = {'N', 'S', 'W', 'E'};

struct Guard {
    int x, y;
    int patrol;
    int dir;

    Guard() {
        char aux;
        scanf("%d%d%d %c\n", &x, &y, &patrol, &aux);
        if (aux == 'N') dir = 0;
        if (aux == 'S') dir = 1;
        if (aux == 'W') dir = 2;
        if (aux == 'E') dir = 3;
    }

    pair<int, int> where_is(int how) {
        how %= (2 * patrol - 2);
        if (how >= patrol)
            how = 2 * patrol - 2 - how;

        return mp(x + how * defX[dir], y + how * defY[dir]);
    }
};

struct Table {
    int n, m, k, i, j, x, y;
    char mat[maxN][maxN];
    vector<Guard> G;

    void init() {
        scanf("%d%d\n", &n, &m);
        for (i = 1; i <= n; i++) scanf("%s\n", mat[i] + 1);

        scanf("%d", &k);
        G.clear();
        for (i = 1; i <= k; i++) G.pb(Guard());

        for (i = 1; i <= n; i++) {
            for (j = 1; j <= m; j++) {
                if (mat[i][j] == 'X') {
                    mat[i][j] = '.';
                    x = i; y = j;
                }
            }
        }

        for (i = 0; i <= n + 1; i++)
            mat[i][0] = mat[i][m + 1] = 'E';
        for (i = 0; i <= m + 1; i++)
            mat[0][i] = mat[n + 1][i] = 'E';
    }

    int can_move(int xs, int ys, int xd, int yd, int ts) {
        /*
         * -1 for dead
         * 0 for wall
         * 1 for good
         */

        pair<int, int> ps = mp(xs, ys);
        pair<int, int> pd = mp(xd, yd);

        if (mat[xd][yd] == '#') {
            for (auto act : G)
                if (act.where_is(ts + 1) == ps)
                    return -1;

            return 0;
        }
        if (mat[xs][ys] == 'E') return 0;

        for (auto act : G) {
            if (act.where_is(ts + 1) == pd)
                return -1;

            if (act.where_is(ts) == pd)
                if (act.where_is(ts + 1) == ps)
                    return -1;
        }

        return 1;
    }
};

Table A, B;

struct state {
    pii pA, pB;
    char t;

    state() {}
    state(pii _pA, pii _pB, int _t) {
        pA = _pA;
        pB = _pB;
        t = _t;
    }

    state expand(int dir) {
        pii _pA, _pB;
        int _t = (t + 1) % time_mod, res;
        _pA = pA;
        _pB = pB;

        _pA.first += defX[dir];
        _pA.second += defY[dir];
        res = A.can_move(pA.first, pA.second, _pA.first, _pA.second,  t);
        if (res == -1) return state(pA, pB, -1);
        if (res == 0) _pA = pA;

        _pB.first += defX[dir];
        _pB.second += defY[dir];
        res = B.can_move(pB.first, pB.second, _pB.first, _pB.second,  t);
        if (res == -1) return state(pA, pB, -1);
        if (res == 0) _pB = pB;

        return state(_pA, _pB, _t);
    }

    bool is_final() {
        return A.mat[pA.first][pA.second] == 'E' && B.mat[pB.first][pB.second] == 'E';
    }
};


int i;
short dp[maxN][maxN][maxN][maxN][time_mod];
int from[maxN][maxN][maxN][maxN][time_mod];
char from_dir[maxN][maxN][maxN][maxN][time_mod];

queue< state > Q;
state act, to;

state where;
int ans;

vector<char> sol;


int compress(state act) {
    int ans = act.pA.first;
    ans <<= 5;

    ans += act.pA.second;
    ans <<= 5;

    ans += act.pB.first;
    ans <<= 5;

    ans += act.pB.second;
    ans <<= 5;

    ans += act.t;
    return ans;
}

state decompress(int id) {
    state ans;

    ans.t = id % 32;
    id >>= 5;

    ans.pB.second = id % 32;
    id >>= 5;

    ans.pB.first = id % 32;
    id >>= 5;

    ans.pA.second = id % 32;
    id >>= 5;

    ans.pA.first = id % 32;
    id >>= 5;

    return ans;
}

int main()
{
    freopen("test.in","r",stdin);

    A.init();
    B.init();

    Q.push(state(mp(A.x, A.y), mp(B.x, B.y), 0));
    dp[A.x][A.y][B.x][B.y][0] = 1;

    while (!Q.empty()) {
        act = Q.front(); Q.pop();

        if (act.is_final()) {
            where = act;
            ans = act_state;
            break;
        }

        for (i = 0; i < 4; i++) {
            to = act.expand(i);
            if (to.t == -1) continue;

            if (to_state == 0) {
                to_state = act_state + 1;
                Q.push(to);

                from_to_state = compress(act);
                from_dir_to_state = i;
            }
        }
    }

    printf("%d\n", ans - 1);

    while (ans > 1) {
        sol.pb( defDir[ from_dir[where.pA.first][where.pA.second][where.pB.first][where.pB.second][where.t]  ] );
        ans--;
        where = decompress(from[where.pA.first][where.pA.second][where.pB.first][where.pB.second][where.t]);
    }

    reverse(sol.begin(), sol.end());
    for (auto e : sol)
        printf("%c\n", e);


    return 0;
}

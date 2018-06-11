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

#define maxN 333

struct Piece {
    int m[4];
    int C;
    int id;

    bool operator<(const Piece& who)const {
        return C <= who.C;
    }
};

struct Cell {
    int x, y, v;

    bool operator<(const Cell& who)const {
        return v <= who.v;
    }
};

int t, ti, n, m, k, i, j, p;
Piece P[maxN * maxN];
int val[maxN][maxN];

vector<Cell> cells;
vector<Piece> pieces;

int sol[maxN * maxN][3];
ll ans;
bool us[maxN][maxN];

bool good(Cell act) {
    if (us[act.x - 1][act.y]) return false;
    if (us[act.x + 1][act.y]) return false;
    if (us[act.x][act.y - 1]) return false;
    if (us[act.x][act.y + 1]) return false;
    return true;
}

int main()
{
    freopen("input","r",stdin);
    freopen("output","w",stdout);

    cin >> t;
    for (ti = 1; ti <= t; ti++) {
        memset(sol, 0, sizeof(sol));
        memset(us, 0, sizeof(us));

        cin >> m >> n; k = 0;
        for (i = 1; i <= n; i++)
            for (j = 1; j <= m; j++)
                cin >> val[i][j];

        for (i = 1; i <= n * m; i++)
            cin >> P[i].m[0] >> P[i].m[1] >> P[i].m[2] >> P[i].m[3] >> P[i].C, P[i].id = i;

        sort(P + 1, P + n * m + 1);

        cells.clear();
        for (i = 1; i <= n; i++) {
            for (j = 1; j <= m; j++) {
                //if ((i + j) % 2) {
                    cells.pb({i, j, val[i][j]});
                //}
            }
        }
        sort(cells.begin(), cells.end());
        reverse(cells.begin(), cells.end());

        pieces.clear();
        for (i = 0; i < cells.size(); i++)
            pieces.pb(P[n * m - i]);

        sort(pieces.begin(), pieces.end());
        reverse(pieces.begin(), pieces.end());

        ans = 0; p = 0;
        for (i = 0; i < pieces.size(); i++) {
            while (p < cells.size()) {
                if (good(cells[p])) break;
                p++;
            }

            if (p >= cells.size()) break;
            if (min(pieces[i].C, cells[p].v) <= 0) continue;

            sol[pieces[i].id][0] = cells[p].x;
            sol[pieces[i].id][1] = cells[p].y;
            sol[pieces[i].id][2] = 0;
            ans += 1LL * min(pieces[i].C, cells[p].v);

            us[cells[p].x][cells[p].y] = true;
            p++;
        }

        for (i = 1; i <= n * m; i++) {
            //if (sol[i][1] == 72 && sol[i][0] == 93)
            //    cerr << 'd';

            cout << sol[i][1] << ' ' << sol[i][0] << ' ' << sol[i][2] << '\n';
        }

        cout << ans << '\n';
    }


    return 0;
}

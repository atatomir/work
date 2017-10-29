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

#define maxN 111

const int defX[8] = {0, 0, +1, +1, +1, -1, -1, -1};
const int defY[8] = {+1, -1, -1, 0, +1, -1, 0, +1};


int n, m, i, j;
int mat[maxN][maxN];
vector< pair<int, int> > wh[11];

int work[maxN][maxN];
vector< pair<int, int> > sol, sol2;
vector< pair<int, int> > ord;

bool brute(int x, int y, int val, bool to_sol);

void rev(int val, bool to_sol) {
    for (int tmp = 1; tmp <= val; tmp++) {
        auto el = sol2[sol2.size() - tmp];
        work[el.first][el.second] = 0;
    }

    sol2.resize(sol2.size() - val);
    if (to_sol)
        sol.resize(sol.size() - val);
}

bool _back(int x, int y, int pos, int val, bool to_sol) {
    if (val == 0)
        return true;

    if (pos == 8)
        return false;

    int xx = defX[pos] + x;
    int yy = defY[pos] + y;

    if (work[xx][yy] == 0) {
        if (brute(xx, yy, val, to_sol)) {
            if (_back(x, y, 0, val - 1, to_sol)) {
                return true;
            } else {
                rev(1, false);
                if (to_sol)
                    sol.resize(sol.size() - (1 << (val - 1)));
            }
        }
    }

    if (_back(x, y, pos + 1, val, to_sol)) {
        return true;
    } else {
        return false;
    }
}

bool brute(int x, int y, int val, bool to_sol) {
    if (_back(x, y, 0, val - 1, to_sol)) {
        sol2.pb(mp(x, y));
        if (to_sol) sol.pb(mp(x, y));
        rev(val, false);
        work[x][y] = val;
        sol2.pb(mp(x, y));
        return true;
    } else {
        return false;
    }
}

void execute(int x, int y) {
    if (work[x][y] != 0)
        exit(-1);

    work[x][y] = 1;
    while (true) {
        bool any = false;

        for (int pos = 0; pos < 8; pos++) {
            int xx = x + defX[pos];
            int yy = y + defY[pos];

            if (work[xx][yy] == work[x][y]) {
                work[xx][yy] = 0;
                work[x][y]++;
                any = true;
            }
        }

        if (!any) break;
    }
}

int main()
{
    freopen("tower8.in","r",stdin);
    freopen("tower8.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            scanf("%d", &mat[i][j]), wh[mat[i][j]].pb(mp(i, j));

    for (i = 0; i <= n + 1; i++)
        work[i][0] = work[i][m + 1] = 11;

    for (i = 0; i <= m + 1; i++)
        work[0][i] = work[n + 1][i] = 11;

    for (int gr = 9; gr > 0; gr--) {
        ord.clear();

        while (wh[gr].size() > 0) {

            for (auto e : wh[gr])
                work[e.first][e.second] = gr;

            for (i = 0; i < wh[gr].size(); i++) {
                auto el = wh[gr][i];
                work[el.first][el.second] = 0;

                sol2.clear();
                if (brute(el.first, el.second, gr, false)) {
                    ord.pb(el);
                    work[el.first][el.second] = 0;
                    wh[gr][i] = wh[gr].back();
                    wh[gr].pop_back();
                    i--; continue;
                } else {
                    work[el.first][el.second] = gr;
                }
            }
        }

        reverse(ord.begin(), ord.end());
        for (auto e : ord) {
            sol2.clear();
            brute(e.first, e.second, gr, true);
        }
    }

    printf("%d\n", sol.size());
    for (auto e : sol)
        printf("%d %d\n", e.first, e.second);

    //! --------------------------------

    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            work[i][j] = 0;

    for (auto e : sol)
        execute(e.first, e.second);

    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            if (work[i][j] != mat[i][j])
                cerr << "err";


    return 0;
}

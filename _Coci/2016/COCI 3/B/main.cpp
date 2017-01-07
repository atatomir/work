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

#define maxN 2016

int defX[2] = {+1, 0};
int defY[2] = {0, +1};

int n, m, i, j, xx, yy;
char s[maxN][maxN];

int prov[maxN][maxN];
vector< pair<int, int> > act, aux;
char best;

vector<char> sol;

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d%d\n", &n, &m);
    for (i = 1; i <= n; i++) scanf("%s\n", s[i] + 1);

    for (i = 1; i <= n; i++) s[i][m + 1] = 'z' + 1;
    for (i = 1; i <= m; i++) s[n + 1][i] = 'z' + 1;

    act.pb(mp(1, 1));
    for (int step = 1; step <= n + m - 2; step++) {
        aux = act;
        act.clear();
        best = 'z' + 1;

        for (auto e : aux) {
            for (i = 0; i < 2; i++) {
                xx = e.first + defX[i];
                yy = e.second + defY[i];

                if (!prov[xx][yy]) {
                    prov[xx][yy] = i + 1;
                    act.pb(mp(xx, yy));
                }
                best = min(best, s[xx][yy]);
            }
        }

        for (i = 0; i < act.size(); i++) {
            auto e = act[i];

            if (s[e.first][e.second] != best) {
                act[i] = act.back();
                act.pop_back();
                i--;
                continue;
            }
        }
    }

    sol = {};
    xx = n; yy = m;
    for (int step = 1; step <= n + m - 2; step++) {
        int zz = prov[xx][yy] - 1;

        sol.pb(s[xx][yy]);
        xx -= defX[zz];
        yy -= defY[zz];
    }

    sol.pb(s[1][1]);
    reverse(sol.begin(), sol.end());

    for (auto e : sol)
        printf("%c", e);

    return 0;
}

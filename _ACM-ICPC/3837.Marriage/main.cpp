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

#define maxN 33

int t, ti;
int n, i, j, c1, c2;
int id[333], coup[2][maxN];
int pref[maxN][maxN];
vector<int> ord[2][maxN];
string aux;
char name[2][maxN];

vector<int> who[maxN];
int pos[maxN];
vector< pair<char, char> > ans;


void solve() {
    int i, j;
    pair<int, int> best;

    for (i = 1; i <= n; i++)
        for (j = 0; j < n; j++)
            pref[i][ ord[1][i][j] ] = j;

    /*for (i = 1; i <= n; i++) {
        pos[i] = 0;
        who[ ord[0][i][0] ].pb(i);
    }

    bool ok = true;
    while (ok) {
        ok = false;

        for (i = 1; i <= n; i++) {
            if (who[i].size() <= 1) continue;
            ok = true;

            best = mp( pref[i][ who[i][0] ], who[i][0] );
            for (auto e : who[i])
                best = min(best, mp(pref[i][e], e));

            for (auto e : who[i]) {
                if (e == best.second) continue;

                pos[e]++;
                who[ ord[0][e][pos[e]] ].pb(e);
            }

            who[i] = {best.second};
        }
    }

    for (i = 1; i <= n; i++) coup[0][i] = ord[0][i][ pos[i] ]; */

    queue<int> Q;
    while (!Q.empty()) Q.pop();
    for (i = 1; i <= n; i++) {
        pos[i] = 0;
        Q.push(i);
    }

    while (!Q.empty()) {
        int man = Q.front();
        int wom = ord[0][man][pos[man]];

        if (coup[1][wom] == 0) {
            coup[0][man] = wom;
            coup[1][wom] = man;
            Q.pop();
        } else {
            if (pref[wom][man] < pref[wom][ coup[1][wom] ]) {
                coup[0][ coup[1][wom] ] = 0;
                Q.push(coup[1][wom]);

                coup[0][man] = wom;
                coup[1][wom] = man;
                Q.pop();
            } else {
                // nothing
            }
        }

        pos[man]++;
    }
}

int main()
{
    freopen("test.in","r",stdin);

    cin >> t;
    for (ti = 1; ti <= t; ti++) {
        cin >> n;

        for (i = 1; i <= n; i++) {
            coup[0][i] = coup[1][i] = 0;
            ord[0][i].clear();
            ord[1][i].clear();
            who[i].clear();
        }

        c1 = c2 = 0;
        for (i = 1; i <= 2 * n; i++) {
            cin >> aux;
            if ('a' <= aux[0] && aux[0] <= 'z') {
                id[aux[0]] = ++c1;
                name[0][c1] = aux[0];
            } else {
                id[aux[0]] = ++c2;
                name[1][c2] = aux[0];
            }
        }

        for (i = 1; i <= 2 * n; i++) {
            cin >> aux;
            if ('a' <= aux[0] && aux[0] <= 'z') {
                for (j = 1; j <= n; j++)
                    ord[0][ id[aux[0]] ].pb(id[aux[j + 1]]);
            } else {
                for (j = 1; j <= n; j++)
                    ord[1][ id[aux[0]] ].pb(id[aux[j + 1]]);
            }
        }

        solve();

        ans.clear();
        for (i = 1; i <= n; i++)
            ans.pb(mp(name[0][i], name[1][ coup[0][i] ]));

        sort(ans.begin(), ans.end());
        for (auto e : ans)
            cout << e.first << ' ' << e.second << '\n';


        if (ti != t) cout << '\n';
    }


    return 0;
}

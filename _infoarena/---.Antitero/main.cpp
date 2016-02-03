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

#define maxX 111
#define maxN 13
#define maxP 23

int x, n, i, j, p, v, a, b;
vector<int> list[maxX];
vector<int> target[maxX];

int locked[maxX];
bool us[maxN][maxX];

int start[maxN];
int dest[maxN];
queue< pair<int, int> > Q;

vector< vector<int> > op;
int where[maxN];
vector<int> enemy[maxX];

void _move(int sol, int pos) {
    if (pos != where[sol])
        op.pb({'M' + 0, sol, pos});
    where[sol] = pos;
}

void _kill(int sol, int ene) {
    op.pb({'E' + 0, sol, ene});
}

void add_global_place(int pos) {
    locked[pos]--;
    if (locked[pos] == 0)
        for (int i = 1; i <= n; i++)
            Q.push(mp(i, pos));
}

void dfs(int sol, int pos) {
    us[sol][pos] = true;

    for (auto to : target[pos]) {
        if (enemy[to].empty()) continue;

        for (auto boss : enemy[to]) {

            _move(sol, pos);
            _kill(sol, boss);

            add_global_place(to);
            for (auto e_to : target[to])
                add_global_place(e_to);

        }
        enemy[to].clear();
    }

    for (auto to : list[pos])
        if (locked[to] == 0 && us[sol][to] == false)
            dfs(sol, to);
}

int main()
{
    freopen("antitero.in","r",stdin);
    freopen("antitero.out","w",stdout);

    scanf("%d%d%d", &x, &n, &p);
    for (i = 1; i <= x; i++) {
        for (j = 1; j <= x; j++) {
            scanf("%d", &v);
            if (v) list[i].pb(j);
        }
    }

    for (i = 1; i <= n; i++) {
        scanf("%d%d", &v, &dest[i]);
        start[i] = v;
        Q.push(mp(i, v));

        where[i] = v;
    }

    for (i = 1; i <= p; i++) {
        scanf("%d", &v);
        enemy[v].pb(i);

        locked[v]++;
    }

    while (scanf("%d%d", &a, &b) == 2) {
        target[a].pb(b);
        if (locked[a])
            locked[b] += enemy[a].size();
    }

    while (!Q.empty()) {
        auto now = Q.front(); Q.pop();
        int sol = now.first;
        int pos = now.second;

        if (us[sol][pos]) continue;

        bool found = (pos == start[sol]);
        for (auto from : list[pos])
            found |= us[sol][from];

        if (!found) continue;
        dfs(sol, pos);
    }

    for (i = 1; i <= n; i++) {
        if (us[i][ dest[i] ] == false) {
            printf("Mission aborted");
            return 0;
        }

        _move(i, dest[i]);
    }

    printf("Success\n");
    for (auto comm : op)
        printf("%c %d %d\n", comm[0], comm[1], comm[2]);

    cerr << "Comm " << op.size();

    return 0;
}

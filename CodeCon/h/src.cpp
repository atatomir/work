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

//#define debug(x) ;
#define debug(x) cerr << #x << " = " << x << "\n";

ostream& operator<<(ostream& cerr, vector<ll> aux) {
    cerr << "[";
    for (auto e : aux) cerr << e << ' ';
    cerr << "]";
    return cerr;
}

const int maxN = 100011;

int n, m, i, x, y, z;
vector< pair<int, int> > list[maxN];
vector< pair<int, pair<int, int> > > ord;
int dad[maxN];

const int maxLog = 22;
int  j, lvl[maxN];
int up[maxLog][maxN], val[maxLog][maxN];
int sol = 0;


int Find(int x) {
    if (dad[x] == x) return dad[x];
    dad[x] = Find(dad[x]);
    return dad[x];
}

bool Merge(int x, int y) {
    x = Find(x); 
    y = Find(y);
    if (x == y) return false;

    dad[x] = y;
    return true; 
}

void dfs(int node, int root) {
    for (auto e : list[node]) {
        if (e.first == root) continue;
        lvl[e.first] = lvl[node] + 1;
        up[0][e.first] = node;
        val[0][e.first] = e.second;
        dfs(e.first, node);
    }
}

int go_up(int x, int cnt) {
    for (int i = 0; cnt > 0; i++, cnt >>= 1)
        if (cnt & 1)
            sol = max(sol, val[i][x]), x = up[i][x]; 

    return x;
}

int solve(int x, int y) {
    if (lvl[x] > lvl[y]) swap(x, y);
    sol = 0;
    y = go_up(y, lvl[y] - lvl[x]);

    if (x == y) return sol;
    for (int i = maxLog - 1; i >= 0; i--) {
        if (up[i][x] == up[i][y]) continue;
        sol = max(sol,val[i][x]);
        sol = max(sol, val[i][y]);
        x = up[i][x];
        y = up[i][y];
    } 
    sol = max(sol, val[0][x]);
    sol = max(sol, val[0][y]);
    return sol;
} 

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) dad[i] = i;
    for (i = 1; i <= m; i++) {
        scanf("%d%d%d", &x, &y, &z);
        ord.pb(mp(z, mp(x, y)));
    }


    sort(ord.begin(), ord.end());
    for (auto e : ord) {
        if (Merge(e.second.first, e.second.second)) {
            list[e.second.first].pb(mp(e.second.second, e.first));
            list[e.second.second].pb(mp(e.second.first, e.first));
        }
    }

    dfs(1, 0);
    for (i = 1; i < maxLog; i++) 
        for (j = 1; j <= n; j++)
            up[i][j] = up[i - 1][up[i - 1][j]],
            val[i][j] = max(val[i - 1][j], val[i - 1][up[i - 1][j]]);


    int q;
    scanf("%d", &q);
    for (i = 1; i <= q; i++) {
        scanf("%d%d", &x, &y);
        if (x == y) 
            printf("0\n");
        else
            printf("%d\n", solve(x, y));
    }


    return 0;
}

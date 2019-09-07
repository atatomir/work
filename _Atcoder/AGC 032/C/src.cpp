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

//#define debug(x) ;
#define debug(x) cerr << #x << " = " << x << "\n";

ostream& operator<<(ostream& cerr, vector<ll> aux) {
    cerr << "[";
    for (auto e : aux) cerr << e << ' ';
    cerr << "]";
    return cerr;
}

const int maxN = 100011;

int n, m, x, y;
vector<int> adj[maxN];
int gr[maxN], dad[maxN], down[maxN], pr[maxN];
int lvl[maxN];
bool any = false;
bool can = false;
int len;

void ret(bool yes) {
    if (yes) 
        cout << "Yes";
    else
        cout << "No";
    exit(0);
}

void dfs(int node) {
    pr[node] = down[node];
    if (gr[node] > 2) down[node]++;

    for (auto to : adj[node]) {
        if (lvl[to] == 0) {
            lvl[to] = lvl[node] + 1;
            down[to] = down[node];
            dad[to] = node;
            dfs(to);
        } else {
            if (lvl[to] >= lvl[node] - 1) continue;
            if (down[node] - pr[to] < len)
                len = down[node] - pr[to];
        }
    }
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        adj[x].pb(y);
        adj[y].pb(x);
        gr[x]++; gr[y]++;
    }

    for (int i = 1; i <= n; i++) {
        if (gr[i] & 1) ret(0);
        if (gr[i] == 4) any = true;
        if (gr[i] >= 6) can = true; 
    }

    if (can) ret(1);
    if (!any) ret(0);

    len = n + 13;
    lvl[1] = 1;
    dfs(1);

    for (int i = 1; i <= n; i++)
        if (gr[i] > 2)
            len--;

    if (len < 0) ret(1);
    ret(0);


    return 0;
}

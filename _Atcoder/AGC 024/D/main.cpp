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

const int maxN = 111;

int n, x, y, i, n1, n2;
vector<int> list[maxN];
pair<int, int> best;
vector<int> way, aux;
ll colors, leaves;

bool us[maxN];
int maxi[maxN];
queue< pair<int, int> > Q;

void dfs(int node, int root, int d) {
    best = max(best, mp(d, node));
    for (auto to : list[node])
        if (to != root)
            dfs(to, node, d + 1);
}

void get_way(int node, int root, int dest) {
    aux.pb(node);

    if (node == dest) way = aux;
    for (auto to : list[node])
        if (to != root)
            get_way(to, node, dest);

    aux.pop_back();
}

ll check(ll n1, ll n2 = 0) {
    int i, j;

    memset(us, 0, sizeof(us));
    memset(maxi, 0, sizeof(maxi));
    Q.push(mp(n1, 0));
    if (n2 != 0) Q.push(mp(n2, 0));
    us[n1] = us[n2] = true;

    while (!Q.empty()) {
        int act = Q.front().first;
        int lvl = Q.front().second;
        Q.pop() + 1;

        int down = 0;
        for (auto to : list[act]) {
            if (us[to]) continue;
            down++;
            Q.push(mp(to, lvl + 1));
            us[to] = true;
        }

        maxi[lvl + 1] = max(maxi[lvl + 1], down);
    }

    ll ans = 1;
    for (i = 1; maxi[i] > 0; i++)
        ans *= 1LL * maxi[i];

    return ans * (n2 != 0 ? 2 : 1);
}

void solve() {
    int sz = way.size();
    int R;
    colors = (sz + 1) / 2;

    if (sz % 2 == 0) {
        leaves = check(way[(sz / 2) - 1], way[sz / 2]);
    } else {
        R = way[sz / 2];
        leaves = check(R);
        for (auto to : list[R])
            leaves = min(leaves, check(R, to));
    }

    printf("%lld %lld", colors, leaves);
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        list[y].pb(x);
    }

    best = mp(0, 0);
    dfs(1, 0, 1);
    n1 = best.second;

    best = mp(0, 0);
    dfs(n1, 0, 1);
    n2 = best.second;

    get_way(n1, 0, n2);

    solve();

    return 0;
}

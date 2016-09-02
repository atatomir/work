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

#define maxN 200011


int n, k, i, x, y;
vector<int> list[maxN];
vector<int> aux;
int col[maxN];
ll ans[maxN];

queue< vector<int> > Q;
int cnt[maxN], lvl[maxN];
bool us[maxN];

ll up[maxN];
int how_many[maxN];

int full, need;


int find_center(int node) {
    us[node] = true;
    cnt[node] = 1;

    for (int to : list[node]) {
        if (us[to]) continue;

        int cc = find_center(to);
        if (cc != 0) {us[node] = false; return cc;}

        cnt[node] += cnt[to];
    }

    bool all_good = (full - cnt[node] <= need);
    for (int to : list[node]) {
        if (cnt[to] > need) {
            all_good = false;
            break;
        }
    }

    us[node] = false;

    if (all_good)
        return node;
    else
        return 0;
}

void rm_edge(int s, int d) {
    static int i;

    for (i = 0; i < list[s].size(); i++) {
        if (list[s][i] == d) {
            list[s][i] = list[s].back();
            list[s].pop_back();
            return;
        }
    }
}

void dfs(int node) {
    us[node] = true;
    ans[col[node]] += 1LL * how_many[col[node]] * lvl[node] + up[col[node]];

    aux.pb(node);

    for (int to : list[node]) {
        if (us[to]) continue;

        lvl[to] = lvl[node] + 1;
        dfs(to);
    }
}

void solve(const vector<int>& nodes) {
    int i;
    int C;

    if (nodes.size() == 1) return;

    // find centroid
    for (auto e : nodes) us[e] = false;
    full = nodes.size();
    need = full / 2;
    C = find_center(nodes[0]);

    // compute dist through centroid
    for (auto e : nodes) up[col[e]] = how_many[col[e]] = 0;
    for (int to : list[C]) {
        rm_edge(to, C);
        aux.clear();

        lvl[to] = 1;
        dfs(to);

        Q.push(aux);
        for (auto e : aux) up[col[e]] += lvl[e], how_many[col[e]]++;
    }

    // compute dist to centroid
    ans[col[C]] += up[col[C]];
}

int main()
{
    freopen("kdist.in","r",stdin);
    freopen("kdist.out","w",stdout);

    scanf("%d%d", &n, &k);
    for (i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        list[y].pb(x);
    }

    for (i = 1; i <= n; i++) {
        scanf("%d", &col[i]);
    }

    aux.reserve(n);

    aux = {};
    for (i = 1; i <= n; i++) aux.pb(i);
    Q.push(aux);

    while (!Q.empty()) {
        solve(Q.front());
        Q.pop();
    }


    for (i = 1; i <= k; i++) printf("%lld\n", ans[i]);


    return 0;
}

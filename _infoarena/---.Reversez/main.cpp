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

#define maxN 300011
#define mod 666013

int n, i, sigma, cnt, dim;
int a[maxN];
vector<int> list[maxN], adj[maxN];
int id[maxN];
bool us[maxN];

ll ans, aux;


void get_equal_edges() {
    int i, j;
    int last;

    last = 0;
    for (i = 2; i <= n; i++) {
        for (j = max(i, last + 1); j - i + 1 <= a[i]; j++) {
            list[j - i + 1].pb(j);
            list[j].pb(j - i + 1);
        }

        last = max(last, i + a[i] - 1);
    }
}

void dfs(int node) {
    id[node] = cnt;
    for (auto to : list[node])
        if (id[to] == 0)
            dfs(to);
}

void dfs2(int node) {
    ll act = sigma;
    us[node] = true;

    sort(adj[node].begin(), adj[node].end());
    adj[node].resize(unique(adj[node].begin(), adj[node].end()) - adj[node].begin());

    for (auto e : adj[node])
        if (us[e])
            act--;

    aux = (aux * act) % mod;

    for (auto e : adj[node]) {
        if (us[e]) continue;
        dfs2(e);
    }
}

int main()
{
    freopen("reversez.in","r",stdin);
    freopen("reversez.out","w",stdout);

    scanf("%d%d", &n, &sigma);
    for (i = 1; i <= n; i++) scanf("%d", &a[i]);

    get_equal_edges();
    for (i = 1; i <= n; i++) {
        if (id[i]) continue;

        cnt++;
        dfs(i);
    }

    for (i = 2; i <= n; i++) {
        int p1 = a[i] + 1;
        int p2 = i + a[i];

        if (p2 <= n) {
            adj[ id[p1] ].pb( id[p2] );
            adj[ id[p2] ].pb( id[p1] );
        }
    }

    for (i = 1; i <= cnt; i++) {
        if (us[i]) continue;
        aux = 1;
        dfs2(i);
        ans = (ans + aux) % mod;
    }

    printf("%lld", ans);


    return 0;
}

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

#define maxN 200011

int n, m, i, x, y;
int v[maxN];
ll aib[maxN];

int nxt[maxN], last[maxN];
int dist[maxN];

vector< pair<int, int> > Q[maxN];
ll ans[maxN];


int zrs(int x) {
    return (x ^ (x - 1)) & x;
}

void add(int x, ll v) {
    while (x <= n) {
        aib[x] += v;
        x += zrs(x);
    }
}

ll sum(int x) {
    ll ans = 0;
    while (x > 0) {
        ans += aib[x];
        x -= zrs(x);
    }
    return ans;
}


int main()
{
    freopen("calafat.in","r",stdin);
    freopen("calafat.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++)
        scanf("%d", &v[i]);

    for (i = n; i > 0; i--) {
        nxt[i] = last[ v[i] ];
        dist[nxt[i]] = nxt[i] - i;
        last[ v[i] ] = i;

        if (nxt[i] != 0)
            add(nxt[i], dist[nxt[i]]);
    }

    for (i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        Q[x].pb(mp(y, i));
    }

    for (i = 1; i <= n; i++) {
        for (auto e : Q[i])
            ans[e.second] = sum(e.first);

        if (nxt[i] != 0)
            add(nxt[i], -dist[nxt[i]]);
    }

    for (i = 1; i <= m; i++)
        printf("%lld\n", ans[i]);



    return 0;
}

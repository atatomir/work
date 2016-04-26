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

#define maxN 100011


int n, m, i, x, y, pos;
vector<int> list[maxN];
bool alrdn[maxN];
vector<int> todo[maxN];
int gr[maxN];

ll ans;

int main()
{
    freopen("tric.in","r",stdin);
    freopen("tric.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        list[y].pb(x);
    }

    for (i = 1; i <= n; i++) todo[0].pb(i);

    while (pos >= 0) {
        if (todo[pos].empty()) {
            pos--;
            continue;
        }

        int node = todo[pos].back();
        todo[pos].pop_back();

        if (alrdn[node]) continue;
        alrdn[node] = true;
        pos++;

        ans += (1LL * gr[node] * (gr[node] - 1)) / 2LL;
        for (int to : list[node])
            if (!alrdn[to])
                todo[ ++gr[to] ].pb(to);
    }

    printf("%lld", ans);


    return 0;
}

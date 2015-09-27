#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 30111

int n, m, i, x, y;
vector<int> list[maxN];
vector< pair<int, int> > ans;
bool us[maxN];

bool dfs(int node) {
    us[node] = true;

    vector<int> aux;
    aux.clear();

    for (auto to : list[node]) {
        if (us[to]) continue;

        if (dfs(to)) aux.pb(to);
    }

    while (aux.size() > 1) {
        int n1 = aux[aux.size() - 1];
        aux.pop_back();
        int n2 = aux[aux.size() - 1];
        aux.pop_back();

        ans.pb(mp(n1, n2));
    }

    if (aux.size() == 1) {
        ans.pb(mp(aux[0], node));
        return false;
    }

    return true;
}

int main()
{
    freopen("g2mm.in","r",stdin);
    freopen("g2mm.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        list[y].pb(x);
    }

    if ( dfs(1) ) {
        cerr << "Error";
        return 0;
    }

    printf("1\n");
    for (auto e : ans) printf("%d %d\n", e.first, e.second);

    return 0;
}

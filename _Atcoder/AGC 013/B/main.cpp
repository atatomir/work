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

int n, m, i, x, y;
vector<int> list[maxN];
bool us[maxN];
vector<int> ans;

void dfs(int node) {
    us[node] = true;
    ans.pb(node);

    for (auto to : list[node]) {
        if (us[to]) continue;
        dfs(to);
        return;
    }
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        list[y].pb(x);
    }

    dfs(1);
    reverse(ans.begin(), ans.end());
    for (auto to : list[1]) {
        if (us[to]) continue;
        dfs(to);
        break;
    }

    printf("%d\n", ans.size());
    for (auto e : ans) printf("%d ", e);


    return 0;
}

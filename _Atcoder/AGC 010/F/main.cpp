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

#define maxN 3011

int n, i, x, y;
int a[maxN];
vector<int> list[maxN];
int st[maxN];

void dfs(int node, int root) {
    st[node] = 0;
    for (auto to : list[node]) {
        if (to == root) continue;
        dfs(to, node);

        if (st[to] == 0 && a[node] > a[to])
            st[node] = 1;
    }
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        list[y].pb(x);
    }

    for (i = 1; i <= n; i++) {
        dfs(i, 0);
        if (st[i] == 1) printf("%d ", i);
    }



    return 0;
}

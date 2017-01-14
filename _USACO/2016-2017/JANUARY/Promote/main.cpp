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

int n, i, x;
int v[maxN];
vector<int> list[maxN];
vector< pair<int, int> > ord;

int aib[maxN];
int ans[maxN];

int zrs(int x) {
    return (x ^ (x - 1)) & x;
}

void add(int x, int v) {
    while (x <= n) {
        aib[x] += v;
        x += zrs(x);
    }
}

int sum(int x) {
    int ans = 0;

    while (x > 0) {
        ans += aib[x];
        x -= zrs(x);
    }

    return ans;
}

void dfs(int node) {
    ans[node] = - sum(v[node]);

    for (auto to : list[node])
        dfs(to);

    ans[node] += sum(v[node]);
    add(1, +1);
    if (v[node] != n) add(v[node] + 1, -1);
}

int main()
{
    freopen("promote.in","r",stdin);
    freopen("promote.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d", &v[i]);
        ord.pb(mp(v[i], i));
    }
    for (i = 2; i <= n; i++) {
        scanf("%d", &x);
        list[x].pb(i);
    }

    sort(ord.begin(), ord.end());
    for (i = 0; i < n; i++)
        v[ ord[i].second ] = i + 1;

    dfs(1);

    for (i = 1; i <= n; i++)
        printf("%d\n", ans[i]);


    return 0;
}

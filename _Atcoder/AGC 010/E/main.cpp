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

#define maxN 2017

int n, nn, i, j;
int a[maxN];
vector<int> adj[maxN];

vector<int> ans[maxN], aux;
bool us[maxN];


int cmmdc(int a, int b) {
    if (a < b) swap(a, b);

    while (b != 0) {
        a %= b;
        swap(a, b);
    }

    return a;
}

void dfs(int node) {
    us[node] = true;

    ans[node] = {};
    sort(adj[node].begin(), adj[node].end());

    for (auto to : adj[node]) {
        if (us[to]) continue;

        dfs(to);
        aux = ans[node];
        ans[node].resize(ans[node].size() + ans[to].size());
        merge(aux.begin(), aux.end(),
              ans[to].begin(), ans[to].end(),
              ans[node].begin(), [](int a, int b)->bool const {return a > b;});
    }

    if (node != 0)
        ans[node].insert(ans[node].begin(), a[node]);
}


int main()
{
    freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) scanf("%d", &a[i]);
    sort(a + 1, a + n + 1);

    for (i = 1; i <= n; i++) {
        for (j = i + 1; j <= n; j++) {
            if (cmmdc(a[i], a[j]) != 1) {
                adj[i].pb(j);
                adj[j].pb(i);
            }
        }

        adj[0].pb(i);
        adj[i].pb(0);
    }

    dfs(0);

    for (auto e : ans[0]) printf("%d ", e);




    return 0;
}

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
vector<int> list[maxN];
int dp[maxN];

void dfs(int node) {
    if(list[node].empty()) {
        dp[node] = 0;
        return;
    }

    vector<int> aux = {};
    for (auto to : list[node]) {
        dfs(to);
        aux.pb(dp[to]);
    }

    sort(aux.begin(), aux.end());
    int vv = aux.size();

    for (auto e : aux) {
        dp[node] = max(dp[node], e + vv);
        vv--;
    }
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 2; i <= n; i++) {
        scanf("%d", &x);
        list[x].pb(i);
    }

    dfs(1);
    printf("%d", dp[1]);



    return 0;
}

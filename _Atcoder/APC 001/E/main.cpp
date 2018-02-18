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

int n, i, x, y;
vector<int> list[maxN];
int gr[maxN];

int dp[maxN], up[maxN];

void dfs(int node, int root) {
    int i;

    for (i = 0; i < list[node].size(); i++) {
        int to = list[node][i];

        if (to == root) {
            list[node][i] = list[node].back();
            list[node].pop_back();
            i--;
            continue;
        }

        dfs(to, node);
    }

    if (list[node].empty()) {
        dp[node] = 1;
        up[node] = 0;
        return;
    }

    if (list[node].size() == 1) {
        int to = list[node][0];
        up[node] = up[to];
        dp[node] = dp[to];
        return;
    }

    up[node] = n + 1;
    for (auto to : list[node])
        dp[node] += dp[to];

    int base = dp[node];

    for (auto to : list[node])
        dp[node] = min(dp[node], base - dp[to] + up[to]);
}

int main()
{
    freopen("test.in","r",stdin);

    cin >> n;
    for (i = 1; i < n; i++) {
        cin >> x >> y;
        x++; y++;

        list[x].pb(y);
        list[y].pb(x);
        gr[x]++; gr[y]++;
    }

    for (i = 1; i <= n && gr[i] <= 2; i++);
    if (i == n) {
        cout << 1;
        return 0;
    }

    dfs(i, 0);
    cout << dp[i];


    return 0;
}

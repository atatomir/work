#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 100011

int n, i, x, y, t;
vector<int> list[maxN];
bool us[maxN];
int dp[maxN];

bool cmp(const int a, const int b) {
    return dp[a] > dp[b];
}

void dfs(int node) {
    int daddy = 0;
    us[node] = true;
    dp[node] = 0;

    for (auto to : list[node]) {
        if (us[to]) {
            daddy = to;
            continue;
        }
        dfs(to);
    }

    int pos = 1;
    sort(list[node].begin(), list[node].end(), cmp);
    for (i = 0; i < list[node].size(); i++, pos++)
        if (list[node][i] != daddy)
            dp[node] = max(dp[node], dp[ list[node][i] ] + pos);
        else
            pos--;
}

int main()
{
    freopen("zvon.in","r",stdin);
    freopen("zvon.out","w",stdout);

    for (scanf("%d", &t); t > 0; t--) {
        scanf("%d", &n);
        for (i = 1; i <= n; i++) list[i].clear();

        for (i = 1; i < n; i++) {
            scanf("%d%d", &x, &y);
            list[x].pb(y);
            list[y].pb(x);
        }

        memset(us, 0, sizeof(us));
        dfs(1);
        printf("%d\n", dp[1]);
    }



    return 0;
}

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 50011
#define mod 666013

int n, m, i, x, y, v, k, ans;
vector< pair<int, int> > list[maxN];
bool us[maxN];
int dp[maxN];

bool allRight;

int norm(int x) {
    while (x >= k) x -= k;
    while (x <  0) x += k;
    return x;
}

void dfs(int node) {
    us[node] = true;

    for (auto to : list[node]) {
        if (us[to.first]) {
            if (dp[to.first] != norm(dp[node] + to.second)) {
                allRight = false;
                return;
            }
        } else {
            dp[to.first] = norm(dp[node] + to.second);
            dfs(to.first);
        }
    }
}

int main()
{
    freopen("restrictii.in","r",stdin);
    freopen("restrictii.out","w",stdout);

    scanf("%d%d%d", &n, &m, &k);
    for (i = 1; i <= m; i++) {
        scanf("%d%d%d", &x, &y, &v);
        list[x - 1].pb(mp(y, v));
        list[y].pb(mp(x - 1, -v));
    }

    allRight = true;
    ans = -1;
    for (i = 0; i <= n; i++) {
        if (!us[i]) {
            dfs(i);
            ans++;
        }
        if (allRight == false) break;
    }

    if (allRight == false) {
        printf("0");
        return 0;
    }

    long long sol = 1;
    for (; ans > 0; ans--) sol = (sol * k) % mod;
    printf("%lld", sol);

    return 0;
}

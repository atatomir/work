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

const int maxN = 300011;
const int maxK = 5;

int n, m, k, i, limit, x, y;
int col[maxN];
vector<int> list[maxN];
ll dp[1 << maxK][maxN];
ll ans;


int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d%d%d", &n, &m, &k);
    for (i = 1; i <= n; i++) {
        scanf("%d", &x);
        col[i] = x;
        dp[1 << (x - 1)][i] = 1;
    }
    for (i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        list[y].pb(x);
    }

    limit = 1 << k;
    for (int conf = 1; conf < limit; conf++) {
        for (i = 1; i <= n; i++) {
            if (dp[conf][i] == 0) continue;
            ans += dp[conf][i];

            for (auto to : list[i]) {
                if (conf & (1 << (col[to] - 1))) continue;
                dp[conf | (1 << (col[to] - 1))][to] += dp[conf][i];
            }
        }
    }

    cout << ans - n;





    return 0;
}

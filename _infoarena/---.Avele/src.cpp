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

//#define debug(x) ;
#define debug(x) cerr << #x << " = " << x << "\n";

ostream& operator<<(ostream& cerr, vector<ll> aux) {
    cerr << "[";
    for (auto e : aux) cerr << e << ' ';
    cerr << "]";
    return cerr;
}

const int maxN = 100011;
const int maxH = 88;
const ll limit = 100000LL * 1000000000LL * 10LL;

ll n, cadd, crem, cnt, i;
ll son[maxN][2];
ll to_add[maxN];

ll dp[maxN][maxH];

void upd(ll& a, ll b) {
    if (a > b) a = b;
}

void dfs(int node) {
    if (node == 0) return;
    int s1 = son[node][0];
    int s2 = son[node][1];

    dfs(s1);
    dfs(s2);
    int i, j;

    for (i = 0; i <= cnt; i++) dp[node][i] = limit;
    dp[node][0] = dp[s1][0] + dp[s2][0] + crem;

    for (i = 0; i < cnt; i++) {
        for (j = max(0, i - 1); j <= i + 1 && j < cnt; j++) {
            upd(dp[node][max(i, j) + 1], dp[s1][i] + dp[s2][j]);
        }
    }
}

int main()
{
    freopen("avele.in","r",stdin);
    freopen("avele.out","w",stdout);

    scanf("%lld%lld%lld", &n, &cadd, &crem);
    for (i = 1; i <= n; i++)
        scanf("%lld%lld", &son[i][0], &son[i][1]);

    to_add[0] = 0;
    to_add[1] = 1;
    for (cnt = 2; true; cnt++) {
        to_add[cnt] = to_add[cnt - 1] + to_add[cnt - 2] + 1LL;
        if (to_add[cnt] * cadd > limit) break;
    }

    for (i = 0; i <= cnt; i++) 
        dp[0][i] = to_add[i] * cadd;

    dfs(1);

    ll ans = limit;
    for (i = 0; i <= cnt; i++) upd(ans, dp[1][i]);
    printf("%lld", ans);


    return 0;
}

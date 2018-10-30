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

const int maxN = 250011;
const ll inf = 1LL << 60;

ll n, k, i, x, y, z, cost;
vector< pair<ll, ll> > list[maxN];
pair<ll, ll> dp[maxN][2];

void clr(vector< pair<ll, ll> >& data, ll x) {
    for (int i = 0; i < data.size(); i++) {
        if (data[i].first == x) {
            data[i] = data.back();
            data.pop_back();
            return;
        }
    }
}

void add(pair<ll, ll>& a, pair<ll, ll>& b) {
    a.first += b.first;
    a.second += b.second;
}

void dfs(int node, int root) {
    clr(list[node], root);

    if (list[node].empty()) {
        dp[node][0] = dp[node][1] = mp(0, 0);
        return;
    }

    dp[node][0] = dp[node][1] = mp(0, 0);
    pair<ll, ll> best = mp(-inf, -inf);
    for (auto to : list[node]) {
        dfs(to.first, node);

        add(dp[node][0], dp[to.first][1]);
        add(dp[node][1], dp[to.first][1]);

        pair<ll, ll> aux = mp(dp[to.first][0].first - dp[to.first][1].first + to.second - cost,
                              dp[to.first][0].second - dp[to.first][1].second + 1);
        best = max(best, aux);
    }
    add(dp[node][1], best);
    dp[node][1] = max(dp[node][1], dp[node][0]);
}

pair<ll, ll> check(ll _cost) {
    cost = _cost;
    dfs(1, 0);

    return max(dp[1][1], dp[1][0]);
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%lld%lld", &n, &k);
    for (i = 1; i < n; i++) {
        scanf("%lld%lld%lld", &x, &y, &z);
        list[x].pb(mp(y, z));
        list[y].pb(mp(x, z));
    }

    ll ans = -(1LL << 42);
    if (check(ans).second < k) {
        printf("Impossible");
        return 0;
    }

    for (ll step = 1LL << 42; step > 0; step >>= 1)
        if (check(ans + step).second >= k) 
            ans += step;

    ll sol = check(ans).first + ans * k;
    printf("%lld", sol);


    return 0;
}

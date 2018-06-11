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

const int maxN = 53;
const int maxSz = 50 * 50 * 50;
const ll inf = 1LL << 60;

struct item {
    ll cost, val, limit;

    bool operator<(const item& who)const {
        return val * who.cost > who.val * cost;
    }
};

int n, i, x;
int cnt[maxN];
ll X, D;
ll m[maxN];
vector<int> list[maxN];
vector<item> data;

ll dp[maxN * maxN * maxN];
deque< pair<ll, ll> > Q;

void dfs(int node) {
    cnt[node] = 1;

    for (auto to : list[node]) {
        dfs(to);
        cnt[node] += cnt[to];
        m[node] += m[to];
    }

    if (node == 1)
        data.pb({m[node], cnt[node], inf});
    else
        data.pb({m[node], cnt[node], D});
}

ll greedy(ll sz, const vector<item>& bag) {
    ll ans = 0;
    ll aux;

    for (auto act : bag) {
        aux = min(act.limit, sz / act.cost);
        ans += aux * act.val;
        sz -= aux * act.cost;
    }

    return ans;
}

ll small_knapsack( vector<item>& small_bag,  vector<item>& big_bag) {
    ll maxi = 0;
    ll i, j, bg;

    dp[0] = 0;
    for (i = 1; i <= maxSz; i++) dp[i] = inf;

    /*reverse(small_bag.begin(), small_bag.end());
    while (small_bag.size() > 1) small_bag.pop_back();

    swap(big_bag[0], big_bag[2]);*/

    for (auto act : small_bag) {
        maxi += act.val * act.limit;

        for (bg = 0; bg < act.val; bg++) {
            while (!Q.empty()) Q.pop_back();

            for (i = bg; i <= maxi; i += act.val) {

                while (!Q.empty()) {
                    if (Q.back().first <= dp[i] - act.cost * (i / act.val)) break;
                    Q.pop_back();
                }
                Q.push_back(mp(dp[i] - act.cost * (i / act.val), i));

                if (i - Q.front().second > act.limit * act.val) Q.pop_front();

                dp[i] = Q.front().first + act.cost * (i / act.val);
            }

        }
    }

    ll ans = 0;
    for (i = 0; i <= maxi; i++) {
        if (dp[i] <= X)
            ans = max(ans, i + greedy(X - dp[i], big_bag));
    }

    return ans;
}

ll knapsack(vector<item> base, int max_sz) {
    vector<item> small_bag, big_bag;

    small_bag = big_bag = {};
    for (auto e : base) {
        if (e.limit <= max_sz) {
            small_bag.pb(e);
        } else {
            small_bag.pb({e.cost, e.val, max_sz});
            big_bag.pb({e.cost, e.val, e.limit - max_sz});
        }
    }

    sort(big_bag.begin(), big_bag.end());
    return small_knapsack(small_bag, big_bag);
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%lld%lld", &n, &X, &D);
    scanf("%lld", &m[1]);
    for (i = 2; i <= n; i++) {
        scanf("%lld%d", &m[i], &x);
        list[x].pb(i);
    }

    dfs(1);
    ll ans = knapsack(data, 50);

    printf("%lld", ans);

    return 0;
}

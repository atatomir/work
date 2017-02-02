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

#define maxN 4000011
#define inf (1LL << 61)
#define mod 1000000007

int t, ti;
ll n, i;
ll O1, AO, BO, CO, DO;
ll R1, AR, BR, CR, DR;

ll O[maxN], R[maxN];

vector< pair<ll, ll> > list[maxN];
ll dist[maxN];
priority_queue< pair<ll, ll>, vector< pair<ll, ll> >, greater< pair<ll, ll> > > H;
ll ans;

int who[maxN];
ll l[maxN], suml[maxN], sumsuml[maxN];
ll r[maxN], sumr[maxN], sumsumr[maxN];
ll sumin[maxN];

ll invtwo;
ll whole;

ll poww(ll a, ll b) {
    ll ans = 1;

    while (b > 0) {
        if (b & 1) ans = (ans * a) % mod;
        b >>= 1;
        a = (a * a) % mod;
    }

    return ans;
}

ll out_dist(ll x, ll y) {
    if (x > y) y += n;
    return suml[y - 1] - suml[x - 1];
}

ll in_dist(ll x, ll y) {
    return R[ who[x] ] + R[ who[y] ];
}

ll move_le(ll le, ll ri) {
    return (sumsuml[ri - 1] - sumsuml[le - 1]) - (suml[le - 1] * (ri - le));
}

ll move_ri(ll le, ll ri) {
    return (sumsumr[le + 1] - sumsumr[ri + 1]) - (sumr[ri + 1] * (ri - le));
}

void solve() {
    ll i;

    for (i = 1; i <= n + 1; i++) list[i].clear(), dist[i] = inf;
    for (i = 1; i <= n; i++) {
        int to = (i == n ? 1 : i + 1);

        list[i].pb(mp(to, O[i]));
        list[to].pb(mp(i, O[i]));
    }

    for (i = 1; i <= n; i++) {
        list[i].pb(mp(n + 1, R[i]));
        list[n + 1].pb(mp(i, R[i]));
    }

    dist[n + 1] = 0;
    H.push(mp(0, n + 1));

    while (!H.empty()) {
        ll dst = H.top().first;
        ll node = H.top().second;
        H.pop();

        if (dist[node] != dst) continue;

        for (auto to : list[node]) {
            if (dist[node] + to.second < dist[to.first]) {
                dist[to.first] = dist[node] + to.second;
                H.push(mp(dist[to.first], to.first));
            }
        }
    }

    ans = 0;
    whole = 0;

    for (i = 1; i <= n; i++) {
        R[i] = dist[i];
        ans = (ans + 2LL * R[i]) % mod;

        whole += O[i];
    }

    memset(l, 0, sizeof(l));
    memset(suml, 0, sizeof(suml));
    memset(sumsuml, 0, sizeof(sumsuml));

    memset(r, 0, sizeof(r));
    memset(sumr, 0, sizeof(sumr));
    memset(sumsumr, 0, sizeof(sumsumr));

    memset(sumin, 0, sizeof(sumin));

    for (i = 1; i <= n; i++) who[i] = who[i + n] = i;

    for (i = 1; i <= 2 * n; i++) {
        sumin[i] = R[ who[i] ];
        sumin[i] += sumin[i - 1];
    }

    for (i = 1; i < 2 * n; i++) {
        l[i] = O[ who[i] ];
        suml[i] = l[i] + suml[i - 1];
        sumsuml[i] = sumsuml[i - 1] + suml[i];
    }

    for (i = 2 * n; i > 1; i--) {
        r[i] = O[ who[i - 1] ];
        sumr[i] = r[i] + sumr[i + 1];
        sumsumr[i] = sumsumr[i + 1] + sumr[i];
    }

    for (i = 1; i <= n; i++) {
        ll le = i;
        ll ri = i + n;
        ll limit = le;

        for (ll step = 1 << 20; step > 0; step >>= 1)
            if (limit + step < ri)
                if (out_dist(i, limit + step) <= out_dist(limit + step, i + n))
                    limit += step;

        for (ll step = 1 << 20; step > 0; step >>= 1)
            if (le + step <= limit)
                if (out_dist(i, le + step) < in_dist(i, le + step))
                    le += step;

        for (ll step = 1 << 20; step > 0; step >>= 1)
            if (ri - step > limit)
                if (out_dist(ri - step, i + n) < in_dist(ri - step, i + n))
                    ri -= step;

        ans += move_le(i, le) % mod;
        ans += move_ri(ri, i + n) % mod;
        ans += (sumin[ri - 1] - sumin[le]) % mod;
        ans += ((ri - le - 1) * R[ who[i] ]) % mod;
        ans %= mod;
    }

    ans = (ans * invtwo) % mod;

}

int main()
{
    freopen("input.in","r",stdin);
    freopen("output.out", "w", stdout);

    invtwo = poww(2, mod - 2);

    scanf("%d", &t);
    cerr << "Solve " << t << " tests\n";

    for (ti = 1; ti <= t; ti++) {
        cerr << "#" << ti << '\n';

        scanf("%lld", &n);
        scanf("%lld%lld%lld%lld%lld", &O1, &AO, &BO, &CO, &DO);
        scanf("%lld%lld%lld%lld%lld", &R1, &AR, &BR, &CR, &DR);

        O[1] = O1;
        for (i = 2; i <= n; i++)
            O[i] = ((AO * O[i - 1] + BO) % CO) + DO;

        R[1] = R1;
        for (i = 2; i <= n; i++)
            R[i] = ((AR * R[i - 1] + BR) % CR) + DR;

        solve();

        printf("Case #%d: %lld\n", ti, ans);
    }


    return 0;
}

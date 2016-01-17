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

#define maxN 100011
#define ll long long
#define pii pair<ll, int>

struct wash_cmp {
    bool operator()(const pii& a, const pii& b)const {
        return a.first > b.first;
    }
};

struct dry_cmp {
    bool operator()(const ll& a, const ll& b)const {
        return a > b;
    }
};


ll t, test, n, i, m;
ll D, L;
ll W[maxN];

priority_queue<ll, vector<ll>, dry_cmp> work_dry;
priority_queue<pii, vector<pii>, wash_cmp> work_wash;

ll solve() {
    int i, j;
    ll ans = 0;

    while (!work_dry.empty()) work_dry.pop();
    while (!work_wash.empty()) work_wash.pop();

    m = min(m, L);

    for (i = 1; i <= n; i++)
        work_wash.push(mp(W[i] + D, i));
    for (i = 1; i <= m; i++)
        work_dry.push(D);

    for (i = 1; i <= L; i++) {
        pii now_wash = work_wash.top();
        work_wash.pop();

        ll now_dry = work_dry.top();
        work_dry.pop();

        ll time = max(now_wash.first, now_dry);
        ans = max(ans, time);

        work_wash.push(mp(now_wash.first + W[now_wash.second], now_wash.second));
        work_dry.push(time + D);
    }

    return ans;
}

int main()
{
    freopen("input.in","r",stdin);
    freopen("output.out","w",stdout);

    for (scanf("%d", &t), test = 1; test <= t; test++) {
        cerr << "Solving " << test << '\n';

        scanf("%lld %lld %lld %lld", &L, &n, &m, &D);
        for (i = 1; i <= n; i++)
            scanf("%lld", &W[i]);

        printf("Case #%d: %lld\n", test, solve());
    }

    return 0;
}

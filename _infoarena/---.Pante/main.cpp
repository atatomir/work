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

#define maxN 200011
#define eps 1e-7

struct frac {
    ll a, b;
    double ang;

    bool operator<(const frac& who)const {
        return ang < who.ang;
    }

    bool operator==(const frac& who)const {
        return -eps <= ang - who.ang && ang - who.ang <= eps;
    }
};

int n, i;
ll A, B, C, D;
ll x, y;
pair<frac, frac> F[maxN];
vector< frac > ord;

int aib[maxN];
ll ans;


int zrs(int x) {
    return (x ^ (x - 1)) & x;
}

void add(int pos, int v) {
    while (pos <= n) {
        aib[pos] += v;
        pos += zrs(pos);
    }
}

int sum(int pos) {
    int ans = 0;
    while(pos > 0) {
        ans += aib[pos];
        pos -= zrs(pos);
    }
    return ans;
}



int main()
{
    freopen("pante.in","r",stdin);
    freopen("pante.out","w",stdout);

    scanf("%d%lld%lld%lld%lld", &n, &A, &B, &C, &D);
    for (i = 1; i <= n; i++) {
        scanf("%lld%lld", &x, &y);
        F[i].first = {x * A - y * B, A};
        F[i].second = {x * C - y * D, C};
        F[i].first.ang = 1.00 * F[i].first.a / F[i].first.b;
        F[i].second.ang = 1.00 * F[i].second.a / F[i].second.b;
        ord.pb(F[i].second);
    }

    sort(F + 1, F + n + 1, [](const pair<frac, frac>& a, const pair<frac, frac>& b)->bool const {
        if (a.first == b.first)
            return b.second < a.second;
        return a.first < b.first;
    });

    sort(ord.begin(), ord.end());
    ord.resize(unique(ord.begin(), ord.end()) - ord.begin());

    for (i = 1; i <= n; i++) {
        auto act = F[i];
        int pos = lower_bound(ord.begin(), ord.end(), act.second) - ord.begin() + 1;

        ans += 1LL * (i - 1 - sum(pos - 1));
        add(pos, +1);
    }

    printf("%lld", ans);
    cerr << ans;


    return 0;
}

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

#define inf 1LL << 50

int t, ti;
ll n, m, k;

ll solve(ll n, ll m) {

    if (m < 2 * k + 3) return inf;

    if (k + 1 <= n && n <= 2 * k) return 2;
    if (2 * k + 1 <= n && n <= 3 * k) return 3;
    if (n >= 2 * k + 1) return 4;

    return inf;
}

ll solve2(ll n, ll m) {

    if (m < 5) return inf;
    if (n == 2) return 2;
    if (n == 3) return 3;
    if (n == 4) return 4;
    if (n >= 3) return 5;

    return inf;
}

int main()
{
    freopen("input.in","r",stdin);
    freopen("output.out","w",stdout);

    scanf("%d", &t);
    cerr << "Solve " << t << "cases\n";

    for (ti = 1; ti <= t; ti++) {
        cerr << "#" << ti << "\n";
        scanf("%lld%lld%lld", &n, &m, &k);


        ll ans = min(solve(n, m), solve(m, n));
        if (ans >= inf)
            ans = -1;

        if (k == 1)
            ans = min(solve2(n, m), solve2(m, n));
        if (ans >= inf)
            ans = -1;

        printf("Case #%d: %lld\n", ti, ans);
    }


    return 0;
}

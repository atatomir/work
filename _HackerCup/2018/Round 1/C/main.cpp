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

const int maxN = 200011;
const ll inf = 1LL << 30;

int t, ti;
ll n, m, H[maxN], W, X, Y, Z, A, B, U, D, i, j;
ll up[maxN], down[maxN];

void gen_input() {
    int i;

    for (i = 3; i <= n; i++) {
        H[i] = (W * H[i - 2] + X * H[i - 1] + Y) % Z;
    }

    for (i = 1; i <= n; i++) {
        up[i] = down[i] = inf;
        H[i] <<= 1;
    }
}

void add_runner() {
    int i;

    if (A < B) {
        for (i = A; i < B; i++) {
            up[i] = min(up[i], U);
            down[i] = min(down[i], D);
        }
    } else {
        for (i = B; i < A; i++) {
            down[i] = min(down[i], U);
            up[i] = min(up[i], D);
        }
    }
}

bool check(ll allow) {
    ll i, a, b;

    a = H[1] - allow;
    b = H[1] + allow;

    for (i = 1; i < n; i++) {
        a -= down[i];
        b += up[i];

        a = max(a, 0LL);

        a = max(a, H[i + 1] - allow);
        b = min(b, H[i + 1] + allow);

        if (a > b) return false;
    }

    return true;
}

ll solve() {
    ll ans = -1;

    for (ll step = 1LL << 25; step > 0; step >>= 1) {
        if (!check(ans + step))
            ans += step;
    }

    return ans + 1;
}

int main()
{
    freopen("input.in","r",stdin);
    freopen("output.out", "w", stdout);

    scanf("%d", &t);
    cerr << "Solve " << t << " tests\n";

    for (ti = 1; ti <= t; ti++) {
        cerr << "#" << ti << '\n';

        scanf("%lld%lld", &n, &m);
        scanf("%lld%lld%lld%lld%lld%lld", &H[1], &H[2], &W, &X, &Y, &Z);

        gen_input();
        for (i = 1; i <= m; i++) {
            scanf("%lld%lld%lld%lld", &A, &B, &U, &D);
            U <<= 1;
            D <<= 1;
            add_runner();

            //cerr << check(47) << ' ';
        }

        ll ans = solve();

        printf("Case #%d: %lld.%lld00000\n", ti, ans / 2, (ans % 2) * 5);
    }


    return 0;
}

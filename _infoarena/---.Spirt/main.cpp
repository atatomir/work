#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stack>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 100011
#define mod 666013

ll n, m, i;
ll mm, mone;

ll vv(ll a) {
    return a % mod;
}

struct el {
    ll s, d;
    bool open;

    void combine(const el who) {
        ll s1 = s;
        ll d1 = d;
        ll s2 = who.s;
        ll d2 = who.d;

        s = d = 0;

        //! same, same
        s += 0;
        d += vv(vv(s1 * s2) * vv((m - 1) * mm));

        if (s >= mod) s -= mod;
        if (d >= mod) d -= mod;

        //! same, diff
        s += vv(vv(s1 * d2) * mm);
        d += vv(vv(s1 * d2) * vv( (m - 2) * mm ));

        if (s >= mod) s -= mod;
        if (d >= mod) d -= mod;

        //! diff, same
        s += vv(vv(d1 * s2) * mm);
        d += vv(vv(d1 * s2) * vv( (m - 2) * mm ));

        if (s >= mod) s -= mod;
        if (d >= mod) d -= mod;

        //! diff, diff
        s += vv(vv(d1 * d2) * vv( (m - 2) * vv(mm * mone)));
        d += vv(vv(vv(d1 * d2) * vv( (m - 2) * (m - 2) )) * vv(mm * mone));
        d += vv(d1 * d2) * mm;

        s %= mod; d %= mod;
    }
};


char s[maxN];

stack<el> S;
el act;


ll poww(ll a, ll b) {
    ll ans = 1;

    while (b) {
        if (b & 1) ans = (ans * a) % mod;
        b >>= 1;
        a = (a * a) % mod;
    }

    return ans;
}

int main()
{
    freopen("spirt.in","r",stdin);
    freopen("spirt.out","w",stdout);

    scanf("%lld%lld\n%s", &n, &m, s + 1);

    mm = poww(m, mod - 2);
    mone = poww(m - 1, mod - 2);

    for (i = 1; i <= n; i++) {
        if (s[i] == '(') {
            S.push({0, 0, true});
            continue;
        }

        if (S.top().open) {
            S.pop();
            S.push({0, ( m * (m - 1) ) % mod, false});
            continue;
        }

        act = S.top(); S.pop();
        while (S.top().open == false) {
            act.combine(S.top());
            S.pop();
        }

        S.pop();

        //! add act
        act.d = vv(vv(act.s * (m - 1)) * (m - 2)) + vv(act.d * vv( mod + vv((m - 1) * (m - 1)) - (m - 2) ));
        act.d %= mod;
        act.s = 0;

        S.push(act);
    }

    act = S.top(); S.pop();
    while (!S.empty()) {
        act.combine(S.top());
        S.pop();
    }

    printf("%lld", (act.s + act.d) % mod );

    return 0;
}

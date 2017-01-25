#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

int t, ti;
ll n, i;
ll x1, ax, bx, cx;
ll h1, ah, bh, ch;
set< pair<ll, ll> > S;

bool good(pair<ll, ll> base, pair<ll, ll> act) {
    static ll delta;

    delta = base.first - act.first;
    if (delta < 0) delta = -delta;

    if (base.second - delta >= act.second) return false;
    return true;
}

double inte(pair<ll, ll> p1, pair<ll, ll> p2) {
    static ll posl, posr;
    static double area1, area2, pos, delta, dif;

    if (p1.first > p2.first) swap(p1, p2);
    posl = p1.first + p1.second;
    posr = p2.first - p2.second;

    if (posl <= posr) {
        area1 = 0.50 * p1.second * p1.second;
        area2 = 0.50 * p2.second * p2.second;
        return area1 + area2;
    }

    delta = p2.first - p1.first;
    dif = p2.second - p1.second;
    if (dif < 0) dif = -dif;

    if (p1.second > p2.second)
        pos = 1.00 * dif + (delta - dif) / 2;
    else
        pos = 0.50 * (delta - dif);

    area1 = 0.5 * pos * (p1.second + p1.second - pos);
    area2 = 0.5 * (delta - pos) * (p2.second + p2.second - (delta - pos));
    return area1 + area2;
}

double rm(pair<ll, ll> who) {
    set< pair<ll, ll> >::iterator le, ri, me;

    me = le = ri = S.lower_bound(who);
    le--; ri++;

    double area1 = inte(*le, who);
    double area2 = inte(*ri, who);
    double area3 = inte(*le, *ri);
    S.erase(me);

    return area3 - area1 - area2;
}

double solve() {
    ll i;
    ll x, h;
    double ans, aux;
    set< pair<ll, ll> >::iterator le, ri, we;
    pair<ll, ll> pp;

    S.clear();
    S.insert({-100000000, 0});
    S.insert({+100000000, 0});

    x = x1;
    h = h1;
    ans = 0.00;
    aux = 0.00;

    for (i = 1; i <= n; i++) {

        pp = mp(x, h);
        le = ri = S.lower_bound(pp);
        le--;

        if (good(*le, pp) && good(*ri, pp)) {
            // we need to add it
            aux -= inte(*le, *ri);
            aux += inte(*le, pp);
            aux += inte(pp, *ri);
            S.insert(pp);

            while (true) {
                we = S.lower_bound(pp);
                ri = we; ri++;

                if (good(pp, *ri)) break;
                aux += rm(*ri);
            }

            while (true) {
                we = S.lower_bound(pp);
                le = we; le--;

                if (good(pp, *le)) break;
                aux += rm(*le);
            }
        }


        ans += aux;
        x = ((ax * x + bx) % cx) + 1;
        h = ((ah * h + bh) % ch) + 1;
    }

    return ans;
}

int main()
{
    freopen("input.in","r",stdin);
    freopen("output.out","w",stdout);

    scanf("%d", &t);
    cerr << "Solve " << t << " tests\n";

    for (ti = 1; ti <= t; ti++) {
        cerr << "#" << ti << '\n';

        scanf("%lld", &n);
        scanf("%lld%lld%lld%lld", &x1, &ax, &bx, &cx);
        scanf("%lld%lld%lld%lld", &h1, &ah, &bh, &ch);

        printf("Case #%d: %.10lf\n", ti, solve());
    }


    return 0;
}

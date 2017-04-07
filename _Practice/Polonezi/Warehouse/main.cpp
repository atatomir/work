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

#define maxN 100011

struct shop {
    ll x, y, t;
};

int n, i, pos;
shop S[maxN];
vector< pair<ll, ll> > xx, yy;
ll x, y, sum, aux, sol_x, sol_y, best, lx, ly;

ll abss(ll x) {
    if (x < 0) return -x;
    return x;
}

void check(ll x, ll y) {
    int i;
    ll ans = 0;

    for (i = 1; i <= n; i++) {
        ll dx = abss(S[i].x - x);
        ll dy = abss(S[i].y - y);
        ans += S[i].t * max(dx, dy);

        dx = abss(S[i].x - lx);
        dy = abss(S[i].y - ly);
        ans -= S[i].t * max(dx, dy);
    }

    if (ans < best) {
        best = ans;
        sol_x = x;
        sol_y = y;
    }
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%lld%lld%lld", &S[i].x, &S[i].y, &S[i].t); sum += S[i].t;
        xx.pb(mp(S[i].x - S[i].y, S[i].t));
        yy.pb(mp(S[i].x + S[i].y, S[i].t));
    }

    aux = (sum + 1) / 2;
    sort(xx.begin(), xx.end());
    sort(yy.begin(), yy.end());

    pos = -1; sum = aux;
    while (sum > 0) {
        pos++;
        sum -= xx[pos].second;
    }
    x = xx[pos].first;

    pos = -1; sum = aux;
    while (sum > 0) {
        pos++;
        sum -= yy[pos].second;
    }
    y = yy[pos].first;

    sol_x = x + y;
    sol_y = -x + y;

    x = sol_x / 2;
    y = sol_y / 2;
    lx = x; ly = y;

    sol_x = sol_y = 0;
    best = 1LL << 60;

    check(x, y);
    check(x + 1, y);
    check(x, y + 1);
    check(x + 1, y + 1);


    printf("%lld %lld", sol_x, sol_y);

    return 0;
}

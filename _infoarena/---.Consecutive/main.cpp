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

#define limit 100000

ll t, ti;
ll n, N, i, j, cnt;

bool ciur[limit + 10];
vector<ll> pr;

vector< pair<ll, ll> > divs;
vector< pair<ll, ll> > ans;

ll act;



bool cmp(const pair<ll, ll>& a, const pair<ll, ll>& b) {
    return a.second - a.first < b.second - b.first;
}

void solve(int pas) {
    ll aux = act;

    if (pas == divs.size()) {
        if (act == 1) return;

        ll p = (N / act) - act + 1;
        if (p % 2 == 0 && p > 0) {
            p /= 2;
            ans.pb(mp(p, p + act - 1));
        }

        return;
    }

    for (int i = 0; i <= divs[pas].second; i++) {
        solve(pas + 1);
        act *= divs[pas].first;
    }

    act = aux;
}

int main()
{
    freopen("consecutive.in","r",stdin);
    freopen("consecutive.out","w",stdout);

    for (i = 2; i <= limit; i++) {
        if (ciur[i]) continue;

        pr.pb(i);
        for (ll j = 1LL * i * i; j <= 1LL * limit; j += i) ciur[j] = true;
    }

    scanf("%lld", &t);
    for (ti = 1; ti <= t; ti++) {
        scanf("%lld", &n);
        n *= 2; N = n;

        divs.clear();
        for (auto e : pr) {
            if (1LL * e * e > n) break;
            if (n % e != 0) continue;

            cnt = 0;
            while (n % e == 0) cnt++, n /= e;

            divs.pb(mp(e, cnt));
        }
        if (n != 1) divs.pb(mp(n, 1));

        ans.clear(); act = 1;
        solve(0);
        sort(ans.begin(), ans.end(), cmp);

        printf("%d\n", ans.size());
        for (auto e : ans)
            printf("%lld %lld\n", e.first, e.second);
    }



    return 0;
}

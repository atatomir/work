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

#define maxN 1000011

int n, i;
ll v[maxN], ans;
vector<ll> ord[2];

ll get_upper(ll mask, ll limit) {
    ll p1, p2;
    ll ans = 0;

    for (p1 = n, p2 = 1; p2 <= n; p2++) {
        while (p1 >= 1 && (v[p1] & mask) + (v[p2] & mask) >= limit) p1--;
        ans += n - p1;
    }

    for (i = 1; i <= n; i++)
        if ((v[i] & mask) * 2 >= limit) ans++;

    return ans / 2;
}

ll ask(int bit) {
    ll mask = (1LL << (bit + 1)) - 1;
    ll ind = 1LL << bit;
    ll cnt00, cnt01, cnt10, cnt11;
    int i;

    ord[0].clear(); ord[1].clear();
    for (i = 1; i <= n; i++)
        ord[ (v[i] >> bit) & 1 ].pb(v[i]);

    n = 0;
    for (auto e : ord[0]) v[++n] = e;
    for (auto e : ord[1]) v[++n] = e;

    cnt00 = n * n;
    cnt01 = get_upper(mask, 1LL << bit);
    cnt10 = get_upper(mask, 1LL << (bit + 1));
    cnt11 = get_upper(mask, (1LL << bit) + (1LL << (bit + 1)));

    return (cnt01 - cnt10) + cnt11;
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) scanf("%lld", &v[i]);

    //cerr << ask(0) << '\n';

    for (int bit = 0; bit <= 30; bit++) {
        if (ask(bit) % 2 == 1)
            ans += 1LL << bit;
    }

    printf("%lld", ans);


    return 0;
}

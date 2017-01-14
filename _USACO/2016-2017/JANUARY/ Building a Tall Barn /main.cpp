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

#define maxN 100011

ll n, k, i;
ll v[maxN];
ll cnt[maxN];
ll sol;
double lm, ans;

priority_queue< pair<double, int> > H;



ll check(double limit) {
    ll i;
    ll ans = 0;
    ll x;
    double aux;

    for (i = 1; i <= n; i++) {
        aux = 1.00 * v[i] / limit;
        aux = sqrt(aux);

        if (aux + ans > k + 10) return k + 1;
        x = aux;

        while (x * (x + 1) > 1.00 * v[i] / limit)
            x--;

        while ((x + 1) * (x + 2) <= 1.00 * v[i] / limit)
            x++;

        ans += x + 1;
        cnt[i] = x + 1;
        if (ans > k) return ans;
    }

    return ans;
}

int main()
{
    freopen("tallbarn.in","r",stdin);
    freopen("tallbarn.out","w",stdout);

    scanf("%lld%lld", &n, &k);
    for (i = 1; i <= n; i++)
        scanf("%lld", &v[i]);

    sort(v + 1, v + n + 1);

    double l = 0.00;
    double r = 1000.00;//500000000000.00;
    int steps = 50;

    if (check(r) > k) {
        l = r;
        r = 500000000000.00;
    }

    while (steps-- > 0) {
        double mid = (l + r) / 2.00;

        if (check(mid) < k)
            r = mid;
        else
            l = mid;
    }



    lm = r;
    while (check(lm) > k)
        lm += 1e-7;


    check(lm);
    for (i = 1; i <= n; i++) {
        k -= cnt[i];
        H.push(mp( (1.00 * v[i] / cnt[i]) -
                   (1.00 * v[i] / (cnt[i] + 1)) , i));
    }


    /*while (k > 0) {
        auto act = H.top(); H.pop();
        k--;

        cnt[act.second]++;
        H.push(mp( (1.00 * v[act.second] / cnt[act.second]) -
                   (1.00 * v[act.second] / (cnt[act.second] + 1)) , act.second));
    }*/

    ans -= lm * k;


    for (i = 1; i <= n; i++)
        ans += 1.00 * v[i] / cnt[i];

    ll sol = round(ans);
    printf("%lld", sol);



    return 0;
}

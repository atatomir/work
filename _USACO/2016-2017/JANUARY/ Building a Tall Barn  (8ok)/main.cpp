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
priority_queue< pair<double, int> > H;
double ans;

int main()
{
    freopen("tallbarn.in","r",stdin);
    freopen("tallbarn.out","w",stdout);

    scanf("%lld%lld", &n, &k);
    for (i = 1; i <= n; i++)
        scanf("%lld", &v[i]);

    sort(v + 1, v + n + 1);
    for (i = 1; i <= n; i++) {
        cnt[i] = 1;
        H.push(mp(0.50 * v[i], i));
    }

    k -= n;
    while (k > 0) {
        auto act = H.top(); H.pop();
        k--;

        cnt[act.second]++;
        H.push(mp( (1.00 * v[act.second] / cnt[act.second]) -
                   (1.00 * v[act.second] / (cnt[act.second] + 1)) , act.second));
    }

    for (i = 1; i <= n; i++)
        ans += 1.00 * v[i] / cnt[i];

    ll sol = round(ans);
    printf("%lld", sol);


    return 0;
}

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
#define limit 8
#define inf 1000000000000000000LL

int n, i;
pair<ll, ll> P[maxN];
pair<ll, ll> aux[maxN];
vector< pair<ll, ll> > work;
ll x_lim[maxN];
ll ans;

bool cmp(const pair<ll, ll> &a, const pair<ll, ll> &b) {
    return a.second < b.second;
}

ll dist(pair<ll, ll> A, pair<ll, ll> B) {
    return (A.first - B.first) * (A.first - B.first) + (A.second - B.second) * (A.second - B.second);
}

ll cmap(int l, int r) {
    int i, j;
    ll ans = inf;

    //! if there are only lim points left
    if (r - l + 1 <= limit) {
        for (i = l; i < r; i++)
            for (j = i + 1; j <= r; j++)
                ans = min(ans, dist(P[i], P[j]));

        sort(P + l, P + r + 1);
        return ans;
    }

    //! split it in two parts
    int mid = (l + r) >> 1;

    ans = cmap(l, mid);
    ans = min(ans, cmap(mid + 1, r));

    //! sort by y
    for (i = l; i <= r; i++) aux[i] = P[i];
    merge(aux + l, aux + mid + 1, aux + mid + 1, aux + r + 1, P + l, cmp);

    //! copy in work
    ll low_x = x_lim[mid] - sqrt(ans);
    ll high_x = x_lim[mid] + sqrt(ans);
    work.clear();

    for (i = l; i <= r; i++)
        if (low_x <= P[i].first && P[i].first <= high_x)
            work.pb(P[i]);

    for (i = 0; i < work.size(); i++)
        for (j = i + 1; j < work.size() && j - i <= limit; j++)
            ans = min(ans, dist(work[i], work[j]));

    return ans;
}

int main()
{
    freopen("cmap.in","r",stdin);
    freopen("cmap.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++)
        scanf("%lld %lld", &P[i].first, &P[i].second);

    sort (P + 1, P + n + 1);
    for (i = 1; i <= n; i++) x_lim[i] = P[i].first;

    ans = cmap(1, n);
    printf("%.10lf", sqrt(1.00 * ans));

    return 0;
}

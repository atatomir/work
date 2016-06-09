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
#define T pair<ll, ll>

int n, i;
pair<ll, ll> v[maxN];

ll unused, bought;

int tp(const T& a) {
    return (a.first <= a.second ? +1 : -1);
}

bool cmp(const T& a, const T& b) {
    if (tp(a) != tp(b)) return tp(a) > tp(b); //! first +1 ones
    if (tp(a) == +1)
        return mp(a.first, -a.second) < mp(b.first, -b.second);
    else
        return mp(a.second, -a.first) > mp(b.second, -b.first);
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) scanf("%lld%lld", &v[i].first, &v[i].second);
    sort(v + 1, v + n + 1, cmp);

    unused = bought = 0;
    for (i = 1; i <= n; i++) {
        if (unused < v[i].first) {
            bought += v[i].first - unused;
            unused = v[i].first;
        }

        unused -= v[i].first;
        unused += v[i].second;
    }

    printf("%lld", bought);

    return 0;
}

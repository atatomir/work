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

int n, q, i, x, y;
int v[maxN];
vector< pair<int, int> > order;

bool on[maxN];
int dad[maxN];
int cnt[maxN];

ll aux;
ll sum[maxN];

int Find(int x) {
    if (dad[x] == x) return x;
    dad[x] = Find(dad[x]);
    return dad[x];
}

bool Merge(int x, int y) {
    x = Find(x);
    y = Find(y);

    if (x == y) return false;
    dad[x] = y;
    cnt[y] += cnt[x];
    return true;
}

int main()
{
    freopen("nrsubsecv.in","r",stdin);
    freopen("nrsubsecv.out","w",stdout);

    scanf("%d%d", &n, &q);
    for (i = 1; i <= n; i++) {
        scanf("%d", &v[i]);
        order.pb(mp(v[i], i));
    }

    sort(order.begin(), order.end());
    reverse(order.begin(), order.end());

    for (i = 1; i <= n; i++) dad[i] = i, cnt[i] = 1;
    for (auto e : order) {
        aux = 1;
        on[e.second] = true;

        if (on[e.second - 1]) {
            aux *= 1LL * cnt[Find(e.second - 1)] + 1;
            Merge(e.second, e.second - 1);
        }

        if (on[e.second + 1]) {
            aux *= 1LL * cnt[Find(e.second + 1)] + 1;
            Merge(e.second, e.second + 1);
        }

        sum[e.first] += aux;
    }

    for (i = 1; i <= 1000000; i++) sum[i] += sum[i - 1];
    for (i = 1; i <= q; i++) {
        scanf("%d%d", &x, &y);
        aux = sum[y];
        if (x != 0) aux -= sum[x - 1];
        printf("%lld\n", aux);
    }

    return 0;
}

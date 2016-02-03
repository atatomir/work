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
#define pii pair<ll, ll>

#define maxN 10011

int n, need, i, j;
pii Point[maxN];
ll aux[maxN];
int order[maxN];

ll slope = 100000LL;

int pos;
vector<int> now;
int hull[maxN];
bool us[maxN];

bool order_cmp(int a, int b) {
    return aux[a] < aux[b];
}

bool batch_cmp(int a, int b) {
    return Point[a] < Point[b];
}

ll cross(pii a, pii b, pii c) {
    b.first -= a.first;
    b.second -= a.second;

    c.first -= a.first;
    c.second -= a.second;

    return b.first * c.second - b.second * c.first;
}

void solve_batch() {
    int i;

    sort(now.begin(), now.end(), batch_cmp);

    hull[1] = now[0];
    hull[2] = now[1];
    pos = 2;

    for (i = 2; i < now.size(); i++) {
        int id = now[i];

        while (pos > 1) {
            ll lulu = cross(Point[ hull[pos - 1] ], Point[ hull[pos] ], Point[id]);
            if (lulu < 0) break;
            pos--;
        }

        hull[++pos] = id;
    }

    int lim = pos;
    for (i = now.size() - 1; i >= 0; i--) {
        int id = now[i];

        while (pos > lim) {
            ll lulu = cross(Point[ hull[pos - 1] ], Point[ hull[pos] ], Point[id]);
            if (lulu < 0) break;
            pos--;
        }

        hull[++pos] = id;
    }

    for (i = 1; i <= pos; i++)
        us[ hull[i] ] = true;

    pos--;
    printf("%d %d ", pos, need - pos);
    for (i = pos; i > 0; i--) printf("%d ", hull[i]);
    for (auto e : now)
        if (us[e] == false)
            printf("%d ", e);
    printf("\n");
}

int main()
{
    freopen("testament.in","r",stdin);
    freopen("testament.out","w",stdout);

    scanf("%d%d", &need, &n);
    n *= need;

    for (i = 1; i <= n; i++) {
        scanf("%lld %lld", &Point[i].first, &Point[i].second);
        aux[i] = Point[i].second - Point[i].first * slope;
        order[i] = i;
    }

    sort(order + 1, order + n + 1, order_cmp);

    for (i = 1; i <= n; i += need) {
        now.clear();
        for (j = i; j < i + need; j++)
            now.pb(order[j]);

        solve_batch();
    }

    return 0;
}

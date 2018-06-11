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

const int limit = 1000000000;

ll abss(ll x) {
    if (x < 0) return -x;
    return x;
}

struct lee_node {
    ll m, n;
    lee_node* son[2];

    lee_node() {}

    lee_node(ll _m, ll _n) {
        m = _m;
        n = _n;
        son[0] = son[1] = NULL;
    }

    ll compute(ll x, ll m, ll n) {
        return abss(x - m) + n;
    }

    void add_line(ll l, ll r, ll mm, ll nn) {
        if (compute(l, mm, nn) < compute(l, m, n)) {
            swap(m, mm);
            swap(n, nn);
        }

        if (compute(r, m, n) <= compute(r, mm, nn)) return;
        ll mid = (l + r) >> 1;

        if (compute(mid, m, n) < compute(mid, mm, nn)) {
            if (son[1] == NULL)
                son[1] = new lee_node(mm, nn);
            else
                son[1]->add_line(mid + 1, r, mm, nn);
        } else {
            swap(n, nn);
            swap(m, mm);

            if (son[0] == NULL)
                son[0] = new lee_node(mm, nn);
            else
                son[0]->add_line(l, mid, mm, nn);
        }
    }

    ll query(ll l, ll r, ll pos) {
        if (l == r) return compute(pos, m, n);
        ll ans = compute(pos, m, n);
        ll mid = (l + r) >> 1;

        if (pos <= mid && son[0] != NULL)
            ans = min(ans, son[0]->query(l, mid, pos));
        if (pos > mid && son[1] != NULL)
            ans = min(ans, son[1]->query(mid + 1, r, pos));

        return ans;
    }

    void rm() {
        if (son[0] != NULL) son[0]->rm();
        if (son[1] != NULL) son[1]->rm();
        delete this;
    }
};

struct Point {
   ll x, y, t;

   bool operator<(const Point& who)const {
    return y < who.y;
   }
};

int n, m, i, p;
Point P[maxN], Q[maxN];
ll ans[maxN];

lee_node *Head;

int main()
{
    freopen("slingshot.in","r",stdin);
    freopen("slingshot.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) scanf("%lld%lld%lld", &P[i].x, &P[i].y, &P[i].t);
    for (i = 1; i <= m; i++) scanf("%lld%lld", &Q[i].x, &Q[i].y), Q[i].t = i, ans[i] = abss(Q[i].x - Q[i].y);

    sort(P + 1, P + n + 1);
    sort(Q + 1, Q + m + 1);

    //! bottom up
    Head = new lee_node(limit, limit);
    p = 1;
    for (i = 1; i <= m; i++) {
        while (p <= n && P[p].y <= Q[i].y) {
            Head->add_line(0, limit, P[p].x, P[p].t - P[p].y);
            p++;
        }

        ans[Q[i].t] = min(ans[Q[i].t], Head->query(0, limit, Q[i].x) + Q[i].y);
    }
    Head->rm();

    //! up - down
    Head = new lee_node(limit, limit);
    p = n;
    for (i = m; i >= 1; i--) {
        while (p >= 1 && P[p].y >= Q[i].y) {
            Head->add_line(0, limit, P[p].x, P[p].t + P[p].y);
            p--;
        }

        ans[Q[i].t] = min(ans[Q[i].t], Head->query(0, limit, Q[i].x) - Q[i].y);
    }
    Head->rm();


    for (i = 1; i <= m; i++) printf("%lld\n", ans[i]);


    return 0;
}

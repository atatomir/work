#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 200011
#define maxLog 19
#define inf 1000000001

struct intr {
    int l, r, id;

    bool operator<(const intr& who)const {
        return mp(r, l) < mp(who.r, who.l);
    }
};

struct place {
    int l, r, need;

    bool operator<(const place& who)const {
        return l < who.l;
    }
};

int n, i, j;
intr I[maxN];
int lmax[maxN];
int wh[maxN];

int nxt[maxLog][maxN];
set< place > S;

int pos, l, r, act_l, act_r, act_need, p1, p2;
vector<int> ans;




int query(int l, int r) {
    int i, pos;

    pos = lower_bound(lmax + 1, lmax + n + 1, l) - lmax;
    if (I[pos].r > r) return 0;

    int ans = 1;
    int act = pos;
    for (i = maxLog - 1; i >= 0; i--)
        if (I[ nxt[i][act] ].r <= r)
            ans += (1 << i), act = nxt[i][act];

    return ans;
}


int main()
{
    freopen("centru2.in","r",stdin);
    freopen("centru2.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) scanf("%d%d", &I[i].l, &I[i].r), I[i].id = i;
    sort(I + 1, I + n + 1);

    lmax[1] = I[1].l;
    for (i = 2; i <= n; i++) lmax[i] = max(lmax[i - 1], I[i].l);

    for (i = 1; i <= n; i++) wh[ I[i].id ] = i;

    nxt[0][n + 1] = n + 1;
    I[n + 1] = {inf, inf, -1};

    for (i = 1; i <= n; i++) {
        int pos = lower_bound(lmax + i, lmax + n + 1, I[i].r + 1) - lmax;
        nxt[0][i] = pos;
    }

    for (i = 1; i < maxLog; i++) {
        nxt[i][n + 1] = n + 1;
        for (j = 1; j <= n; j++)
            nxt[i][j] = nxt[i - 1][ nxt[i - 1][j] ];
    }

    S.insert({1, inf - 1, query(1, inf - 1)});

    for (i = 1; i <= n; i++) {
        pos = wh[i];
        l = I[pos].l;
        r = I[pos].r;

        auto it = S.upper_bound({l, r, 0});
        if (it == S.begin()) continue;
        it--;

        act_l = it->l;
        act_r = it->r;
        act_need = it->need;

        if (l < act_l || r > act_r) continue;

        p1 = query(act_l, l - 1);
        p2 = query(r + 1, act_r);
        if (p1 + 1 + p2 == act_need) {
            //! we can use it
            ans.pb(i);

            S.erase(it);
            if (p1 != 0) S.insert({act_l, l - 1, p1});
            if (p2 != 0) S.insert({r + 1, act_r, p2});
        }
    }

    printf("%d\n", ans.size());
    for (auto e : ans)
        printf("%d ", e);

    if (ans.size() != query(1, inf - 1))
        cerr << "err";

    return 0;
}

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>


using namespace std;


#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 31
#define maxQ 300011
#define maxL 30011
#define inf 1000000007

struct edge {
    int x, y, a, r;
};

struct que {
    int u, v, a, b, id;
};

int n, l, q, i;
edge E[maxQ];
que Q[maxQ];
int ans[maxQ];

int le[maxL][maxN][maxN];
int ri[maxL][maxN][maxN];

void solve(int posl, int posr, int ql, int qr) {
    int i, j, mid, p;
    if (ql > qr) return;
    if (posl > posr) return;

    mid = (posl + posr) >> 1;

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            le[mid][i][j] = ri[mid - 1][i][j] = inf;
        }
        le[mid][i][i] = ri[mid - 1][i][i] = 0;
    }

    //! compute ri
    for (p = mid; p <= posr; p++) {
        for (i = 1; i <= n; i++)
            for (j = 1; j <= n; j++)
                ri[p][i][j] = min(inf, ri[p - 1][i][j] + E[p].r);

        for (i = 1; i <= n; i++) {
            ri[p][i][E[p].x] = min(ri[p][i][E[p].x], ri[p - 1][i][E[p].y] + E[p].a);
            ri[p][i][E[p].y] = min(ri[p][i][E[p].y], ri[p - 1][i][E[p].x] + E[p].a);
        }
    }

    //! compute le
    for (p = mid - 1; p >= posl; p--) {
        for (i = 1; i <= n; i++)
            for (j = 1; j <= n; j++)
                le[p][i][j] = min(inf, le[p + 1][i][j] + E[p].r);

        for (i = 1; i <= n; i++) {
            le[p][i][E[p].x] = min(le[p][i][E[p].x], le[p + 1][i][E[p].y] + E[p].a);
            le[p][i][E[p].y] = min(le[p][i][E[p].y], le[p + 1][i][E[p].x] + E[p].a);
        }
    }

    p = ql;
    for (i = ql; i <= qr; i++) {
        if (Q[i].b < mid)
            swap(Q[p++], Q[i]);
    }
    int act_l = p;

    p = qr;
    for (i = qr; i >= ql; i--) {
        if (Q[i].a > mid)
            swap(Q[p--], Q[i]);
    }
    int act_r = p;

    for (p = act_l; p <= act_r; p++) {
        auto qq = Q[p];

        ans[qq.id] = inf;
        for (i = 1; i <= n; i++)
            ans[qq.id] = min(ans[qq.id], le[qq.a][i][qq.u] + ri[qq.b][i][qq.v]);
    }

    solve(posl, mid - 1, ql, act_l - 1);
    solve(mid + 1, posr, act_r + 1, qr);
}

int main() {
    freopen("razbunare.in", "r", stdin);
    freopen("razbunare.out", "w", stdout);

    scanf("%d%d%d", &n, &l, &q);
    for (i = 1; i <= l; i++) scanf("%d%d%d%d", &E[i].x, &E[i].y, &E[i].a, &E[i].r);
    for (i = 1; i <= q; i++) scanf("%d%d%d%d", &Q[i].u, &Q[i].v, &Q[i].a, &Q[i].b), Q[i].id = i;

    solve(1, l, 1, q);
    for (i = 1; i <= q; i++) {
        if (ans[i] >= inf) ans[i] = -1;
        printf("%d\n", ans[i]);
    }


    return 0;
}

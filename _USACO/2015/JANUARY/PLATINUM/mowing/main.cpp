#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 400011
#define lSon (node << 1)
#define rSon (lSon | 1)
#define ll long long

//! it is not balanced
struct Treap {
    Treap *son[2];
    int cnt, val;
    int how;

    Treap(int _val) {
        son[0] = son[1] = NULL;
        cnt = 0;
        val = _val;
        how = 0;
    }

    void update() {
        cnt = how;
        if (son[0] != NULL)
            cnt += son[0]->cnt;
        if (son[1] != NULL)
            cnt += son[1]->cnt;
    }
} *nil;

void insert_treap(Treap* &Head, int _val) {
    if (Head == nil) {
        Head = new Treap(_val);

        Head->son[0] = Head->son[1] = nil;
        Head->how = 1;
        Head->update();
        return;
    }

    if (_val < Head->val)
        insert_treap(Head->son[0], _val);
    else
    if (_val > Head->val)
        insert_treap(Head->son[1], _val);
    else
        Head->how++;

    Head->update();
};

int count_treap(Treap *Head, int limit) {
    if (Head == nil)
        return 0;

    if (Head->val <= limit)
        return Head->son[0]->cnt + 1 + count_treap(Head->son[1], limit);
    else
        return count_treap(Head->son[0], limit);
}

//! --------------------------------------------

class aint {
    public:
        int n;
        Treap **data;

        void init(int _n, Treap **_data) {
            n = _n;
            data = _data;
        }

        void update(int node, int l, int r, int qL, int qR, int v) {
            if (qL <= l && r <= qR) {
                insert_treap(data[node], v);
                return;
            }

            int mid = (l + r) >> 1;
            if (qL <= mid)
                update(lSon, l, mid, qL, qR, v);
            if (qR >  mid)
                update(rSon, mid + 1, r, qL, qR, v);
        }

        ll query(int node, int l, int r, int pos, int qL, int qR) {
            ll ans = count_treap(data[node], qR - 1) - count_treap(data[node], qL);

            if (l == r)
                return ans;

            int mid = (l + r) >> 1;
            if (pos <= mid)
                return query(lSon, l, mid, pos, qL, qR) + ans;
            else
                return query(rSon, mid + 1, r, pos, qL, qR) + ans;
        }

};

struct Point {
    int x, y;
};

int n, t, i;
Point P[maxN];

vector<int> norm_x, norm_y;
unordered_map<int, int> aux;

ll ans;

//! for aint -----------------
Treap* vert_data[maxN << 2];
aint vert;

Treap* hori_data[maxN << 2];
aint hori;
//! -------------------------

int main()
{
    freopen("mowing.in","r",stdin);
    freopen("mowing.out","w",stdout);

    scanf("%d%d", &n, &t);
    for (i = 1; i <= n; i++) {
        scanf("%d%d", &P[i].x, &P[i].y);
        norm_x.pb(P[i].x);
        norm_y.pb(P[i].y);

        norm_x.pb(P[i].x - 1);
        norm_x.pb(P[i].x + 1);
        norm_y.pb(P[i].y - 1);
        norm_y.pb(P[i].y + 1);
    }

    //! normalizare pe x
    sort(norm_x.begin(), norm_x.end());
    norm_x.resize( unique(norm_x.begin(), norm_x.end()) - norm_x.begin() );

    aux.clear();
    for (i = 0; i < norm_x.size(); i++)
        aux[ norm_x[i] ] = i + 1;

    for (i = 1; i <= n; i++)
        P[i].x = aux[ P[i].x ];

    //! normalizare pe y
    sort(norm_y.begin(), norm_y.end());
    norm_y.resize( unique(norm_y.begin(), norm_y.end()) - norm_y.begin() );

    aux.clear();
    for (i = 0; i < norm_y.size(); i++)
        aux[ norm_y[i] ] = i + 1;

    for (i = 1; i <= n; i++)
        P[i].y = aux[ P[i].y ];

    //! init nil
    int lim = max(norm_x.size(), norm_y.size());

    nil = new Treap(0);
    for (i = 1; i <= lim * 4; i++)
        vert_data[i] = hori_data[i] = nil;

    //! now solve

    vert.init(norm_y.size(), vert_data);
    hori.init(norm_x.size(), hori_data);

    for (i = 1; i + t + 2 <= n; i++) {
        if (P[i].x == P[i + 1].x) { //! actual line is vertical
            int mini = min(P[i].y, P[i + 1].y);
            int maxi = max(P[i].y, P[i + 1].y);

            if (P[i + 1].y < P[i].y)
                mini++;
            else
                maxi--;

            if (mini <= maxi)
                vert.update(1, 1, vert.n, mini, maxi, P[i].x);

            int id = i + t + 1;
            mini = min(P[id].x, P[id + 1].x);
            maxi = max(P[id].x, P[id + 1].x);

            ans += vert.query(1, 1, vert.n, P[id].y, mini, maxi);
        } else { //! actual line is horizontal
            int mini = min(P[i].x, P[i + 1].x);
            int maxi = max(P[i].x, P[i + 1].x);

            if (P[i + 1].x < P[i].x)
                mini++;
            else
                maxi--;

            if (mini <= maxi)
                hori.update(1, 1, hori.n, mini, maxi, P[i].y);

            int id = i + t + 1;
            mini = min(P[id].y, P[id + 1].y);
            maxi = max(P[id].y, P[id + 1].y);

            ans += hori.query(1, 1, hori.n, P[id].x, mini, maxi);
        }
    }

    printf("%lld", ans);

    return 0;
}

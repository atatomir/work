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

#define maxN 100011
#define lSon (node << 1)
#define rSon (lSon | 1)
#define ll long long

class aint {
    public:
        int n;
        vector<int> *data;

        void init(int _n, vector<int> *_data) {
            n = _n;
            data = _data;
        }

        void update(int node, int l, int r, int qL, int qR, int v) {
            if (qL <= l && r <= qR) {
                data[node].pb(v);
                sort(data[node].begin(), data[node].end());
                return;
            }

            int mid = (l + r) >> 1;
            if (qL <= mid)
                update(lSon, l, mid, qL, qR, v);
            if (qR >  mid)
                update(rSon, mid + 1, r, qL, qR, v);
        }

        ll query(int node, int l, int r, int pos, int qL, int qR) {
            auto lft = upper_bound(data[node].begin(), data[node].end(), qL - 1);
            auto rgh = upper_bound(data[node].begin(), data[node].end(), qR);

            ll ans = rgh - lft;

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
vector<int> vert_data[maxN << 2];
aint vert;

vector<int> hori_data[maxN << 2];
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

    //! now solve

    vert.init(norm_y.size(), vert_data);
    hori.init(norm_x.size(), hori_data);

    for (i = 1; i + t + 2 <= n; i++) {
        if (P[i].x == P[i + 1].x) { //! actual line is vertical
            int mini = min(P[i].y, P[i + 1].y);
            int maxi = max(P[i].y, P[i + 1].y);

            vert.update(1, 1, vert.n, mini, maxi, P[i].x);

            int id = i + t + 1;
            mini = min(P[id].x, P[id + 1].x);
            maxi = max(P[id].x, P[id + 1].x);

            ans += vert.query(1, 1, vert.n, P[id].y, mini, maxi);
        } else { //! actual line is horizontal
            int mini = min(P[i].x, P[i + 1].x);
            int maxi = max(P[i].x, P[i + 1].x);

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

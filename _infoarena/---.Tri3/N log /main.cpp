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
#define lSon (node << 1)
#define rSon (lSon | 1)



struct point {
    ll x, y;

    bool operator<(const point& who)const {
        return mp(x, -y) < mp(who.x, -who.y);
    }
};

struct query {
    point A, B;
    int id;
};

void convex_hull(vector<point>& data);
ll cross(point A, point B, point C);
query Q[maxN];
int posL[maxN], posR[maxN];
bool ans[maxN];


struct aint {
    int n, i;
    vector< vector<point> > data;
    vector< vector<int> > answer;
    point *from;

    void build(int node, int l, int r) {
        if (l == r) {
            data[node] = {from[l]};
            return;
        }

        int mid = (l + r) >> 1;
        build(lSon, l, mid);
        build(rSon, mid + 1, r);

        data[node].resize(data[lSon].size() + data[rSon].size());
        merge(data[lSon].begin(), data[lSon].end(),
              data[rSon].begin(), data[rSon].end(),
              data[node].begin());

        convex_hull(data[node]);
    }

    void init(int _n, point* _from) {
        n = _n; from = _from;
        data = vector< vector<point> >(4 * n + 11, vector<point>(0));
        answer = vector< vector<int> >(4 * n + 11, vector<int>(0));

        build(1, 1, n);
    }

    void solve(int node) {
        int pos = 0;

        for (auto id_e : answer[node]) {
            auto e = Q[id_e];
            while (pos + 1 < data[node].size()) {
                if (cross(e.A, e.B, data[node][pos]) < cross(e.A, e.B, data[node][pos + 1]))
                    break;
                pos++;
            }

            if (cross(e.A, e.B, data[node][pos]) <= 0)
                ans[e.id] = true;
        }
    }

    void propagate(int node, int l, int r) {
        vector<int> here = {};
        int mid = (l + r) >> 1;

        for (auto id_e : answer[node]) {
            auto e = Q[id_e];
            if (posL[e.id] <= l && r <= posR[e.id]) {
                here.pb(id_e);
                continue;
            }

            if (posL[e.id] <= mid)
                answer[lSon].pb(id_e);
            if (posR[e.id] > mid)
                answer[rSon].pb(id_e);
        }

        answer[node] = here;
        solve(node);

        if (l != r) {
            propagate(lSon, l, mid);
            propagate(rSon, mid + 1, r);
        }
    }

};

int n, m, i;
point P[maxN];
aint work;

vector<query> hh;

ll cross(point A, point B, point C) {
    B.x -= A.x;
    B.y -= A.y;

    C.x -= A.x;
    C.y -= A.y;

    return B.x * C.y - B.y * C.x;
}

void convex_hull(vector<point>& data) {
    vector<point> aux = data;
    data.clear();

    for (auto e : aux) {
        while (data.size() >= 2) {
            if (cross(data[data.size() - 2], data[data.size() - 1], e) > 0)
                break;
            data.pop_back();
        }
        data.pb(e);
    }
}

int main()
{
    freopen("tri3.in","r",stdin);
    freopen("tri3.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) {
        scanf("%lld%lld", &P[i].x, &P[i].y);
    }
    for (i = 1; i <= m; i++) {
        scanf("%lld%lld", &Q[i].A.x, &Q[i].A.y);
        scanf("%lld%lld", &Q[i].B.x, &Q[i].B.y);
        Q[i].id = i;
    }

    auto cmp = [](const point& a, const point& b)->bool const {
        return a.y * b.x < a.x * b.y;
    };

    sort(P + 1, P + n + 1, cmp);
    work.init(n, P);

    for (i = 1; i <= m; i++) {
        if (Q[i].B < Q[i].A) swap(Q[i].A, Q[i].B);
        posL[i] = lower_bound(P + 1, P + n + 1, Q[i].A, cmp) - P;
        posR[i] = lower_bound(P + 1, P + n + 1, Q[i].B, cmp) - P;

        if (posL[i] > posR[i]) swap(posL[i], posR[i]);
        posR[i]--;

        if (posL[i] > posR[i]) continue;
        work.answer[1].pb(i);
    }

    auto cmp2 = [](const int& aa, const int& bb)->bool const {
        const auto& a = Q[aa];
        const auto& b = Q[bb];

        if (a.A.x == a.B.x) return true;
        if (b.A.x == b.B.x) return false;
        return (a.B.y - a.A.y) * (b.B.x - b.A.x) < (a.B.x - a.A.x) * (b.B.y - b.A.y);
    };

    sort(work.answer[1].begin(), work.answer[1].end(), cmp2);
    work.propagate(1, 1, n);

    for (i = 1; i <= m; i++) {
        if (ans[i])
            printf("Y\n");
        else
            printf("N\n");
    }


    return 0;
}

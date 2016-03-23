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

#define maxN 500011
#define lSon (node << 1)
#define rSon (lSon | 1)
#define inf 1000000000000000000LL
#define ref 500001LL

class aint {
    public:
        void init(int _dim, ll *_data) {
            dim = _dim;
            data = _data;

            for (int i = 1; i <= 4 * dim; i++)  data[i] = -inf;
        }

        void update(int node, int l, int r, int pos, ll val) {
            if (l == r) {
                data[node] = val;
                return;
            }

            int mid = (l + r) >> 1;
            if (pos <= mid)
                update(lSon, l, mid, pos, val);
            else
                update(rSon, mid + 1, r, pos, val);

            data[node] = max(data[lSon], data[rSon]);
        }

        ll query(int node, int l, int r, int qL, int qR) {
            if (qL <= l && r <= qR)
                return data[node];

            ll ans = -inf;
            int mid = (l + r) >> 1;
            if (qL <= mid)
                ans = max(ans, query(lSon, l, mid, qL, qR));
            if (qR >  mid)
                ans = max(ans, query(rSon, mid + 1, r, qL, qR));

            return ans;
        }

    private:
        int dim;
        ll *data;
};

struct offer {
    ll t, pos, pay;

    void read() {
        scanf("%lld%lld%lld", &t, &pos, &pay);
    }

    bool operator<(const offer &who)const {
        if (t == who.t) return pos < who.pos;
        return t < who.t;
    }
};

int n, i, U, D, S, j;
offer v[maxN];
ll aint_data_l[maxN << 2];
ll aint_data_r[maxN << 2];
aint le, ri;

vector<offer> work;
ll val[maxN];

void add_l(int pos, ll val) {
    val -= D * (ref - pos);
    le.update(1, 1, ref, pos, val);
}

void add_r(int pos, ll val) {
    val -= U * pos;
    ri.update(1, 1, ref, pos, val);
}


int main()
{
    freopen("salesman.in","r",stdin);

    scanf("%d%d%d%d", &n, &U, &D, &S);
    le.init(ref, aint_data_l);
    ri.init(ref, aint_data_r);

    swap(U, D);

    for (i = 1; i <= n; i++) v[i].read();
    for (i = 1; i <= ref; i++) val[i] = -inf;

    n++;
    v[n].pay = 0;
    v[n].pos = S;
    v[n].t = ref + 1;

    sort(v + 1, v + n + 1);
    add_l(S, 0);
    add_r(S, 0);

    for (i = 1; i <= n; i = j) {
        ll rez;

        work.clear();
        for (j = i; j <= n && v[j].t == v[i].t; j++)
            work.pb(v[j]);

        //! from left
        rez = -inf;
        for (offer e : work) {
            ll aux = max(le.query(1, 1, ref, 1, e.pos) + (ref - e.pos) * D + e.pay,
                         ri.query(1, 1, ref, e.pos, ref) + e.pos * U + e.pay);

            aux = max(rez + (ref - e.pos) * D + e.pay, aux);
            val[e.pos] = max(val[e.pos], aux);
            rez = max(rez, aux - (ref - e.pos) * D );
        }



        //! from right
        reverse(work.begin(), work.end());
        rez = -inf;
        for (offer e : work) {
            ll aux = max(le.query(1, 1, ref, 1, e.pos) + (ref - e.pos) * D + e.pay,
                         ri.query(1, 1, ref, e.pos, ref) + e.pos * U + e.pay);

            aux = max(rez + e.pos * U + e.pay, aux);
            val[e.pos] = max(val[e.pos], aux);
            rez = max(rez, aux - e.pos * U);
        }



        //! add to aint
        for (offer e : work) {
            add_l(e.pos, val[e.pos]);
            add_r(e.pos, val[e.pos]);
        }
    }

    printf("%lld", max(val[S], 0LL));


    return 0;
}

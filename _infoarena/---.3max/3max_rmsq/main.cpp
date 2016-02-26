#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll int//long long

#define maxN 55000 * 5
#define pii pair<ll, ll>

//! metoda smenoasa cu RMQ
int how[maxN];

class max_RMQ {
    public:
        void get_from(int _dim, ll *aux) {
            logg = how[_dim];

            dim = _dim;
            data = vector< vector<pii> >(logg + 2, vector<pii>(dim + 5, mp(0, 0)));

            for (i = 1; i <= dim; i++) data[0][i] = mp(aux[i], i);

            for (int act_log = 1; act_log <= logg; act_log++) {
                int sz = (1 << act_log);
                int small_sz = sz >> 1;

                for (i = 1; i + sz - 1 <= dim; i++)
                    data[act_log][i] = max(data[act_log - 1][i], data[act_log - 1][i + small_sz]);
            }
        }

        pii query(int l, int r) {
            int now = how[r - l + 1];
            int sz = 1 << now;

            if (l > r) return mp(0, 0);

            return max(data[now][l], data[now][r - sz + 1]);
        }

    private:
        int dim, i, logg;
        vector< vector<pii> > data;
};

class min_RMQ {
    public:
        void get_from(int _dim, ll *aux) {
            logg = how[_dim];

            dim = _dim;
            data = vector< vector<pii> >(logg + 2, vector<pii>(dim + 5, mp(0, 0)));

            for (i = 1; i <= dim; i++) data[0][i] = mp(aux[i], i);

            for (int act_log = 1; act_log <= logg; act_log++) {
                int sz = (1 << act_log);
                int small_sz = sz >> 1;

                for (i = 1; i + sz - 1 <= dim; i++)
                    data[act_log][i] = min(data[act_log - 1][i], data[act_log - 1][i + small_sz]);
            }
        }

        pii query(int l, int r) {
            int now = how[r - l + 1];
            int sz = 1 << now;

            if (l > r) return mp(0, 0);

            return min(data[now][l], data[now][r - sz + 1]);
        }

    private:
        int dim, i, logg;
        vector< vector<pii> > data;
};

int n, m, i, cnt;
ll v[maxN];
ll dp_l[maxN], dp_r[maxN];

ll now[maxN];
ll sum[maxN], partner[maxN], limit[maxN], best[maxN];

min_RMQ rmq_sum;
max_RMQ rmq_best;

void compute_all() {
    int i;

    for (i = 1; i <= n; i++) sum[i] = sum[i - 1] + now[i];
    limit[1] = 0;
    partner[1] = 1;
    best[1] = 0;

    for (i = 2; i <= n; i++) {
        if (sum[i - 1] >= sum[i]) {
            limit[i] = i - 1;
            partner[i] = i;
            best[i] = 0;
        } else {
            limit[i] = i - 1;
            partner[i] = i;

            while (limit[i] > 0 && sum[ limit[i] ] < sum[i]) {
                if (sum[ partner[ limit[i] ] - 1 ] < sum[ partner[i] - 1 ]) partner[i] = partner[ limit[i] ];
                limit[i] = limit[ limit[i] ];
            }

            best[i] = sum[i] - sum[ partner[i] - 1 ];
        }
    }

    rmq_sum.get_from(n, sum);
    rmq_best.get_from(n, best);
}

int main()
{
    freopen("3max.in","r",stdin);
    freopen("3max.out","w",stdout);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) scanf("%d", &v[i]);

    for (i = 1; i <= n; i++)
        dp_l[i] = max(0, dp_l[i - 1]) + v[i];
    for (i = 1; i <= n; i++)
        dp_l[i] = max(dp_l[i], dp_l[i - 1]);

    for (i = n; i >= 1; i--)
        dp_r[i] = max(0, dp_r[i + 1]) + v[i];
    for (i = n; i >= 1; i--)
        dp_r[i] = max(dp_r[i], dp_r[i + 1]);

    for (i = 1; i <= n; i++) {
        now[++cnt] = v[i];

        now[++cnt] = -dp_l[i];
        now[++cnt] = +dp_l[i];

        now[++cnt] = +dp_r[i + 1];
        now[++cnt] = -dp_r[i + 1];
    }

    how[1] = 0;
    for (i = 1; i <= cnt; i++) {
        how[i] = how[i - 1];
        if ( (1 << (how[i] + 1)) <= i ) how[i]++;
    }

    n = cnt;
    compute_all();

    for (int qq = 1; qq <= m; qq++) {
        int l, r;
        ll ans = 0;

        scanf("%d%d", &l, &r);

        l = max(1, ((l - 1) * 5) - 3);
		r = min(n, ((r) * 5 ) + 3);

        auto now = rmq_best.query(l, r);
        if (partner[now.second] < l) {
            int aux = now.second;

            ans = max(rmq_best.query(aux + 1, r).first, sum[aux] - rmq_sum.query(l - 1, aux).first);
        } else {
            ans = now.first;
        }

        if (n < 3) ans = 0;
        printf("%d\n", max(ans, 0));
    }

    return 0;
}

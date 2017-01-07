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

#define maxN 200011
#define maxSQRT 355
#define maxLogSQRT 11

const int limit = 270; // [1,limit] split (> limit) brute

struct trip {
    int x, y, id;

    bool operator<(const trip& who) const {
        return mp(x, y) < mp(who.x, who.y);
    }
};

struct suffix_array {
    int n, i, j, dm, who;
    vector<int> lg;
    vector< vector<int> > data;
    vector<trip> aux;

    void init(int _n, char* from) {
        n = _n;

        lg.resize(n + 10);
        lg[1] = 0;
        for (i = 2; i <= n; i++) lg[i] = 1 + lg[i / 2];

        data = vector< vector<int> >(lg[n] + 2, vector<int>(n + 1, 0));
        for (i = 1; i <= n; i++) data[0][i] = from[i];

        aux.resize(n + 2);

        for (i = 1; i <= lg[n] + 1; i++) {
            dm = (1 << (i - 1));

            for (j = 1; j <= n; j++)
                aux[j - 1] = {data[i - 1][j], (j + dm <= n ? data[i - 1][j + dm] : -1), j};
            sort(aux.begin(), aux.end());

            data[i][ aux[0].id ] = 0;
            for (j = 1; j < aux.size(); j++) {
                if (!(aux[j - 1] < aux[j]))
                    data[i][ aux[j].id ] = data[i][ aux[j - 1].id ];
                else
                    data[i][ aux[j].id ] = j;
            }
        }
    }

    int lcp(int a, int b) {
        int ans = 0;

        for (int step = lg[n] + 1; step >= 0; step--)
            if (data[step][a] == data[step][b])
                ans += 1 << step, a += 1 << step, b += 1 << step;

        return ans;
    }
};

struct query {
    int l, r, k, x, y;
    int ans;
};

struct rmq {
    int n, i, j, sm, bg;
    vector< vector< int > > data;
    //pair<int, int> data[maxLogSQRT][maxSQRT];
    vector<int> *lg;

    void init(int _n, int *from, vector<int>* _lg) {
        n = _n; lg = _lg;

        data = vector< vector< int > >( (*lg)[n] + 1, vector< int >(n + 1, 0) );
        for (i = 0; i < n; i++) data[0][i] = from[i];
        for (i = 1; i <= (*lg)[n]; i++) {
            bg = (1 << i);
            sm = bg >> 1;

            for (j = 0; j + bg <= n; j++)
                data[i][j] = min(data[i - 1][j], data[i - 1][j + sm]);
        }
    }

    int query(int l, int r) {
        int dim = (r - l + 1);
        int hp = (*lg)[dim];

        return min(data[hp][l], data[hp][r - (1 << hp) + 1]);
    }
};

int n, m, q, i;
char s[maxN];
suffix_array SA;

vector<int> order;
int val[maxN];

query Q[maxN];
rmq whole, part[maxSQRT];

vector<int> part_vals[maxSQRT];
vector<int> ids[maxSQRT];

int dif;


bool conc_cmp(pair<int, int> a1, pair<int, int> a2, pair<int, int> a3, pair<int, int> b1, pair<int, int> b2, pair<int, int> b3, bool eq) {
    int lcp, dim;
    int sum = 0;

    dim = a1.second - a1.first + 1; sum += dim;
    if (b1.second - b1.first + 1 != dim)
        {cerr << "err"; exit(1);}
    lcp = SA.lcp(a1.first, b1.first);
    if (lcp < dim) return s[a1.first + lcp] < s[b1.first + lcp];

    a1 = a2; b1 = b2;

    dim = a1.second - a1.first + 1; sum += dim;
    if (b1.second - b1.first + 1 != dim)
        {cerr << "err"; exit(1);}
    lcp = SA.lcp(a1.first, b1.first);
    if (lcp < dim) return s[a1.first + lcp] < s[b1.first + lcp];

    a1 = a3; b1 = b3;

    dim = a1.second - a1.first + 1; sum += dim;
    if (b1.second - b1.first + 1 != dim)
        {cerr << "err"; exit(1);}
    lcp = SA.lcp(a1.first, b1.first);
    if (lcp < dim) return s[a1.first + lcp] < s[b1.first + lcp];

    /*if (sum != m + dif)
        {cerr << "err"; exit(1);}*/

    return eq;
}

bool cmp(int a, int b) {
    dif = (a > b ? a - b : b - a);

    if (a == b) return false;

    if (min(a, b) + m <= max(a, b)) {
        if (a < b) {
            return conc_cmp({n + 2, n + m + 1}, {a + 1, a + (dif - m)}, {b + 1 - m, b + m - m},
                            {a + 1, a + m}, {a + m + 1, a + dif}, {n + 2, n + m + 1}, true);
        } else {
            swap(a, b);
            return conc_cmp({a + 1, a + m}, {a + m + 1, a + dif}, {n + 2, n + m + 1},
                            {n + 2, n + m + 1}, {a + 1, a + (dif - m)}, {b + 1 - m, b + m - m}, false);
        }
    }

    if (a < b) {
        return conc_cmp({n + 2, n + 1 + dif}, {n + 2 + dif, n + m + 1}, {a + 1, a + dif},
                        {a + 1, a + dif}, {n + 2, n + 1 + (m - dif)}, {n + 2 + (m - dif), n + m + 1}, true);
    } else {
        swap(a, b);
        return conc_cmp({a + 1, a + dif}, {n + 2, n + 1 + (m - dif)}, {n + 2 + (m - dif), n + m + 1},
                        {n + 2, n + 1 + dif}, {n + 2 + dif, n + m + 1}, {a + 1, a + dif}, false);
    }
}

int brute(const query& act) {
    int l, r, x, y, k, pos;
    int le, ri;
    int ans = n + 1;

    l = act.l; r = act.r;
    x = act.x; y = act.y;
    k = act.k;

    pos = (l - y + k - 1) / k;
    pos = max(pos, 0);
    pos *= k;

    for (; pos <= act.r; pos += k) {
        le = max(pos + x, act.l);
        ri = min(pos + y, act.r);

        if (le <= ri)
            ans = min(ans, whole.query(le, ri));
    }

    return ans;
}

void solve_bucket(int k) {
    int i, le, ri;
    int ans;

    if (ids[k].empty()) return;
    for (i = 0; i < k; i++) part_vals[i].clear();
    for (i = 0; i <= n; i++) part_vals[i % k].pb(val[i]);
    for (i = 0; i < k; i++) {
        if (part_vals[i].empty()) continue;
        part[i].init(part_vals[i].size(), &part_vals[i][0], &SA.lg);
    }

    for (auto e : ids[k]) {
        ans = n + 1;

        for (i = Q[e].x; i <= Q[e].y; i++) {
            le = (Q[e].l - i + k - 1) / k;
            ri = (Q[e].r - i) / k;

            if (Q[e].r - i < 0) continue;

            le = max(le, 0);
            ri = min(ri, (int)part_vals[i].size() - 1);

            if (le <= ri)
                ans = min(ans, part[i].query(le, ri));
        }

        Q[e].ans = order[ans];
    }
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%s ", s + 1);
    n = strlen(s + 1);
    s[n + 1] = '#';
    scanf("%s ", s + n + 2);
    m = strlen(s + n + 2);

    SA.init(n + m + 1, s);
    scanf("%d", &q);

    for (i = 1; i <= q; i++) {
        scanf("%d%d%d%d%d", &Q[i].l, &Q[i].r, &Q[i].k, &Q[i].x, &Q[i].y);
    }

    for (i = 0; i <= n; i++) order.pb(i);
    sort(order.begin(), order.end(), cmp);
    for (i = 0; i < order.size(); i++) val[order[i]] = i;

    order.pb(-1);

    //! solve k >= sqrt
    whole.init(n + 1, val, &SA.lg);
    for (i = 1; i <= q; i++) {
        if (Q[i].k <= limit) {
            ids[Q[i].k].pb(i);
            continue;
        }

        Q[i].ans = order[brute(Q[i])];
    }

    for (i = 1; i <= limit; i++)
        solve_bucket(i);

    /*if (Q[1].ans == 16252) {
        //printf("%d %d %d %d %d", Q[1].l, Q[1].r, Q[1].k, Q[1].x, Q[1].y);
        printf("%d %d\n", val[16251], val[16252]);
        return 0;
    }*/


    for (i = 1; i <= q; i++)
        printf("%d ", Q[i].ans);


    return 0;
}

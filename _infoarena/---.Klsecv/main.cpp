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

#define maxN 20011
#define maxLog 16

struct query {
    int l, k, id;

    bool operator<(const query& who)const {
        return l < who.l;
    }
};

struct triple {
    int a, b, id;

    bool operator<(const triple& who)const {
        return mp(a, b) < mp(who.a, who.b);
    }

    bool operator==(const triple& who)const {
        return mp(a, b) == mp(who.a, who.b);
    }
};

int t, ti;
int n, i, q, l, k, pos;
char s[maxN];
vector<query> Q;

int suff[maxLog][maxN];
vector<triple> aux;
vector< pair<int, int> > ord;
int wh[maxN];

int aib[maxN];
int ans[maxN];

int zrs(int x) {
    return (x & (x - 1)) ^ x;
}

void add(int pos, int x) {
    while (pos <= n) {
        aib[pos] += x;
        pos += zrs(pos);
    }
}

int src(int v) {
    int ans = 0;

    for (int step = 1 << maxLog; step > 0; step >>= 1)
        if (ans + step <= n)
            if (aib[ans + step] <= v)
                ans += step, v -= aib[ans];

    return ans;
}

void pre() {
    int i, j;
    int dim, sdim;

    for (i = 1; i <= n; i++) suff[0][i] = s[i] - 'a';
    for (i = 1; i < maxLog; i++) {
        dim = (1 << i);
        sdim = dim >> 1;

        aux.clear();
        for (j = 1; j <= n; j++) {
            if (j + sdim <= n)
                aux.pb({suff[i - 1][j], suff[i - 1][j + sdim], j});
            else
                aux.pb({suff[i - 1][j], -1, j});
        }

        sort(aux.begin(), aux.end());
        suff[i][aux[0].id] = 1;
        for (j = 1; j < aux.size(); j++) {
            if (aux[j - 1] == aux[j])
                suff[i][aux[j].id] = suff[i][aux[j - 1].id];
            else
                suff[i][aux[j].id] = suff[i][aux[j - 1].id] + 1;
        }
    }

    ord.clear();
    for (i = 1; i <= n; i++)
        ord.pb(mp(suff[maxLog - 1][i], i));

    sort(ord.begin(), ord.end());
    for (i = 0; i < ord.size(); i++)
        wh[ ord[i].second ] = i + 1;

}

int main()
{
    freopen("klsecv.in","r",stdin);
    freopen("klsecv.out","w",stdout);

    scanf("%d\n", &t);
    for (ti = 1; ti <= t; ti++) {
        memset(s, 0, sizeof(s));
        scanf("%s", s + 1); n = strlen(s + 1);
        scanf("%d", &q); Q.clear();
        for (i = 1; i <= q; i++) {
            scanf("%d%d", &l, &k);
            Q.pb({l, k, i});
        }

        sort(Q.begin(), Q.end());
        pre();

        memset(aib, 0, sizeof(aib));
        for (i = 1; i <= n; i++) add(i, +1);

        pos = 0;
        for (auto q : Q) {
            while (pos + 1 < q.l) {
                pos++;
                add(wh[n - pos + 1], -1);
            }

            ans[q.id] = ord[src(q.k - 1)].second;
        }

        for (i = 1; i <= q; i++) printf("%d\n", ans[i]);

    }



    return 0;
}

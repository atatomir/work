#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 1000011
#define mod 1000000007

const int dim = 1000000;
const int cnt_tp = 311;

class Buffer {
    public:
        Buffer(int _dim) {
            freopen("test.in", "r", stdin);
            dim = _dim;
            data.resize(dim + 11);
            refill();
        }

        Buffer& operator>>(int &dest) {
            while (!is_digit(data[pos]) && data[pos] != '-')
                if (++pos == dim)
                    refill();

            dest = 0;
            int sgn = 1;

            if (data[pos] == '-') {
                sgn = -1;
                if (++pos == dim)
                    refill();
            }

            while (is_digit(data[pos])) {
                dest = dest * 10 + data[pos] - '0';
                if (++pos == dim)
                    refill();
            }

            dest *= sgn;

            return *this;
        }

    private:
        int dim, pos;
        vector<char> data;

        bool is_digit(char c) {
            return '0' <= c && c <= '9';
        }

        void refill() {
            memset(&data[0], 0, dim);
            fread(&data[0], 1, dim, stdin);
            pos = 0;
        }
};

struct query {
    int r, n, id;

    bool operator<(const query& who)const {
        return r < who.r;
    }
};

int q, i, rr, ss, dd;
vector<query> Q;
query qaux;
ll dp[2][cnt_tp];
ll ans[maxN];

vector<int> divs[maxN];

int cnt;
int tp_id[maxN];
vector< vector<int> > tps;
map< vector<int>, int > M;
vector<int> aux;
int help[cnt_tp];

vector<int> list[cnt_tp];
vector< pair<int, int> > adj[cnt_tp];
vector< pair<int, int> > hp[cnt_tp];

int act;
vector<int> now;

int edges, edges2;


void check(int step) {
    if (step == tps[act].size()) {

        aux = now;
        sort(aux.begin(), aux.end());
        reverse(aux.begin(), aux.end());
        list[act].pb( M[aux] );

        edges++;

        return;
    }

    check(step + 1);
    now.pb(0);
    for (int i = 1; i <= tps[act][step]; i++) {
        now[ now.size() - 1 ] = i;
        check(step + 1);
    }

    now.pop_back();
}

void pre() {
    ll i, j;
    ll vv, cc;

    cnt = -1;

    tps.pb({});
    M[{}] = ++cnt;

    tps.pb({1});
    M[{1}] = ++cnt;

    tp_id[1] = 0;

    for (i = 2; i <= dim; i++) {
        if (divs[i].size()) {

            vv = i;
            aux.clear();

            for (auto e : divs[i]) {
                cc = 0;
                while (vv % e == 0) {
                    vv /= e;
                    cc++;
                }

                aux.pb(cc);
            }

            sort(aux.begin(), aux.end());
            reverse(aux.begin(), aux.end());

            if (M[aux] == 0) {
                tps.pb(aux);
                M[aux] = ++cnt;
            }

            tp_id[i] = M[aux];

            continue;
        }

        tp_id[i] = 1;
        for (j = i; j <= dim; j += i)
            divs[j].pb(i);
    }

    for (i = 0; i < cnt; i++) {
        act = i;

        for (int conf = (1 << tps[i].size()) - 1; conf > 0; conf--) {
            aux = tps[i];

            for (int pp = 0; pp < tps[i].size(); pp++)
                if ( (conf >> pp) & 1 )
                    aux[pp]--;

            for (int pp = 0; pp < aux.size(); pp++) {
                if (aux[pp] == 0) {
                    aux[pp] = aux.back();
                    aux.pop_back();
                    pp--; continue;
                }
            }

            sort(aux.begin(), aux.end());
            reverse(aux.begin(), aux.end());

            if ( __builtin_popcount(conf) % 2 == 1 )
                hp[i].pb(mp(M[aux], +1));
            else
                hp[i].pb(mp(M[aux], -1));
        }

        if (tps[i].empty()) {
            check(0);
        } else {
            aux = tps[i];
            aux[0]--;

            if (aux[0] == 0) {
                swap(aux[0], aux.back());
                aux.pop_back();
            }

            sort(aux.begin(), aux.end());
            reverse(aux.begin(), aux.end());

            help[i] = M[aux];
            now = {tps[i][0]};
            check(1);
        }
    }

    for (i = 0; i < cnt; i++) {
        sort(list[i].begin(), list[i].end());

        int l, r;

        for (l = 0; l < list[i].size(); l = r) {
            for (r = l; r < list[i].size(); r++)
                if (list[i][l] != list[i][r])
                    break;

            adj[i].pb(mp(list[i][l], r - l));
            edges2++;
        }
    }
}

void get_next() {
    int i;

    rr++;

    memset(dp[dd], 0, sizeof(dp[dd]));
    dp[dd][0] = 1;

    for (i = 0; i < cnt; i++) {
        /*if (i != 0) dp[dd][i] += dp[dd][ help[i] ];

        for (auto e : adj[i])
            dp[dd][i] += (dp[ss][ e.first ] * e.second) % mod;
        dp[dd][i] %= mod;*/

        if (i == 0) continue;
        for (auto e : hp[i])
            dp[dd][i] += (1LL * (mod + e.second) * dp[dd][e.first]) % mod;
        dp[dd][i] += dp[ss][i];
        dp[dd][i] %= mod;
    }

    swap(ss, dd);
}

int main()
{
    Buffer fin(1 << 20);

    pre();
    cerr << cnt << ' ';
    cerr << edges << ' ';
    cerr << edges2 << '\n';

    fin >> q;
    for (i = 1; i <= q; i++) {
        fin >> qaux.r >> qaux.n;
        qaux.id = i;
        Q.pb(qaux);
    }

    ss = 0; dd = 1;
    for (i = 0; i < cnt; i++) {
        dp[ss][i] = 1LL << tps[i].size();
        dp[ss][i] %= mod;
    }

    sort(Q.begin(), Q.end());

    rr = 0;
    for (auto e : Q) {
        while (rr < e.r)
            get_next();

        ans[e.id] = dp[ss][ tp_id[e.n] ];
    }

    for (i = 1; i <= q; i++)
        printf("%lld\n", ans[i]);


    return 0;
}

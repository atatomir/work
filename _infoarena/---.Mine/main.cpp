#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 10011
#define maxW 1000011

#define lSon (node << 1)
#define rSon (lSon | 1)
#define inf 1000000000

class Buffer {
    public:
        Buffer(string name, int _dim) {
            freopen(name.c_str(), "r", stdin);
            dim = _dim;
            data.resize(dim);

            reFill();
        }

        template<class T>
        Buffer& operator>>(T &who) {
            bool sign = false;

            while (!isDigit(data[pos]) && data[pos] != '-')
                if (++pos == dim) reFill();

            if (data[pos] == '-') {
                sign = true;
                if (++pos == dim) reFill();
            }

            who = 0;
            while (isDigit(data[pos])) {
                who = who * 10 + data[pos] - '0';
                if (++pos == dim) reFill();
            }

            if (sign) who *= -1;
            return *this;
        }

    private:
        int dim, pos;
        vector<char> data;

        bool isDigit(char c) {
            return ('0' <= c && c <= '9');
        }

        void reFill() {
            pos = 0;
            memset(&data[0], 0, dim);
            fread(&data[0], 1, dim, stdin);
        }
};

Buffer fin("mine.in", 1 << 20);

int qq, vv;
class aint {
    public:
        void init(int _n, int *_data, int *_from) {
            n = _n;
            data = _data;
            from = _from;

            initTree(1, 1, n);
        }

        void update(int node, int l, int r) {
            if (l == r) {
                data[node] = vv;
                return;
            }

            int mid = (l + r) >> 1;
            if (qq <= mid)
                update(lSon, l, mid);
            else
                update(rSon, mid + 1, r);

            data[node] = max(data[lSon], data[rSon]);
        }

        int binary(int node, int l, int r) {
            if (data[node] < vv)
                return r;
            if (l == r)
                return l - 1;

            int mid = (l + r) >> 1;

            if (data[lSon] >= vv)
                return binary(lSon, l, mid);
            else
                return binary(rSon, mid + 1, r);
        }

    private:
        int *data, *from;
        int n;

        void initTree(int node, int l, int r) {
            if (l == r) {
                data[node] = from[l];
                return;
            }

            int mid = (l + r) >> 1;
            initTree(lSon, l, mid);
            initTree(rSon, mid + 1, r);

            data[node] = max(data[lSon], data[rSon]);
        }
};

int n, m, i, x, y, w;
vector< pair<int, int> > list[maxN];
int E[maxW];

aint work;
int aint_data[maxW << 2];
int pos;

int dp[maxN];
bool updated[maxN];
//! node; val

vector<int> *H[maxW];
bool done[maxW];

int getPay(int v) {
    if (aint_data[1] < v) return w + 1;

    vv = v;
    return work.binary(1, 1, w) + 1;
}

void init_vect(int id) {
    done[id] = true;
    H[id] = new vector<int>(0);
}

int main()
{
    //freopen("mine.in","r",stdin);
    freopen("mine.out","w",stdout);

    fin >> n >> m;
    for (i = 1; i <= m; i++) {
        fin >> x >> y >> w;
        list[x].pb(mp(y, w));
        list[y].pb(mp(x, w));
    }

    fin >> w;
    for (i = 1; i <= w; i++)
        fin >> E[i];

    work.init(w, aint_data, E);

    //!---------------------------

    for (i = 1; i <= n; i++)
        dp[i] = inf;

    int h_pos = 0;
    init_vect(0);
    H[0]->pb(1);
    dp[1] = 0;

    while (true) {
        while (h_pos <= w) {
            if (done[h_pos] == true)
                if (H[h_pos]->size() > 0)
                    break;
            h_pos++;
        }
        if (h_pos == w + 1) break;

        int act = H[h_pos]->back(); H[h_pos]->pop_back();

        if (updated[act]) continue;
        updated[act] = true;

        while (pos < dp[act]) {
            qq = ++pos; vv = -1;
            work.update(1, 1, w);
        }

        for (auto e : list[act]) {
            int to = e.first;
            int pay = getPay(e.second);

            if (dp[to] <= pay) continue;
            dp[to] = pay;

            if (done[pay] == false)
                init_vect(pay);
            H[pay]->pb(to);
        }

        if (updated[n]) break;
    }

    if (dp[n] > w)
        printf("-1");
    else
        printf("%d", dp[n]);

    return 0;
}

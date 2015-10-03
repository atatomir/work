#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>

using namespace std;

#define pb push_back
#define mp make_pair

#define lSon (node << 1)
#define rSon (lSon | 1)

#define maxN 250011

class Buffer {
    public:
        Buffer(string name, int _dim) {
            freopen(name.c_str(), "r", stdin);
            dim = _dim;
            data.resize(dim);
            reFill();
        }

        Buffer& operator>>(int &dest) {
            while (!isDigit(data[pos])) {
                if (++pos == dim) reFill();
            }
            dest = 0;
            while(isDigit(data[pos])) {
                dest = dest * 10 + data[pos] - '0';
                if (++pos == dim) reFill();
            }
            return *this;
        }

    private:
        int dim, pos;
        vector<char> data;

        void reFill() {
            pos = 0;
            memset(&data[0], 0, dim);
            fread(&data[0], 1, dim, stdin);
        }
        bool isDigit(char c) {
            return ('0' <= c) && (c <= '9');
        }
};

struct qStruct {
    int pos, from, to, cost;
    bool add;

    qStruct(int _pos, int _from, int _to, int _cost, bool _add) {
        pos = _pos;
        from = _from;
        to = _to;
        add = _add;
        cost = _cost;
    }
    bool operator<(const qStruct& who)const {
        return pos < who.pos;
    }
} nowUpdated(1,1,1,1,1);

class Aint {
    public:
        void init(int _n, multiset<int> *_data, int *_dp) {
            dim = _n;
            data = _data;
            dp = _dp;
            makeTree(1, 1, dim);
        }

        void addInterv(int node, int l, int r) {
            if (nowUpdated.from <= l && r <= nowUpdated.to) {
                data[node].insert(nowUpdated.cost);
                balance(node, l == r);
                return;
            }

            int mid = (l + r) >> 1;
            if (nowUpdated.from <= mid) addInterv(lSon, l, mid);
            if (nowUpdated.to   >  mid) addInterv(rSon, mid + 1, r);

            balance(node, false);
        }

        void delInterv(int node, int l, int r) {
            if (nowUpdated.from <= l && r <= nowUpdated.to) {
                data[node].erase(nowUpdated.cost);
                balance(node, l == r);
                return;
            }

            int mid = (l + r) >> 1;
            if (nowUpdated.from <= mid) delInterv(lSon, l, mid);
            if (nowUpdated.to   >  mid) delInterv(rSon, mid + 1, r);

            balance(node, false);
        }

        int getBest() {
            return dp[1];
        }

    private:
        int dim;
        multiset<int> *data;
        int *dp;

        void makeTree(int node, int l, int r) {
            data[node].clear();
            data[node].insert(0);
            dp[node] = 0;

            if (l == r) return;

            int mid = (l + r) >> 1;
            makeTree(lSon, l, mid);
            makeTree(rSon, mid + 1, r);
        }

        void balance(int node, bool leaf) {
            auto it = data[node].end(); it--;
            dp[node] = *it;

            if (!leaf) dp[node] = max(dp[node], min(dp[lSon], dp[rSon]));
        }
};

int dim, n, L, i, ans;
int xx1, xx2, yy1, yy2, cost;
vector<qStruct> Events;

//!------------------------------------
multiset<int> aint_data[maxN << 2];
int aint_dp[maxN << 2];
Aint work;
//!------------------------------------

void coord_balance() {
    xx1 = max(xx1 - L + 1, 1);
    yy1 = max(yy1 - L + 1, 1);

    xx2 = min(xx2, dim);
    yy2 = min(yy2, dim);
}

int norm_y[maxN];
int aint_dim = 0;
vector<int> aux;
void normalizare() {
    aux.clear();
    aux.pb(1); aux.pb(dim);

    for (int i = 0; i < Events.size(); i++) {
        aux.pb(Events[i].from);
        aux.pb( min(Events[i].to + 1, dim) );
    }

    sort(aux.begin(), aux.end());
    aux.resize(unique(aux.begin(), aux.end()) - aux.begin());
    for (auto e : aux) norm_y[e] = ++aint_dim;

    for (int i = 1; i <= dim; i++)
        if (norm_y[i] == 0)
            norm_y[i] = norm_y[i - 1];

    for (int i = 0; i < Events.size(); i++) {
        Events[i].from = norm_y[Events[i].from];
        Events[i].to = norm_y[Events[i].to];
    }
}

void addEvent(int id) {
    nowUpdated = Events[id];
    if (Events[id].add)
        work.addInterv(1, 1, aint_dim);
    else
        work.delInterv(1, 1, aint_dim);
}

int main()
{
    Buffer fin("mm.in", 1 << 20);
    freopen("mm.out", "w", stdout);

    fin >> dim >> L >> n;
    dim -= L - 1;

    for (i = 1; i <= n; i++) {
        fin >> xx1 >> yy1 >> xx2 >> yy2 >> cost;
        coord_balance();

        Events.pb(qStruct(yy1, xx1, xx2, cost, true));
        Events.pb(qStruct(yy2 + 1, xx1, xx2, cost, false));
    }

    normalizare();

    sort(Events.begin(), Events.end());
    work.init(aint_dim, aint_data, aint_dp);
    ans = 2000000111;

    int ind = 0;
    for (i = 1; i <= dim; i++) {
        while (ind != Events.size()) {
            if (Events[ind].pos > i) break;
            addEvent(ind++);
        }

        ans = min(ans, work.getBest());
    }

    printf("%d", ans);
    cerr << ans;

    return 0;
}

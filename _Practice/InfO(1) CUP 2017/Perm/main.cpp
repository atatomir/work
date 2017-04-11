#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cstdio>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 70011
#define mod 1000000007

class Buffer {
    public:
        Buffer(string name, int _dim) {
            if (name != "")
                freopen(name.c_str(), "r", stdin);
            dim = _dim;
            data.resize(dim + 11);
            refill();
        }

        Buffer& operator>>(int &dest) {
            int sign = +1;
            dest = 0;

            while (!is_digit(data[pos]) && data[pos] != '-')
                if (++pos == dim)
                    refill();

            if (data[pos] == '-') {
                sign = -1;
                if (++pos == dim)
                    refill();
            }

            while (is_digit(data[pos])) {
                dest = dest * 10 + data[pos] - '0';
                if (++pos == dim)
                    refill();
            }

            dest *= sign;
            return *this;
        }

        Buffer& operator>>(string& s) {
            s = "";

            while (!is_digit(data[pos]))
                if (++pos == dim)
                    refill();

            while (is_digit(data[pos])) {
                s += data[pos];
                if (++pos == dim)
                    refill();
            }

            return *this;
        }


    private:
        int pos, dim;
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

const ll base = 1000000000000000000LL;
const ll sz = 21000 / 17;
const int dig = 18;

struct bignum {
    int dim;
    vector<ll> data;

    void init() {
        dim = 1;
        data = {0, 0};
    }

    void init(string s) {
        int i, j;
        ll aux;

        data = {0};
        dim = 0;

        for (i = s.size() - 1; i >= 0; i -= dig) {
            aux = 0;
            for (j = max(0, i - dig + 1); j <= i; j++)
                aux = aux * 10 + s[j] - '0';
            dim++;
            data.pb(aux);
        }
    }

    void operator+=(const bignum& who) {
        int i, dimi;

        dim = max(dim, who.dim);
        dimi = min(dim, who.dim);

        while (data.size() < dim + 2) data.pb(0);
        for (i = 1; i <= dimi; i++) data[i] += who.data[i];
        for (i = 1; i <= dim; i++) {
            if (data[i] < base) continue;
            data[i + 1]++;
            data[i] -= base;
        }
        if (data[dim + 1] != 0) dim++;
    }

    void operator-=(const bignum& who) {
        int i, dimi;

        dim = max(dim, who.dim);
        dimi = min(dim, who.dim);

        while (data.size() < dim + 2) data.pb(0);
        for (i = 1; i <= dimi; i++) data[i] -= who.data[i];
        for (i = 1; i <= dim; i++) {
            while (data[i] < 0) {
                data[i] += base;
                data[i + 1]--;
            }
        }

        while (dim > 1 && data[dim] == 0) dim--;
        while (data.size() > dim + 2) data.pop_back();
    }

    bool operator<(const bignum& who) {
        if (dim < who.dim) return true;
        if (dim > who.dim) return false;

        int i;
        for (i = dim; i > 0; i--) {
            if (data[i] < who.data[i]) return true;
            if (data[i] > who.data[i]) return false;
        }

        return false;
    }
};

int act_id;
bignum delta[maxN], sum[maxN];
bignum aux, aux2;
vector<int> sol;

struct treap {
    treap *son[2];
    int id;
    int key;

    treap() {
        son[0] = son[1] = NULL;
        id = 0;
        key = -1;
    }

    treap(int _id, treap* lson, treap* rson) {
        id = _id;
        son[0] = lson;
        son[1] = rson;
        key = rand() % mod;
    }
} *nil;

void recomp(treap* &act) {
    if (act == nil) return;
    sum[act->id] = delta[act->id];
    sum[act->id] += sum[act->son[0]->id];
    sum[act->id] += sum[act->son[1]->id];
}

void rotleft(treap* &act) {
    treap *aux = act->son[0];
    act->son[0] = aux->son[1];
    aux->son[1] = act;
    act = aux;

    recomp(act);
    recomp(act->son[1]);
}

void rotright(treap* &act) {
    treap *aux = act->son[1];
    act->son[1] = aux->son[0];
    aux->son[0] = act;
    act = aux;

    recomp(act);
    recomp(act->son[0]);
}

void balance(treap* &act) {
    if (act == nil) return;

    if (act->son[0]->key > act->key)
        rotleft(act);
    else
    if (act->son[1]->key > act->key)
        rotright(act);

    recomp(act);
}

void add(treap* &act) {
    if (act == nil) {
        act = new treap(act_id, nil, nil);
        return;
    }

    aux2 = sum[act->son[0]->id];
    aux2 += delta[act->id];

    if (aux2 < aux) {
        aux -= aux2;
        add(act->son[1]);
    } else {
        add(act->son[0]);
    }

    balance(act);
}

void dfs(treap* act) {
    if (act == nil) return;
    dfs(act->son[0]);
    sol.pb(act->id);
    dfs(act->son[1]);
}

int n, i;
bignum act, last;
string s;
treap* Head;

int ans[maxN];

int main()
{
    Buffer fin("input", 1 << 20);
    //freopen("input","r",stdin);
    freopen("output","w",stdout);


    srand(time(NULL));
    nil = new treap();
    Head = nil;

    delta[0].init();
    sum[0].init();

    fin >> n;
    last.init();
    for (i = 1; i <= n; i++) {
        fin >> s;
        act.init(s);

        delta[i] = act;
        delta[i] -= last;
        sum[i] = delta[i];

        last = act;
    }

    for (i = 1; i <= n; i++) {
        act_id = i;
        aux = delta[i];
        add(Head);

        /*sol.clear();
        dfs(Head);
        for (auto e : sol) cerr << e << ' ';
        cerr << '\n';*/
    }

    sol.clear();
    dfs(Head);

    for (i = 0; i < n; i++)
        ans[ sol[i] ] = i + 1;

    for (i = 1; i <= n; i++) printf("%d ", ans[i]);


    return 0;
}

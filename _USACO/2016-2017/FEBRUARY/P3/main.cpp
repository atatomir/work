#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 100011
#define mod 1000000007

class Buffer {
    public:
        Buffer(string name, int _dim) {
            freopen(name.c_str(), "r", stdin);
            dim = _dim;
            data.resize(dim + 11);
            refill();
        }

        Buffer& operator>>(int &dest) {
            while (!is_digit(data[pos]))
                if (++pos == dim)
                    refill();

            dest = 0;
            while (is_digit(data[pos])) {
                dest = dest * 10 + data[pos] - '0';
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
            pos = 0;
            memset(&data[0], 0, dim);
            fread(&data[0], 1, dim, stdin);
        }
};

struct treap {
    treap *son[2];
    int cnt, val;
    int key;

    treap() {
        son[0] = son[1] = NULL;
        val = 0;
        cnt = 0;
        key = -1;
    }

    treap(int _val, treap* lson, treap* rson) {
        val = _val;
        son[0] = lson;
        son[1] = rson;
        cnt = 1;
        key = rand() % mod;
    }
} *nil;

void recomp(treap* &act) {
    if (act == nil) return;
    act->cnt = act->son[0]->cnt + act->son[1]->cnt + 1;
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

void add(treap* &act, int v) {
    if (act == nil) {
        act = new treap(v, nil, nil);
        return;
    }

    if (v < act->val)
        add(act->son[0], v);
    else
        add(act->son[1], v);

    balance(act);
}

void erase(treap* &act, int v) {
    if (act->son[0] == nil && act->son[1] == nil) {
        act = nil;
        return;
    }

    if (act->val == v) {
        if (act->son[0]->key > act->son[1]->key)
            rotleft(act);
        else
            rotright(act);
    }

    if (v < act->val) erase(act->son[0], v);
    if (v > act->val) erase(act->son[1], v);

    balance(act);
}

int lower(treap* act, int v) {
    if (act == nil) return 0;

    if (v == act->val) return act->cnt - act->son[1]->cnt;

    if (v < act->val)
        return lower(act->son[0], v);
    else
        return act->cnt - act->son[1]->cnt + lower(act->son[1], v);
}



int n, k, i;
int a[maxN], b[maxN], wha[maxN], whb[maxN];
treap* aib[maxN];
int aib2[maxN];

ll ans;


int zrs(int x) {
    return (x ^ (x - 1)) & x;
}

void add_aib(int pos, int x) {
    while (pos <= n) {
        add(aib[pos], x);
        pos += zrs(pos);
    }
}

void rm_aib(int pos, int x) {
    while (pos <= n) {
        erase(aib[pos], x);
        pos += zrs(pos);
    }
}

int que_aib(int pos, int v) {
    int ans = 0;

    while (pos > 0) {
        ans += aib[pos]->cnt - lower(aib[pos], v);
        pos -= zrs(pos);
    }

    return ans;
}

int que_aib2(int pos, int v) {
    int ans = 0;

    while (pos > 0) {
        ans += lower(aib[pos], v);
        pos -= zrs(pos);
    }

    return ans;
}


void add_aib2(int pos, int x) {
    while (pos <= n) {
        aib2[pos] += x;
        pos += zrs(pos);
    }
}

int sum_aib2(int pos) {
    int ans = 0;
    while (pos > 0) {
        ans += aib2[pos];
        pos -= zrs(pos);
    }

    return ans;
}


int main()
{
    Buffer fin("friendcross.in", 1 << 20);
    freopen("friendcross.out","w",stdout);

    srand(time(NULL));
    nil = new treap();

    fin >> n >> k;
    for (i = 1; i <= n; i++) fin >> a[i], wha[a[i]] = i, aib[i] = nil;
    for (i = 1; i <= n; i++) fin >> b[i], whb[b[i]] = i;

    for (i = 1; i <= n; i++) {
        int pos = wha[i];
        int val = whb[i];

        ans += que_aib(pos, val);
        ans += sum_aib2(val) - que_aib2(pos, val);

        add_aib(pos, val);
        add_aib2(val, +1);

        if (i > k) {
            rm_aib(wha[i - k], whb[i - k]);
            add_aib2(whb[i - k], -1);
        }
    }

    memset(aib2, 0, sizeof(aib2));

    ans *= -1;
    for (i = 1; i <= n; i++) {
        int val = a[i];
        int p = whb[val];

        ans += sum_aib2(n) - sum_aib2(p);
        add_aib2(p, +1);
    }

    printf("%lld", ans);
    cerr << ans;


    return 0;
}

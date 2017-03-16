#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 200011
#define lSon (node << 1)
#define rSon (lSon | 1)

#define mod 1000000007

struct treap {
    treap *son[2];
    pair<int, int> val;
    int same;
    int key;

    treap() {
        son[0] = son[1] = NULL;
        val = mp(0, 0);
        same = 0;
        key = -1;
    }

    treap(pair<int, int> _val, treap* lson, treap* rson) {
        val = _val;
        son[0] = lson;
        son[1] = rson;
        same = val.second;
        key = rand() % mod;
    }
} *nil;

void recomp(treap* &act) {
    if (act == nil) return;
    act->same = act->val.second;
    if (act->son[0]->same != act->same && act->son[0] != nil) act->same = -1;
    if (act->son[1]->same != act->same && act->son[1] != nil) act->same = -1;
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

void add(treap* &act, pair<int, int> v) {
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

void erase(treap* &act, pair<int, int> v) {
    if (act->son[0] == nil && act->son[1] == nil) {
        act = nil;
        return;
    }

    if (act->val == v) {
        if (act->son[0]->key > act->son[1]->key) {
            rotleft(act);
            erase(act->son[1], v);
        } else {
            rotright(act);
            erase(act->son[0], v);
        }

        balance(act);
        return;
    }

    if (v < act->val) erase(act->son[0], v);
    if (v > act->val) erase(act->son[1], v);

    balance(act);
}

pair<int, int> first_dif(treap* act, int dif) {
    if (act->same == dif || act == nil)
        return mp(0, 0);

    if (act->son[0]->same != dif && act->son[0] != nil)
        return first_dif(act->son[0], dif);

    if (act->val.second != dif)
        return act->val;

    return first_dif(act->son[1], dif);
}

struct edge {
    int x, y, cost;

    bool operator<(const edge& who)const {
        return cost < who.cost;
    }
};

struct aint {
    int n;
    vector<int> data;

    void init(int _n) {
        n = _n;
        data = vector<int>(n * 4 + 11, 0);
    }

    void upd(int node, int l, int r, int pos, int v) {
        if (l == r) {
            data[node] = v;
            return;
        }

        int mid = (l + r) >> 1;
        if (pos <= mid)
            upd(lSon, l, mid, pos, v);
        else
            upd(rSon, mid + 1, r, pos, v);

        data[node] = min(data[lSon], data[rSon]);
    }
};

int n, m, k, q, i, x, y, z;
int col[maxN];
vector<edge> E;
pair<int, int> op[maxN];
int dad[maxN];

vector< pair<int, int> > list[maxN];
int lvl[maxN];
int daddy[maxN];
int daddy_edge[maxN];

treap *Head[maxN];
aint work;


int Find(int x) {
    if (dad[x] == x)
        return x;
    dad[x] = Find(dad[x]);
    return dad[x];
}

bool Merge(int x, int y) {
    x = Find(x);
    y = Find(y);

    if (x == y) return false;
    dad[x] = y;
    return true;
}

void dfs(int node, int root) {
    for (auto to : list[node]) {
        if (to.first == root)
            continue;

        lvl[to.first] = lvl[node] + 1;
        daddy[to.first] = node;
        daddy_edge[to.first] = to.second;
        dfs(to.first, node);

        add(Head[node], mp(to.second, col[to.first]));
    }
}

int compute(int node) {
    auto act = first_dif(Head[node], col[node]);
    if (act == mp(0, 0))
        return 1000000000;
    return act.first;
}

int main()
{
    srand(time(NULL));

    freopen("grass.in","r",stdin);
    freopen("grass.out","w",stdout);

    scanf("%d%d%d%d", &n, &m, &k, &q);
    for (i = 1; i <= m; i++) {
        scanf("%d%d%d", &x, &y, &z);
        E.pb({x, y, z});
    }
    for (i = 1; i <= n; i++) scanf("%d", &col[i]);

    for (i = 1; i <= q; i++) {
        scanf("%d%d", &op[i].first, &op[i].second);
    }

    sort(E.begin(), E.end());

    for (i = 1; i <= n; i++) dad[i] = i;

    for (auto e : E) {
        if (Merge(e.x, e.y)) {
            list[e.x].pb(mp(e.y, e.cost));
            list[e.y].pb(mp(e.x, e.cost));
        }
    }

    nil = new treap();
    for (i = 1; i <= n; i++) Head[i] = nil;
    work.init(n);

    daddy_edge[0] = 1000000000;
    dfs(1, 0);

    for (i = 1; i <= n; i++)
        work.upd(1, 1, n, i, compute(i));

    for (i = 1; i <= q; i++) {
        int A = op[i].first;
        int B = op[i].second;

        if (daddy[A]) {
            int dd = daddy[A];
            erase(Head[dd], mp(daddy_edge[A], col[A]));
            add(Head[dd], mp(daddy_edge[A], B));
            work.upd(1, 1, n, dd, compute(dd));
        }

        col[A] = B;
        work.upd(1, 1, n, A, compute(A));
        printf("%d\n", work.data[1]);
    }



    return 0;
}

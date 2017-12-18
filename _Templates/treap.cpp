#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <functional>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define mod 1000000007
#define maxN 100011

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

void walk(treap* act, function<void(int)> callback) {
    if (act == nil) return;
    callback(act->val);

    walk(act->son[0], callback);
    walk(act->son[1], callback);
}

int n, i, x, y, xx, yy;
vector< pair<int, int> > edges;
int dad[maxN];
treap* Head[maxN];
ll ans;

int Find(int x) {
    if (dad[x] == x) return x;
    dad[x] = Find(dad[x]);
    return dad[x];
}

int main()
{
    //freopen("test.in","r",stdin);
    srand(time(NULL));
    nil = new treap();

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        dad[i] = i;
        Head[i] = nil;
        add(Head[i], i);

        if (i != n) {
            scanf("%d%d", &x, &y);
            edges.pb(mp(x, y));
        }
    }

    sort(edges.begin(), edges.end(), [](const pair<int, int>& a, const pair<int, int>& b)->bool const {
        return a.first + a.second < b.first + b.second;
    });


    for (auto e : edges) {
        x = e.first;
        y = e.second;

        xx = Find(x);
        yy = Find(y);

        if (Head[xx]->cnt > Head[yy]->cnt) swap(xx, yy);
        dad[xx] = yy;

        walk(Head[xx], [&](int v)->void {
            ans += 1LL * Head[yy]->cnt - lower(Head[yy], x + y - v - 1);
        });

        walk(Head[xx], [&](int v)->void {
            add(Head[yy], v);
        });
    }

    printf("%lld", ans);


    return 0;
}

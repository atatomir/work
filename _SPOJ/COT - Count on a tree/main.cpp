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

#define maxN 100011
#define maxLog 20

struct node {
    node* son[2];
    int cnt;

    node() {
        son[0] = son[1] = NULL;
        cnt = 0;
    }
};

node* init(int l, int r) {
    node *act = new node();
    if (l == r) return act;

    int mid = (l + r) >> 1;
    act->son[0] = init(l, mid);
    act->son[1] = init(mid + 1, r);

    return act;
}

node* clone(node* act, int l, int r, int pos) {
    node *cl = new node();
    cl->son[0] = act->son[0];
    cl->son[1] = act->son[1];
    cl->cnt = act->cnt;

    if (l == r) return cl;

    int mid = (l + r) >> 1;
    if (pos <= mid)
        cl->son[0] = clone(act->son[0], l, mid, pos);
    else
        cl->son[1] = clone(act->son[1], mid + 1, r, pos);

    return cl;
}

void update(node* act, int l, int r, int pos, int val) {
    act->cnt += val;
    if (l == r) return;

    int mid = (l + r) >> 1;
    if (pos <= mid)
        update(act->son[0], l, mid, pos, val);
    else
        update(act->son[1], mid + 1, r, pos, val);
}


//! -----------------------------------------


int n, m, i, x, y, def, k;
vector<int> list[maxN];
bool us[maxN];

int W[maxN];
int id[maxN];
vector<int> norm;

int lvl[maxN];
int dad[maxLog][maxN];
node* Head[maxN];


void dfs(int node) {
    us[node] = true;

    for (int i = 0; i < list[node].size(); i++) {
        int to = list[node][i];
        if (us[to]) continue;

        dad[0][to] = node;
        lvl[to] = lvl[node] + 1;


        Head[to] = clone(Head[node], 1, def, id[to]);
        update(Head[to], 1, def, id[to], +1);

        dfs(to);
    }
}

void compute_dad() {
    for (int i = 1; i < maxLog; i++)
        for (int j = 1; j <= n; j++)
            dad[i][j] = dad[i - 1][ dad[i - 1][j] ];
}

int go_up(int node, int how) {
    for (int i = 0; how; i++, how >>= 1)
        if (how & 1)
            node = dad[i][node];

    return node;
}

int get_lca(int x, int y) {
    if (lvl[x] > lvl[y]) swap(x, y);

    y = go_up(y, lvl[y] - lvl[x]);
    if (x == y) return x;

    for (int i = maxLog - 1; i >= 0; i--)
        if (dad[i][x] != dad[i][y])
            x = dad[i][x], y = dad[i][y];

    return dad[0][x];
}

int solve(int x, int y, int k) {
    int i, l, r;
    int lca = get_lca(x, y);

    node* p1 = Head[x];
    node* p2 = Head[y];
    node* n1 = Head[lca];
    node* n2 = Head[dad[0][lca]];

    l = 1; r = def;

    while (l != r) {
        int mid = (l + r >> 1);

        int how_left = p1->son[0]->cnt + p2->son[0]->cnt - n1->son[0]->cnt - n2->son[0]->cnt;
        if (how_left >= k) {
            r = mid;

            p1 = p1->son[0];
            p2 = p2->son[0];
            n1 = n1->son[0];
            n2 = n2->son[0];
        } else {
            l = mid + 1;
            k -= how_left;

            p1 = p1->son[1];
            p2 = p2->son[1];
            n1 = n1->son[1];
            n2 = n2->son[1];
        }
    }

    return l;
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) {
        scanf("%d", &W[i]);
        norm.pb(W[i]);
    }
    for (i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        list[x].pb(y);
        list[y].pb(x);
    }

    sort(norm.begin(), norm.end());
    norm.resize(unique(norm.begin(), norm.end()) - norm.begin());
    def = norm.size();

    for (i = 1; i <= n; i++)
        id[i] = lower_bound(norm.begin(), norm.end(), W[i]) - norm.begin() + 1;

    Head[0] = init(1, def);
    list[0].pb(1);

    dfs(0);
    compute_dad();

    for (i = 1; i <= m; i++) {
        scanf("%d%d%d", &x, &y, &k);
        printf("%d\n", norm[ solve(x, y, k) - 1 ]);
    }



    return 0;
}

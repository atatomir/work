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

#define maxN 25011
#define maxLog 20

struct node {
    node* son[2];

    node() {
        son[0] = son[1] = NULL;
    }
};

int t, ti;
int n, i, x;
node* Head, *nil;
ll ans;
int best;

void add_nr(int x) {
    node* act;
    int bit, go;

    act = Head;
    for (bit = maxLog - 1; bit >= 0; bit--) {
        go = (x >> bit) & 1;
        if (act->son[go] == NULL) act->son[go] = new node();
        act = act->son[go];
    }
}

void parall(node* n1, node* n2, int nr) {
    int go;

    if (n1->son[0] == NULL && n1->son[1] == NULL) {
        best = min(best, nr);
        return;
    }

    for (go = 0; go < 2; go++) {
        if (n1->son[go] != NULL) {
            if (n2->son[go] != NULL) {
                parall(n1->son[go], n2->son[go], nr << 1);
            } else {
                if (n2->son[1 ^ go] != NULL) {
                    parall(n1->son[go], n2->son[1 ^ go], (nr << 1) | 1);
                } else {
                    cerr << "Impossible is now possible\n";
                }
            }
        }
    }
}

int dfs(node *act) {
    int dim = 1;

    if (act->son[0] == NULL && act->son[1] == NULL)
        return dim;
    if (act->son[0] == NULL)
        return dim + dfs(act->son[1]);
    if (act->son[1] == NULL)
        return dim + dfs(act->son[0]);

    int d1 = dfs(act->son[0]);
    int d2 = dfs(act->son[1]);
    dim += d1 + d2;

    best = 1 << 30;
    if (d1 <= d2)
        parall(act->son[0], act->son[1], 1);
    else
        parall(act->son[1], act->son[0], 1);

    ans += 1LL * best;

    return dim;
}

void rm(node* act) {
    if (act->son[0]) rm(act->son[0]);
    if (act->son[1]) rm(act->son[1]);
    delete act;
}

int main()
{
    freopen("yamstp.in","r",stdin);
    freopen("yamstp.out","w",stdout);

    nil = new node();

    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++) {
        Head = new node();

        scanf("%d", &n);
        for (i = 1; i <= n; i++) {
            scanf("%d", &x);
            add_nr(x);
        }

        ans = 0;
        dfs(Head);
        printf("%lld\n", ans);

        rm(Head);
    }


    return 0;
}

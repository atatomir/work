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

struct node {
    node* son[2];
    int val;

    node() {
        son[0] = son[1] = NULL;
        val = 0;
    }
};

int n, m, i, j, x;
node* Head;

ll hsh;
vector<ll> ids;



void insert(node* &act, int val) {
    if (act == NULL) {
        act = new node();
        act->val = val;
        return;
    }

    if (val < act->val)
        insert(act->son[0], val);
    else
        insert(act->son[1], val);
}

void dfs(node *act) {
    int aux = 0;

    if (act->son[0] != NULL) aux |= 1;
    if (act->son[1] != NULL) aux |= 2;

    hsh = (hsh << 2) | aux;
    if (act->son[0] != NULL)
        dfs(act->son[0]);
    if (act->son[1] != NULL)
        dfs(act->son[1]);
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) {
        Head = NULL;

        for (j = 1; j <= m; j++) scanf("%d", &x), insert(Head, x);

        hsh = 0;
        dfs(Head);
        ids.pb(hsh);

        cerr << hsh << '\n';
    }

    sort(ids.begin(), ids.end());
    ids.resize(unique(ids.begin(), ids.end()) - ids.begin());

    printf("%d", ids.size());


    return 0;
}

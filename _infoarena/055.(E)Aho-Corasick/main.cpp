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
#define ll long long

#define maxN 1000011
#define maxM 10011
#define maxWords 111

struct node {
    int nr;
    node *son[26];
    node *fail;
    vector<int> words;

    node() {
        nr = 0;
        fail = NULL;
        for (int i = 0; i < 26; i++) son[i] = NULL;
        words.clear();
    }
};

int n, m, i, j, go;
char S[maxN];
char A[maxM];
node *Head;

queue<node*> Q;
vector<node*> order;
int ans[maxWords];

void compute_son(node *act, int go) {
    if (act == Head) {
        act->son[go]->fail = Head;
        return;
    }

    node *aux = act->fail;
    while (aux != Head && aux->son[go] == NULL)
        aux = aux->fail;

    if (aux->son[go] != NULL) aux = aux->son[go];
    act->son[go]->fail = aux;
}

int main()
{
    freopen("ahocorasick.in","r",stdin);
    freopen("ahocorasick.out","w",stdout);

    Head = new node();
    Head->fail = Head;

    scanf("%s\n%d\n", S + 1, &n);
    for (i = 1; i <= n; i++) {
        memset(A, 0, sizeof(A));
        scanf("%s\n", A + 1);
        m = strlen(A + 1);

        node *act = Head;
        for (j = 1; j <= m; j++) {
            go = A[j] - 'a';
            if (act->son[go] == NULL) act->son[go] = new node();
            act = act->son[go];
        }

        act->words.pb(i);
    }

    Q.push(Head);
    while (!Q.empty()) {
        node *act = Q.front(); Q.pop();
        order.pb(act);

        for (i = 0; i < 26; i++) {
            if (act->son[i] != NULL) {
                Q.push(act->son[i]);
                compute_son(act, i);
            }
        }
    }

    m = n;
    n = strlen(S + 1);
    node *act = Head;

    for (i = 1; i <= n; i++) {
        go = S[i] - 'a';

        while (act != Head && act->son[go] == NULL) act = act->fail;
        if (act->son[go] != NULL) act = act->son[go];
        act->nr++;
    }

    reverse(order.begin(), order.end());
    for (auto e : order) {
        e->fail->nr += e->nr;
        for (auto w : e->words)
            ans[w] += e->nr;
    }

    for (i = 1; i <= m; i++) printf("%d\n", ans[i]);

    return 0;
}

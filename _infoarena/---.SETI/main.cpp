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

#define maxN (2222 * 64)
#define maxDim 22
#define maxM 33111

struct node {
    int nr;
    node *fail;
    node *son[52];
    vector<int> words;

    node() {
        nr = 0;
        words.clear();
        fail = this;
        for (int i = 0; i < 52; i++) son[i] = NULL;
    }
};


int n, m, i, dim, j;
char S[maxN];
char A[maxDim];

node *Head;
queue<node*> Q;
vector<node*> nodes;

int ans[maxM];

int get_go(char c) {
    if ('a' <= c && c <= 'z') return c - 'a';
    return c - 'A' + 26;
}

node* next_with(node* act, int go) {
    act = act->fail;

    while (act != Head && act->son[go] == NULL) act = act->fail;
    if (act->son[go] != NULL) act = act->son[go];

    return act;
}

int main()
{
    freopen("seti.in","r",stdin);
    freopen("seti.out","w",stdout);

    scanf("%d\n", &n);
    for (i = 1; i <= n; i++) scanf("%s\n", S + (i - 1) * 64 + 1);
    n *= 64;

    Head = new node();
    scanf("%d", &m);
    for (i = 1; i <= m; i++) {
        memset(A, 0, sizeof(A));
        scanf("%s\n", A + 1);
        dim = strlen(A + 1);

        node *act = Head;

        for (j = 1; j <= dim; j++) {
            int go = get_go(A[j]);

            if (act->son[go] == NULL) act->son[go] = new node();
            act = act->son[go];
        }

        act->words.pb(i);
    }

    Q.push(Head);
    while (!Q.empty()) {
        node *act = Q.front(); Q.pop();
        nodes.pb(act);

        for (i = 0; i < 52; i++) {
            if (act->son[i] != NULL) {
                if (act == Head)
                    act->son[i]->fail = act;
                else
                    act->son[i]->fail = next_with(act, i);

                Q.push(act->son[i]);
            }
        }
    }

    node *act = Head;
    for (i = 1; i <= n; i++) {
        int go = get_go(S[i]);

        if (act->son[go] != NULL)
            act = act->son[go];
        else
            act = next_with(act, go);

        act->nr++;
    }

    reverse(nodes.begin(), nodes.end());
    for (node* act : nodes) {
        act->fail->nr += act->nr;
        for (auto w : act->words)
            ans[w] += act->nr;
    }

    for (i = 1; i <= m; i++)
        printf("%d\n", ans[i]);


    return 0;
}

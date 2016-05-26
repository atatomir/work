#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

#define ll long long
#define pb push_back
#define mp make_pair

#define maxN 100111
#define sigma 26

struct node {
    node *son[sigma];
    node *fail, *last_good;
    int len;
    bool valid;

    node() {
        for (int i = 0; i < sigma; i++) son[i] = NULL;
        fail = last_good = NULL;
        valid = false;
        len = 0;
    }
};



int n, m, k, i;
char s[maxN];
char word[maxN];

node* Head;
queue<node*> Q;

int dp[maxN];




void add_word() {
    int i, go;

    node* act = Head;
    for (i = 1; i <= k; i++) {
        go = word[i] - 'a';

        if (act->son[go] == NULL) act->son[go] = new node();
        act = act->son[go];
        act->len = i;
    }

    act->valid = true;
}

node* get_next(node* act, int go) {
    while (act != Head && act->son[go] == NULL) act = act->fail;
    if (act->son[go] != NULL) act = act->son[go];
    return act;
}

void compute_tree() {
    int i;
    node *act, *aux;

    while (!Q.empty()) Q.pop();
    Q.push(Head);

    Head->fail = Head;

    while (!Q.empty()) {
        act = Q.front(); Q.pop();

        for (i = 0; i < sigma; i++) {
            if (act->son[i] == NULL) continue;

            if (act == Head)
                act->son[i]->fail = Head;
            else
                act->son[i]->fail = get_next(act->fail, i);

            Q.push(act->son[i]);
        }

        for (aux = act->fail; aux->valid == false && aux != Head; aux = aux->last_good);
        act->last_good = aux;
    }
}



int main()
{
    freopen("kc.in", "r", stdin);
    freopen("kc.out", "w", stdout);

    scanf("%d%d\n", &n, &m);
    scanf("%s\n", s + 1);

    Head = new node();

    k = 0;
    for (i = 1; i <= m; i++) {
        memset(word, 0, k + 10);
        scanf("%s\n", word + 1);
        k = strlen(word + 1);

        add_word();
    }

    compute_tree();

    node* act = Head;
    node* aux;
    for (i = 1; i <= n; i++) {
        act = get_next(act, s[i] - 'a');

        for (aux = act; aux != Head; aux = aux->last_good) {
            if (aux->valid == false) continue;
            dp[i] = max(dp[i], dp[i - aux->len] + aux->len);
        }

        dp[i] = max(dp[i], dp[i - 1]);
    }

    printf("%d", dp[n]);


    return 0;
}

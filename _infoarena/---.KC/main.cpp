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

#define maxN 100011
#define sigma 26

struct node {
    bool useful;
    int lvl;
    node* son[sigma];
    node *fail, *last;

    node() {
        lvl = 0;
        fail = last = NULL;
        memset(son, 0, sizeof(son));
        useful = false;
    }
};

int n, k, l, i;
char s[maxN];
char word[maxN];
node* Head;
queue<node*> Q;
int dp[maxN];

void add_word() {
    node* act = Head;
    int i;

    for (i = 1; i <= l; i++) {
        int go = word[i] - 'a';
        if (act->son[go] == NULL) act->son[go] = new node();
        act = act->son[go];
    }

    act->useful = true;
}

node* get_fail(node* act, int go) {
    while (act != Head && act->son[go] == NULL) act = act->fail;
    if (act->son[go]) act = act->son[go];
    return act;
}

int main()
{
    freopen("kc.in","r",stdin);
    freopen("kc.out","w",stdout);

    Head = new node();

    scanf("%d%d\n%s\n", &n, &k, s + 1);
    for (i = 1; i <= k; i++) {
        memset(word, 0, l + 3);
        scanf("%s\n", word + 1);
        l = strlen(word + 1);
        add_word();
    }

    Q.push(Head);
    Head->fail = Head;
    Head->last = Head;

    while (!Q.empty()) {
        node* act = Q.front(); Q.pop();
        if (act->fail->useful)
            act->last = act->fail;
        else
            act->last = act->fail->last;

        for (int to = 0; to < sigma; to++) {
            if (act->son[to] == NULL) continue;
            act->son[to]->lvl = act->lvl + 1;
            if (act != Head)
                act->son[to]->fail = get_fail(act->fail, to);
            else
                act->son[to]->fail = Head;

            Q.push(act->son[to]);
        }
    }

    node* act = Head;
    for (i = 1; i <= n; i++) {
        int go = s[i] - 'a';
        dp[i] = dp[i - 1];

        while (act != Head && act->son[go] == NULL) act = act->fail;
        if (act->son[go]) act = act->son[go];

        node* aux = act;
        while (aux != Head) {
            if (aux->useful) dp[i] = max(dp[i], aux->lvl + dp[i - aux->lvl]);
            aux = aux->last;
        }
    }

    printf("%d", dp[n]);



    return 0;
}

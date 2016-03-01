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

#define maxN 111
#define maxNode maxN * maxN
#define pii pair< int, pair<node*, int> >

struct node {
    int bonus;
    node *son[26];
    node *fail;
    int id;

    node(int _id) {
        bonus = 0;
        for (int i = 0; i < 26; i++) son[i] = NULL;
        fail = NULL;
        id = _id;
    }
};

int n, m, dim, i, j, pay, cnt;
char S[maxN];
node *Head, *best;
char ans[maxN];

char ch[maxNode];
int dp[maxNode][maxN];
node* prov[maxNode][maxN];

queue<node*> Q;
vector<node*> nodes;
node* Tree[maxNode];

node* next_with(node *act, int go) {
    act = act->fail;

    while (act != Head && act->son[go] == NULL) act = act->fail;
    if (act->son[go] != NULL) act = act->son[go];

    return act;
}

void bfs(node *act) {
    Q.push(act);

    while (!Q.empty()) {
        act = Q.front(); Q.pop();
        nodes.pb(act);

        act->bonus += act->fail->bonus;
        for (int i = 0; i < 26; i++) {
            if (act->son[i] == NULL) continue;

            if (act == Head)
                act->son[i]->fail = act;
            else
                act->son[i]->fail = next_with(act, i);

            Q.push(act->son[i]);
        }
    }
}

int main()
{
    freopen("strigat.in","r",stdin);
    freopen("strigat.out","w",stdout);

    cnt++;
    Head = new node(0);
    Head->fail = Head;
    ch[0] = '@';
    best = Head;

    scanf("%d%d\n", &n, &m);
    for (i = 1; i <= m; i++) {
        scanf("%s\n%d\n", S + 1, &pay);
        dim = strlen(S + 1);

        node *act = Head;
        for (j = 1; j <= dim; j++) {
            int go = S[j] - 'a';

            if (act->son[go] == NULL)
                act->son[go] = new node(cnt++);

            act = act->son[go];
            ch[ act->id ] = S[j];
        }

        act->bonus += pay;
    }

    bfs(Head);
    for (auto e : nodes) {
        for (i = 0; i < 26; i++) {
            if (e->son[i] != NULL) continue;

            e->son[i] = next_with(e, i);
        }
    }

    for (auto e : nodes)
        Tree[e->id] = e;

    dp[0][0] = 1;
    for (int lvl = 1; lvl <= n; lvl++) {
        for (i = 0; i < cnt; i++) {
            node* act = Tree[i];

            for (j = 0; j < 26; j++) {
                node *to = Tree[i]->son[j];
                int new_power = dp[i][lvl - 1] + to->bonus;
                if (dp[i][lvl - 1] == 0) new_power = 0;

                if (new_power > dp[to->id][lvl]) {
                    dp[to->id][lvl] = new_power;
                    prov[to->id][lvl] = act;
                }
            }
        }
    }

    for (i = 0; i < cnt; i++)
        if (dp[i][n] > dp[best->id][n])
            best = Tree[i];

    printf("%d\n", dp[best->id][n] - 1);
    for (i = n; i > 0; i--) {
        ans[i] = ch[ best->id ];
        best = prov[best->id][i];
    }

    printf("%s\n", ans + 1);

    return 0;
}

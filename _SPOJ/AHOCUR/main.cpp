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

#define maxDim 22
#define maxLev 103
#define sigma 62

struct node {
    bool deny;
    node *fail;
    node *son[sigma];
    double chance[maxLev];

    node() {
        deny = false;
        fail = this;
        for (int i = 0; i < sigma; i++) son[i] = NULL;
        memset(chance, 0, sizeof(chance));
    }
};

int T, n, k, i, j, dim, L;
char s[maxDim];
double let_chance[sigma];
char ch;

node *Head;
queue<node*> Q;
vector<node*> nodes;

int get_go(char c) {
    if ('a' <= c && c <= 'z') return c - 'a';
    if ('A' <= c && c <= 'Z') return c - 'A' + 26;
    return c - '0' + 26 * 2;
}

node* next_with(node* act, int go) {
    act = act->fail;

    while (act != Head && act->son[go] == NULL) act = act->fail;
    if (act->son[go] != NULL) act = act->son[go];

    return act;
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d", &T);

    for (int ti = 1; ti <= T; ti++) {
        scanf("%d\n", &n);
        Head = new node();

        //! add to dictionary
        for (i = 1; i <= n; i++) {
            memset(s, 0, sizeof(s));
            scanf("%s\n", s + 1);
            dim = strlen(s + 1);

            node *act = Head;
            for (j = 1; j <= dim; j++) {
                int go = get_go(s[j]);

                if (act->son[go] == NULL) act->son[go] = new node();
                act = act->son[go];
            }

            act->deny = true;
        }

        //! get chances
        memset(let_chance, 0, sizeof(let_chance));
        scanf("%d\n", &k);
        for (i = 1; i <= k; i++) {
            double aux;
            scanf("%c %lf\n", &ch, &aux);
            let_chance[ get_go(ch) ] = aux;
        }
        scanf("%d\n", &L);


        //! compute fail for every node
        Q.push(Head);

        while (!Q.empty()) {
            node *act = Q.front(); Q.pop();
            nodes.pb(act);

            act->deny |= act->fail->deny;

            for (i = 0; i < sigma; i++) {
                if (act->son[i] == NULL) continue;

                if (act == Head)
                    act->son[i]->fail = act;
                else
                    act->son[i]->fail = next_with(act, i);

                Q.push(act->son[i]);
            }
        }

        //! compute all edges for every node
        for (node *act : nodes) {
            for (i = 0; i < sigma; i++) {
                if (act->son[i] != NULL) continue;

                act->son[i] = next_with(act, i);
            }
        }

        //! compute chance
        Head->chance[0] = 1.00;
        for (int lvl = 1; lvl <= L; lvl++) {
            for (auto act : nodes) {
                for (i = 0; i < sigma; i++) {
                    node *to = act->son[i];

                    if (to->deny == false)
                        to->chance[lvl] += act->chance[lvl - 1] * let_chance[i];
                }
            }
        }

        //! sum chances
        double ans = 0.00;
        for (auto act : nodes)
            ans += act->chance[L];
        printf("Case #%d: %lf\n", ti, ans);

        //! remove trash
        for (auto act : nodes)
            delete act;
        nodes.clear();
    }



    return 0;
}

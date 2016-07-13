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

#define mod 666013
#define maxN 333
#define maxM 8
#define maxLen 22
#define maxNodes (8 * 20 + 3)

struct node {
    node* son[4];
    node* fail;
    int id;

    node(int _id) {
        memset(son, 0, sizeof(son));
        fail = NULL;
        id = _id;
    }
};

int t, ti;
int n, m, dim, i, digits;
char s[maxLen];

int cnt;
node* Head;
int state[maxNodes];
int dir[maxNodes][4];
queue< node* > Q;

int ss, dd;
int dp[2][maxNodes][1 << maxM];



int get_id(char c) {
    if (c == 'A')
        return 0;
    if (c == 'G')
        return 1;
    if (c == 'C')
        return 2;
    return 3;
}

void add_word(int id) {
    int i;
    node* act = Head;

    for (i = 1; i <= dim; i++) {
        int go = get_id(s[i]);

        if (act->son[go] == NULL)
            act->son[go] = new node(++cnt);
        act = act->son[go];
    }

    state[act->id] = (1 << (id - 1));
}

void compute_all() {
    int i;
    node *act, *aux;

    Head->fail = Head;

    Q.push(Head);
    while (!Q.empty()) {
        act = Q.front(); Q.pop();
        state[act->id] |= state[act->fail->id];

        for (i = 0; i < 4; i++) {
            if (act->son[i] == NULL) {
                if (act == Head)
                    dir[act->id][i] = act->id;
                else
                    dir[act->id][i] = dir[act->fail->id][i];
                continue;
            }

            dir[act->id][i] = act->son[i]->id;
            Q.push(act->son[i]);

            aux = act->fail;
            while (aux != Head && aux->son[i] == NULL) aux = aux->fail;
            if (aux->son[i] != NULL) aux = aux->son[i];
            act->son[i]->fail = aux;

            if (act == Head)
                act->son[i]->fail = Head;
        }

    }
}

void solve() {
    int i, j, st, k;
    int max_st;

    memset(dp, 0, sizeof(dp));
    n = cnt;
    ss = 0; dd = 1;
    max_st = (1 << m);

    dp[ss][1][0] = 1;
    for (i = 0; i < digits; i++) {
        memset(dp[dd], 0, sizeof(dp[dd]));

        for (j = 1; j <= n; j++) {
            for (st = 0; st < max_st; st++) {
                if (dp[ss][j][st] == 0) continue;
                dp[ss][j][st] %= mod;

                for (k = 0; k < 4; k++)
                    dp[dd][ dir[j][k] ][st | state[ dir[j][k] ]] += dp[ss][j][st];
            }
        }

        swap(ss, dd);
    }

    int ans = 0;
    for (i = 1; i <= n; i++)
        ans = (ans + dp[ss][i][max_st - 1]) % mod;

    printf("%d\n", ans);
}


int main()
{
    freopen("adn2.in","r",stdin);
    freopen("adn2.out","w",stdout);

    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++) {
        Head = new node(cnt = 1);
        memset(state, 0, sizeof(state));

        scanf("%d%d\n", &n, &m);
        digits = n;

        for (i = 1; i <= m; i++) {
            memset(s, 0, sizeof(s));
            scanf("%s\n", s + 1);
            dim = strlen(s + 1);
            add_word(i);
        }

        compute_all();
        solve();

    }


    return 0;
}

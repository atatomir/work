#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stack>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxDim 100111
#define maxN 333
#define inf 1000000000

struct node {
    vector<short> ids;
    node *son[26];

    node() {
        ids.clear();
        for (int i = 0; i < 26; i++)
            son[i] = NULL;
    }
};

int t, test, n, k, i, j, dim, fr, pos, ans;
char s[maxDim];

char mat[maxN][maxDim];
int sz[maxN];

node *Head;
vector<int> aux;

int dp[maxN][maxN];
stack<node*> S;

void add_trie(int id) {
    node *act = Head;

    for (int i = 1; i <= dim; i++) {
        int go = s[i] - 'a';

        if (act->son[go] == NULL)
            act->son[go] = new node();
        act = act->son[go];

        mat[id][i] = s[i];
        s[i] = '\0';
    }

    act->ids.pb(id);
}

void dfs(node *act) {
    while (!S.empty())
        S.pop();
    S.push(act);

    while (!S.empty()) {
        node *act = S.top();

        for (auto e : act->ids)
            aux.pb(e);
        act->ids.clear();

        bool found = false;
        for (int i = 0; i < 26; i++) {
            if (act->son[i] == NULL)
                continue;

            S.push(act->son[i]);
            act->son[i] = NULL;

            found = true;
            break;
        }

        if (found)
            continue;

        S.pop();
        delete act;
    }
}

int main()
{
    freopen("input.in","r",stdin);
    freopen("output.out","w",stdout);

    scanf("%d", &t);
    for (test = 1; test <= t; test++) {
        cerr << "Solving" << test << '\n';

        scanf("%d%d\n", &n, &k);
        ans = inf;

        Head = new node();

        for (i = 1; i <= n; i++) {
            scanf("%s\n", s + 1);
            dim = strlen(s + 1);
            sz[i] = dim;

            add_trie(i);
        }

        aux.clear();
        dfs(Head);

        //! now i have the strings sorted

        dp[0][0] = 0;
        for (i = 1; i <= n; i++) {
            int id_i = aux[i - 1];

            dp[i][1] = sz[id_i];

            for (j = 2; j <= i; j++) {
                pos = 0;
                dp[i][j] = inf;

                for (fr = j - 1; fr <= i - 1; fr++) {
                    int id_fr = aux[fr - 1];

                    while (pos + 1 <= sz[id_fr] && pos + 1 <= sz[id_i] && mat[id_fr][pos + 1] == mat[id_i][pos + 1])
                        pos++;

                    dp[i][j] = min(dp[i][j], dp[fr][j - 1] + sz[id_fr] - pos + sz[id_i] - pos);
                }
            }

            if (i >= k)
                ans = min(ans, dp[i][k] + sz[id_i]);
        }

        printf("Case #%d: %d\n", test, ans + k);
    }


    return 0;
}

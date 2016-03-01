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

#define maxS 10011
#define maxDim 22
#define maxMorDim maxDim * 5
#define sigma 2

const string def[26] = {".-",
                        "-...",
                        "-.-.",
                        "-..",
                        ".",
                        "..-.",
                        "--.",
                        "....",
                        "..",
                        ".---",
                        "-.-",
                        ".-..",
                        "--",
                        "-.",
                        "---",
                        ".--.",
                        "--.-",
                        ".-.",
                        "...",
                        "-",
                        "..-",
                        "...-",
                        ".--",
                        "-..-",
                        "-.--",
                        "--.."};

struct node {
    node *fail;
    node *son[sigma];
    int dim, how;

    node() {
        dim = how = 0;
        fail = NULL;
        for (int i = 0; i < sigma; i++)
            son[i] = NULL;
    }
};


int T, ti;
int n, m, dim, i, j;
char S[maxS];
char A[maxDim];
string aux;

ll dp[maxS];

node *Head;
queue<node*> Q;
vector<node*> nodes;

int get_go(char c) {
    if (c == '.') return 0;
    return 1;
}

node* next_when(node* act, int go) {
    act = act->fail;

    while (act != Head && act->son[go] == NULL) act = act->fail;
    if (act->son[go] != NULL) act = act->son[go];

    return act;
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d\n", &T);
    for (ti = 1; ti <= T; ti++) {
        memset(S, 0, sizeof(S));
        scanf("%s\n%d\n", S + 1, &m);
        n = strlen(S + 1);

        Head = new node();

        //! add to dictionary
        for (i = 1; i <= m; i++) {
            memset(A, 0, sizeof(A));
            scanf("%s\n", A + 1);
            dim = strlen(A + 1);

            aux.clear();
            for (j = 1; j <= dim; j++) aux += def[A[j] - 'A'];

            //! now add aux
            node *act = Head;
            for (char let : aux) {
                int go = get_go(let);

                if (act->son[go] == NULL) act->son[go] = new node();
                act = act->son[go];
            }

            act->dim = aux.size();
            act->how++;
        }

        //! compute fail
        nodes.clear();
        Q.push(Head);
        Head->fail = Head;

        while (!Q.empty()) {
            node *act = Q.front(); Q.pop();

            for (i = 0; i < sigma; i++) {
                if (act->son[i] == NULL) continue;

                if (act == Head)
                    act->son[i]->fail = Head;
                else
                    act->son[i]->fail = next_when(act, i);

                Q.push(act->son[i]);
            }
        }

        //! compute ans
        memset(dp, 0, sizeof(dp));
        dp[0] = 1;
        node *act = Head;

        for (i = 1; i <= n; i++) {
            int go = get_go(S[i]);

            if (act->son[go] != NULL)
                act = act->son[go];
            else
                act = next_when(act, go);

            node* aux = act;
            while (aux != Head) {
                if (aux->dim && i >= aux->dim)
                    dp[i] += 1LL * aux->how * dp[i - aux->dim];

                aux = aux->fail;
            }

        }

        //! remove trash
        for (node* e : nodes)
            delete e;
        nodes.clear();

        //! write answer
        printf("%lld\n", dp[n]);
    }




    return 0;
}

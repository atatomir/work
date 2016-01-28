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

#define maxN 333

struct Trie {
    int last;
    Trie *son[26];

    Trie() {
        last = 0;
        for (int i = 0; i < 26; i++) son[i] = NULL;
    }
};

int n, i, dim, good;
char s[maxN];
Trie *R;
int ans;

void add_string(int id) {
    int i, j;

    for (i = 1; i <= dim; i++) {
        Trie *act = R;

        for (j = i; j <= dim; j++) {
            int go = s[j] - 'a';

            if (act->son[go] == NULL) {
                if (id == 1)
                    act->son[go] = new Trie();
                else
                    break;
            }

            act = act->son[go];
            if (act->last < id - 1) break;
            act->last = id;
        }
    }
}

void rm_string() {
    int i, j;

    for (i = 1; i <= dim; i++) {
        Trie *act = R;

        for (j = i; j <= dim; j++) {
            int go = s[j] - 'a';

            if (act->son[go] == NULL)
                break;

            act = act->son[go];
            act->last = 0;
        }
    }
}

void dfs(Trie *act) {
    if (act->last == good)
        ans++;

    for (int i = 0; i < 26; i++)
        if (act->son[i] != NULL)
            dfs(act->son[i]);
}

int main()
{
    freopen("sub.in","r",stdin);
    freopen("sub.out","w",stdout);

    R = new Trie();

    scanf("%d\n", &n);
    for (i = 1; i <= n; i++) {
        scanf("%s\n", s + 1);

        dim = strlen(s + 1);
        add_string(i);
    }
    good = n;

    scanf("%d\n", &n);
    for (i = 1; i <= n; i++) {
        scanf("%s\n", s + 1);

        dim = strlen(s + 1);
        rm_string();
    }

    dfs(R);
    printf("%d", ans);


    return 0;
}

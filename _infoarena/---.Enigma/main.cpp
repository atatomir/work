#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 300011
#define maxS 111
#define maxM 4555
#define mod 31333

int tr_i;
struct Trie {
    int cnt;
    Trie *son[26];

    Trie() {
        cnt = 0;
        for (tr_i = 0; tr_i < 26; tr_i++)
            son[tr_i] = NULL;
    }
};

int n, m, i, j, len;
char s[maxN];
char aux[maxS];

int dp[maxN];
Trie *R;

int main()
{
    freopen("enigma.in","r",stdin);
    freopen("enigma.out","w",stdout);

    scanf("%d%d\n", &n, &m);
    scanf("%s\n", s + 1);

    R = new Trie();
    for (i = 1; i <= m; i++) {
        memset(aux, 0, sizeof(aux));
        scanf("%s\n", aux + 1);

        Trie *act = R;
        for (j = 1; aux[j] != '\0'; j++) {
            int go = aux[j] - 'a';

            if (act->son[go] == NULL) act->son[go] = new Trie();
            act = act->son[go];

            act->cnt++;
        }
    }

    dp[0] = 1;
    for (i = 0; i < n; i++) {
        Trie *act = R;

        for (j = i + 1; j <= n; j++) {
            act = act->son[s[j] - 'a'];
            if (act == NULL) break;

            dp[j] = ( dp[j] + dp[i] * act->cnt) % mod;
        }
    }

    printf("%d", dp[n]);

    return 0;
}

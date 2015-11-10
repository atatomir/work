#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 5100000

int tri, trj;

struct Trie {
    Trie *son[26][26];
    int best;

    Trie(){
        for (tri = 0; tri < 26; tri++)
            for (trj = 0; trj < 26; trj++)
                son[tri][trj] = NULL;
        best = 0;
    };
};

int n, i;
char s[maxN];
vector<int> beg;
vector<int> len;

vector<int> aux;

Trie *R;
int bigBest;


bool cmp(int a, int b) {
    return len[a] < len[b];
}

void add_to_trie(int id) {
    //cerr << id << ' ' << bigBest << '\n';

    int bg = beg[id];
    int l  = len[id];
    int en = bg + l - 1;

    Trie *act = R;

    int ans = 0;
    int c1, c2;
    for (int i = 1; i <= l; i++) {
        c1 = s[bg + i - 1] - 'A';
        c2 = s[en - i + 1] - 'A';

        if (act->son[c1][c2] == NULL) act->son[c1][c2] = new Trie();
        act = act->son[c1][c2];
        ans = max(ans, act->best);
    }

    ans++;
    act->best = max(act->best, ans);
    bigBest = max(bigBest, ans);
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d\n", &n);

    beg.resize(n + 3);
    len.resize(n + 3);
    aux.resize(n);
    beg[1] = 1;

    for (i = 1; i <= n; i++) {
        scanf("%s\n", s + beg[i]);
        len[i] = strlen(s + beg[i]);
        beg[i + 1] = beg[i] + len[i] + 1;
        aux[i - 1] = i;
    }

    //sort(aux.begin(), aux.end(), cmp);

    R = new Trie();
    for (auto id : aux)
        add_to_trie(id);

    printf("%d", bigBest);


    return 0;
}

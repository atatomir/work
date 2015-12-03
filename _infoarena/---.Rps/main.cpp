#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 1000011
#define inf 1000000000

char ids['Z' + 11];
char beat['Z' + 11];
char lett[3];
int lexi[3] = {1, 0, 2};

struct Trie{
    int add;
    int best;

    Trie *son[3];
    //! R < P ; P < S ; S < R

    Trie() {
        add = best = 0;
        son[0] = son[1] = son[2] = NULL;
    }

    void update() {
        best = -inf;
        for (int i = 0; i < 3; i++)
            if (son[i] != NULL)
                best = max(best, son[i]->best);
            else
                best = max(best, 0);
        best += add;
    }
};

int n, k, i, j, w, d;
char s[maxN];
Trie *R;

void add_player(Trie *act, int pos) {
    int go;

    go = beat[ s[pos] ];
    if (act->son[go] == NULL)
        act->son[go] = new Trie();
    act->son[go]->add += w;
    act->son[go]->update();

    go = ids[ s[pos] ];
    if (act->son[go] == NULL)
        act->son[go] = new Trie();
    if (pos < k) {
        add_player(act->son[go], pos + 1);
    } else {
        act->son[go]->add += d;
        act->son[go]->update();
    }

    act->update();
}

void print_best() {
    //cerr << R->best << '\n';

    Trie *act = R;
    for (int i = 1; i <= k; i++) {
        int need = act->best - act->add;

        for (int ind = 0; ind < 3; ind++) {
            int wh = lexi[ind];

            if (act->son[wh] == NULL) {
                if (need == 0) {
                    s[i] = lett[wh];
                    for (int jj = i + 1; jj <= k; jj++)
                        s[jj] = lett[ lexi[0] ];
                    printf("%s\n", s + 1);

                    return;
                } else {
                    continue;
                }
            }
            if (act->son[wh]->best == need) {
                s[i] = lett[wh];
                act = act->son[wh];
                break;
            }
        }
    }

    s[k + 1] = '\0';
    //cerr << s + 1 << '\n';
    printf("%s\n", s + 1);
}

int main()
{
    freopen("rps.in","r",stdin);
    freopen("rps.out","w",stdout);

    scanf("%d%d%d%d\n", &n, &k, &w, &d);
    R = new Trie();

    ids['R'] = 0; beat['R'] = 1;
    ids['P'] = 1; beat['P'] = 2;
    ids['S'] = 2; beat['S'] = 0;
    lett[0] = 'R';
    lett[1] = 'P';
    lett[2] = 'S';

    for (i = 1; i <= n; i++) {
        scanf("%s\n", s + 1);
        add_player(R, 1);
        print_best();
    }


    return 0;
}

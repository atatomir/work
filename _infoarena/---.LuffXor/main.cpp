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

#define maxN 200011

struct trie {
    int cnt;
    trie *son[2];

    trie() {
        cnt = 0;
        son[0] = son[1] = NULL;
    }
};

int n, i, ins, op, x, k;
int ord[maxN];
trie *Head;

void add(int nr, int v) {
    trie *act = Head;

    for (int bit = 30; bit >= 0; bit--) {
        int to = (nr >> bit) & 1;

        if (act->son[to] == NULL)
            act->son[to] = new trie();

        act = act->son[to];
        act->cnt += v;
    }
}

int solve() {
    int k_bit, x_bit;
    int ans = 0;
    trie *act = Head;

    for (int bit = 30; bit >= 0; bit--) {
        if (act == NULL) break;

        x_bit = (x >> bit) & 1;
        k_bit = (k >> bit) & 1;

        if (k_bit == 1) {
            int to = x_bit;
            if (act->son[to] != NULL)
                ans += act->son[to]->cnt;
        }

        act = act->son[x_bit ^ k_bit];
    }

    if (act != NULL)
        ans += act->cnt;

    return ans;
}

int main()
{
    freopen("luffxor.in","r",stdin);
    freopen("luffxor.out","w",stdout);

    Head = new trie();

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d%d", &op, &x);

        if (op == 0) {
            ord[++ins] = x;
            add(x, +1);
        }

        if (op == 1) {
            add(ord[x], -1);
        }

        if (op == 2) {
            scanf("%d", &k);
            printf("%d\n", solve());
        }
    }


    return 0;
}

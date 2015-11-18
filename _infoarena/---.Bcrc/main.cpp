#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 2050
#define maxM 50011
#define inf 100000000

int n, i, m, t, c, b;

int best_last;
int last[maxN][maxN];
int bg[maxN];

int from;
int best_global;

int abss(int x) {
    if (x < 0) return -x;
    return x;
}

int get_time(int x, int y) {
    if (x > y) swap(x, y);
    return min(y - x, n - y + x);
}

void test_from(int where) {
    int t_lim = t - get_time(where, c);

    int poss = min(n, t_lim - bg[where] + 1);
    from = max(from, 1 * last[where][poss]);
}

void update() {
    b += from;

    int rez = last[c][n];
    int new_bg = t - n + 1;
    int rm = min(new_bg - bg[c], n);

    best_last = max(best_last, 1 * last[c][rm]);

    for (i = rm + 1; i <= n; i++)
        last[c][i - rm] = last[c][i];
    for (i = n - rm + 1; i <= n; i++) last[c][i] = rez;
    last[c][n] = max(1 * last[c][n], b);
    bg[c] = new_bg;

    best_global = max(best_global, b);
}

int main()
{
    freopen("bcrc.in","r",stdin);
    freopen("bcrc.out","w",stdout);

    best_global = -inf;
    best_last = -inf;

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) bg[i] = -n + 1;

    for (i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            last[i][j] = -inf;
    last[1][n] = 0;

    for (; m > 0; m--) {
        scanf("%d%d%d", &t, &c, &b);

        from = best_last;
        for (i = 1; i <= n; i++)
            test_from(i);

        update();
    }

    printf("%d", best_global);

    return 0;
}

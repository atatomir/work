#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 100011
#define maxK 35

int n, l, m, i, dim;
char A[maxN];
char aux[maxN];
char B[maxN];
int dims[maxK];

vector<int> match[maxK];

int pr[maxN];
int u;

void solve() {
    int i;

    memset(pr, 0, sizeof(u));
    u = 0;

    for (i = 2; i <= m; i++) {
        while (u > 0 && B[i] != B[u + 1]) u = pr[u];
        if (B[i] == B[u + 1]) u++;
        pr[i] = u;
    }

    u = 0;
    for (i = 1; i <= n; i++) {
        while (u > 0 && A[i] != B[u + 1]) u = pr[u];
        if (A[i] == B[u + 1]) u++;

        if (u == m) {
            match[dim].pb(i - m + 1);
            u = pr[u];
        }
    }
}

void getSolution() {
    int bg;
    int pos = 0;

    if (match[1].empty()) {
        printf("-1\n");
        return;
    }
    bg = match[1][0];
    pos = bg + dims[1] - 1;

    for (int i = 2; i <= dim; i++) {
        int now = 0;

        for (auto wh : match[i]) {
            if (wh > pos) {
                now = wh + dims[i] - 1;
                break;
            }
        }

        if (now == 0) {
            printf("-1\n");
            return;
        }
        pos = now;
    }

    printf("%d %d\n", bg, pos);
}

int main()
{
    freopen("potrivire.in","r",stdin);
    freopen("potrivire.out","w",stdout);

    scanf("%d%d\n%s\n%s", &n, &l, A + 1, aux + 1);

    for (i = 1; i <= l; i++) {
        while (i <= l && aux[i] == '*') i++;
        if (i > l) break;

        dim++; m = 0;
        while (i <= l && aux[i] != '*') {
            B[++m] = aux[i];
            i++;
        }

        dims[dim] = m;
        solve();
    }

    getSolution();

    return 0;
}

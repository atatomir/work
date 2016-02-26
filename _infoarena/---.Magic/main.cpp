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

#define maxN 7

int n, i, j, op, limit;
int ln[maxN], co[maxN];
int wh[maxN * 2];
int ind[maxN];

int act[maxN * 2];
int ans;

ll best, aux;

void solve(int pas, int wh) {
    if (pas == n + 1) {
        for (int i = 2; i <= 2 * n; i++)
            if (act[i] <= act[i - 1]) return;

        ans++;

        aux = 0;
        for (i = 1; i <= 2 * n; i++) {
            aux <<= n;
            aux |= 1LL * act[i];
        }

        best = min(best, aux);

        return;
    }

    for (int i = wh + 1; i < limit; i++) {
        act[ ln[ ind[pas] ] ] = i;

        for (int j = 1; j <= n; j++)
            if ( i & (1 << (n - j)) )
                act[ co[j] ] ^= 1 << (n - ind[pas]);

        solve(pas + 1, i);

        for (int j = 1; j <= n; j++)
            if ( i & (1 << (n - j)) )
                act[ co[j] ] ^= 1 << (n - ind[pas]);
    }
}

bool cmp(int a, int b) {
    return ln[a] < ln[b];
}

int main()
{
    freopen("magic.in","r",stdin);
    freopen("magic.out","w",stdout);

    scanf("%d%d", &op, &n);
    for (i = 1; i <= n; i++) {
        scanf("%d", &ln[i]);
        wh[ ln[i] ] = i;

        ind[i] = i;
    }
    for (i = 1; i <= n; i++) {
        scanf("%d", &co[i]);
        wh[ co[i] ] = -i;
    }

    sort(ind + 1, ind + n + 1, cmp);
    limit = 1 << n;

    best = 1LL << (60);
    solve(1, -1);

    if (op == 1) {
        printf("%d", ans);
    } else {
        for (i = 2 * n * n; i > 0; i--)
            printf("%d", (best & (1LL << (i - 1))) ? 9 : 1 );
    }

    return 0;
}

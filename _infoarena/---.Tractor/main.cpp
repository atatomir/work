#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 16

int n, i, j, t;
int win[maxN][maxN];

int dp[1 << maxN][maxN];

int mask1, mask2, id;

vector< pair<int, int> > masks[4];

void gen(int pas, int n1, int n2) {
    if (pas == n) {
        masks[id].pb(mp(mask1, mask2));
        return;
    }

    if (n - pas > n1 + n2)
        gen(pas + 1, n1, n2);

    if (n1) {
        mask1 ^= 1 << pas;
        gen(pas + 1, n1 - 1, n2);
        mask1 ^= 1 << pas;
    }

    if (n2) {
        mask2 ^= 1 << pas;
        gen(pas + 1, n1, n2 - 1);
        mask2 ^= 1 << pas;
    }
}

void solve(int id) {
    int i, head1, head2;

    for (auto now : masks[id]) {
        int rez = now.first | now.second;

        if (now.first >= (1 << n)) continue;
        if (now.second >= (1 << n)) continue;

        for (head1 = 0; head1 < n; head1++) {
            if (now.first & (1 << head1)) {

                for (head2 = head1 + 1; head2 < n; head2++) {
                    if (now.second & (1 << head2)) {

                        int val = dp[now.first][head1] + dp[now.second][head2];

                        dp[rez][head1] = max(dp[rez][head1], val + win[head1][head2]);
                        dp[rez][head2] = max(dp[rez][head2], val + win[head2][head1]);
                    }
                }

            }
        }
    }
}

int main()
{
    freopen("tractor.in","r",stdin);
    freopen("tractor.out","w",stdout);

    n = 16;

    id = 0; gen(0, 1, 1);
    id = 1; gen(0, 2, 2);
    id = 2; gen(0, 4, 4);
    id = 3; gen(0, 8, 8);

    scanf("%d", &t);
    for (; t > 0; t--) {
        memset(dp, 0, sizeof(dp));

        scanf("%d", &n);
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                scanf("%d", &win[i][j]);

        if (n >= 2) solve(0);
        if (n >= 4) solve(1);
        if (n >= 8) solve(2);
        if (n >= 16) solve(3);

        for (i = 0; i < n; i++)
            printf("%d\n", dp[(1 << n) - 1][i]);

    }


    return 0;
}

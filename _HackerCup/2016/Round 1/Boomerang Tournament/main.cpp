#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 20
#define bit_limit 18

int test, t, i, j, n;
int better[maxN][maxN];
int ans[maxN][2];

int dp[1 << bit_limit][maxN];

int act_s1;
int act_s2;

int head1, head2;
int beat;

void give_answer() {
    printf("Case #%d:\n", test);
    for (int i = 0; i < n; i++)
        printf("%d %d\n", ans[i][0], ans[i][1]);
}

void gen(int pas, int need1, int need2) {
    if (pas == n) {
        for (head1 = 0; head1 < n; head1++) {
            if (dp[act_s1][head1] == false) continue;

            if (act_s1 & (1 << head1)) {
                for (head2 = 0; head2 < n; head2++) {
                    if (dp[act_s2][head2] == false) continue;

                    if (act_s2 & (1 << head2)) {
                        //! all good

                        if (better[head1][head2]) {
                            dp[act_s1 | act_s2][head1] = true;
                            ans[head1][0] = beat;
                        } else {
                            dp[act_s1 | act_s2][head2] = true;
                            ans[head2][0] = beat;
                        }
                    }
                }
            }
        }

        return;
    }

    if (n - pas > need1 + need2)
        gen(pas + 1, need1, need2);
    if (need1) {
        act_s1 ^= (1 << pas);
        gen(pas + 1, need1 - 1, need2);
        act_s1 ^= (1 << pas);
    }
    if (need2) {
        act_s2 ^= (1 << pas);
        gen(pas + 1, need1, need2 - 1);
        act_s2 ^= (1 << pas);
    }
}

int main()
{
    freopen("input.in","r",stdin);
    freopen("output.out","w",stdout);

    scanf("%d", &t);
    for (test = 1; test <= t; test++) {
        cerr << "Solving " << test << '\n';
        memset(dp, 0, sizeof(dp));

        scanf("%d", &n);
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                scanf("%d", &better[i][j]);

        //! only one node
        if (n == 1) {
            ans[0][0] = ans[0][1] = 1;
            give_answer();
            continue;
        }

        //! the great winner
        for (i = 0; i < n; i++) {
            bool all = true;
            for (j = 0; j < n; j++)
                if (i != j && better[i][j] == false)
                    all = false;

            if (all)
                ans[i][1] = 1;
            else
                ans[i][1] = (n / 2) + 1;

            ans[i][0] = ans[i][1];
        }

        //! compute best
        int lim = (1 << n);

        for (i = 0; i < n; i++)
            dp[1 << i][i] = true;

        act_s1 = act_s2 = 0;

        beat = (n / 4) + 1;
        if (n >= 2) gen(0, 1, 1);

        beat = (n / 8) + 1;
        if (n >= 4) gen(0, 2, 2);

        beat = (n / 16) + 1;
        if (n >= 8) gen(0, 4, 4);

        beat = 1;
        if (n >= 16) gen(0, 8, 8);

        give_answer();
    }


    return 0;
}

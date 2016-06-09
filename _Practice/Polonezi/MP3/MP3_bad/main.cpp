#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <assert.h>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 100011
#define inf 2000000011
#define tm anti_compilation_error

int n, limit, speed, i, j, ss, dd, to;
char press[maxN];
int tm[maxN];

vector<int> dp[2], aux;
pair<int, int> best;

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d%d%d\n", &n, &limit, &speed);
    for (i = 1; i <= n; i++) scanf("%c %d\n", &press[i], &tm[i]);
    tm[0] = -inf;

    ss = 0; dd = 1;
    dp[ss] = aux = vector<int>(limit + 3, -1);

    dp[ss][speed] = inf;
    for (i = n; i > 0; i--) {
        dp[dd] = aux;

        for (j = 0; j <= limit; j++) {
            dp[dd][j] = max(1LL * dp[dd][j], min(1LL * dp[ss][j], 1LL * tm[i] - tm[i - 1] - 1));

            if (press[i] == '-') {
                if (j == limit) continue;

                dp[dd][j + 1] = max(dp[dd][j + 1], dp[ss][j]);
                if (j == 0) dp[dd][j] = max(dp[dd][j], dp[ss][j]);

            } else {
                if (j == 0) continue;

                dp[dd][j - 1] = max(dp[dd][j - 1], dp[ss][j]);
                if (j == limit) dp[dd][j] = max(dp[dd][j], dp[ss][j]);

            }
        }

        swap(ss, dd);
    }

    best = mp(dp[ss][0], 0);
    for (i = 1; i <= limit; i++)
        best = max(best, mp(dp[ss][i], i));

    if (best.first == inf) {
        printf("infinity");
        return 0;
    }

    printf("%d %d\n", best.first, best.second);


    return 0;
}

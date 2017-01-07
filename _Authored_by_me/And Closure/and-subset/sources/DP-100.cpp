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

#define maxN (1024 * 1024 + 11)

const int mask = (1 << 20) - 1;

int n, conf, i, x;
int dp[maxN];
int answer;

int main()
{
    //freopen("test.in","r",stdin);
    //freopen("test.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d", &x);
        dp[x] = mask ^ x;
    }

    dp[0] = mask;

    for (conf = mask - 1; conf >= 0; conf--) {
        if (dp[conf] == (mask ^ conf))
            answer++;

        if (dp[conf] == 0) continue;

        for (i = 0; i < 20; i++) {
            if ((conf >> i) & 1)
                dp[conf ^ (1 << i)] |= dp[conf];
        }
    }

    printf("%d\n", answer);
    for (i = 0; i < mask; i++)
        if (dp[i] == (i ^ mask))
            printf("%d ", i);

    return 0;
}

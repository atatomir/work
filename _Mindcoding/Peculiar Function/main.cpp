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

#define maxN (1 << 21)

const int limit = 1 << 19;

int n, i, j, x, ans;
bool on[maxN];
int dp[maxN];

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) scanf("%d", &x), on[x] = true;

    for (i = 1; i < limit; i++) {
        if (on[i]) {
            if (dp[i] != i) {
                dp[i] = i;
                ans++;
            }
        }

        for (j = 0; j < 20; j++) {
            if (i & (1 << j)) continue;
            dp[i | (1 << j)] |= dp[i];
        }
    }

    printf("%d", ans);

    return 0;
}

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

#define maxN 1024

int t, ti;
int n, k, i;
bool dp[maxN][2];

void solve() {
    int i, j, g;
    int last[2];

    dp[0][1] = false; last[1] = 0;
    dp[0][0] = true; last[0] = -3 * k;

    for (i = 1; i <= n; i++) {
        for (j = 0; j < 2; j++) {
            g = 1 ^ i ^ j;
            g &= 1;

            if (i - last[g] <= k)
                dp[i][j] = 1;
            else
                dp[i][j] = 0;
        }

        for (j = 0; j < 2; j++)
            if (dp[i][j] == 0)
                last[j] = i;
    }
}

int observe(int n, int k) {
    if (k % 2 == 0) {
        int pos = n % (k + 2);
        if (pos == 0) pos = k + 2;

        if (pos == 1)
            return 0;
        return 1;
    } else {
        int pos = n % (2 * k + 2);
        if (pos == 0) pos = 2 * k + 2;

        if (pos == 1 || pos == k + 1)
            return 0;
        return 1;
    }
}

int main()
{
    freopen("obj.in","r",stdin);
    freopen("obj.out","w",stdout);

    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++) {
        scanf("%d%d", &n, &k);

        if (observe(n, k))
            printf("G\n");
        else
            printf("I\n");

        /*solve();
        if (dp[n][0])
            printf("G\n");
        else
            printf("I\n");*/
    }

    /*for (i = 1; i <= n; i++) cerr << dp[i][0] << ' '; cerr << '\n';
    for (i = 1; i <= n; i++) cerr << dp[i][1] << ' ';*/



    return 0;
}

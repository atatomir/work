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

#define maxN 2411
#define inf 1000000000

int n, i, j, len, x;
int dp[maxN][maxN];
int vals[maxN];
vector<int> wh[maxN];



int main()
{
    freopen("harrypotter.in","r",stdin);
    freopen("harrypotter.out","w",stdout);

    scanf("%d", &n); n *= 4;
    for (i = 1; i <= n; i++) {
        scanf("%d", &vals[i]);
        wh[vals[i]].pb(i);
    }

    for (i = 1; i <= n; i++) dp[i][i - 1] = 0;
    for (i = 1; i <= n; i++) dp[i][i] = 0;

    for (len = 1; len < n; len++) {
        for (i = 1; i + len <= n; i++) {
            j = i + len;

            dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
            for (int to : wh[vals[i]]) {
                if (to <= i) continue;
                if (to > j) break;

                dp[i][j] = max(dp[i][j], 1 + dp[i + 1][to - 1] + dp[to + 1][j]);
            }

            for (int from : wh[vals[j]]) {
                if (from < i) continue;
                if (from >= j) break;
                dp[i][j] = max(dp[i][j], 1 + dp[i][from - 1] + dp[from + 1][j - 1]);
            }
        }
    }

    printf("%d", dp[1][n]);
    cerr << dp[1][n];


    return 0;
}

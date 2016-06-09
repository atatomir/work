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

#define maxN 23
#define maxBits 20
#define mod 1000000009
#define care(x) {if(x >= mod) {x -= mod;}}

int n, d, i, j;
int dim[maxN], high[maxN];
int dp[maxN][1 << maxBits];
int ans;

vector<int> bits[1 << maxBits];

int solve(int node, int conf) {
    /*   0 - unsolved
     *  >0 - computed
     *  -1 - zero
     */

    int new_conf;

    if (dp[node][conf] != 0)
        return max(0, dp[node][conf]);

    new_conf = conf ^ (1 << node);
    if ( new_conf == 0 )
        return dp[node][conf] = 1;

    for (int i = 0; i < bits[new_conf].size(); i++) {
        if (bits[new_conf][i] > high[node]) break;

        dp[node][conf] += solve( bits[new_conf][i] , new_conf);
        care(dp[node][conf]);
    }

    if (dp[node][conf] == 0) {dp[node][conf] = -1; return 0;}
    return dp[node][conf];
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d%d", &n, &d);
    for (i = 0; i < n; i++) scanf("%d", &dim[i]);

    sort(dim, dim + n);
    for (i = j = 0; i < n; i++) {
        while (j + 1 < n && dim[i] + d >= dim[j + 1]) j++;
        high[i] = j;
    }

    for (int state = (1 << n) - 1; state >= 0; state--)
        for (i = 0; i < n; i++)
            if ( (state >> i) & 1 )
                bits[state].pb(i);


    for (i = 0; i < n; i++) {
        ans += solve(i, (1 << n) - 1);
        care(ans);
    }

    printf("%d", ans);

    return 0;
}

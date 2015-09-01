#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 111
#define maxVal 131

int n,i,j;
char s[maxN][maxN];
int len[maxN];
int dp[maxN][maxN];

int best[maxN][maxN];

bool canRemove(int l,int r) {
    if ( dp[l][r] != (r-l-1)-1 ) return false;

    int i,j;
    for (i = 1; i <= len[l]; i++)
        for (j = 1; j <= len[r]; j++)
            if (s[l][i] == s[r][j])
                best[i][j] = best[i-1][j-1]+1;
            else
                best[i][j] = max(best[i-1][j],best[i][j-1]);

    return best[ len[l] ][ len[r] ] > 6;
}

int compute(int l,int r) {
    if (dp[l][r] != -1) return dp[l][r];

    if (r - l <= 1) {
        dp[l][r] = 0;
        return dp[l][r];
    }

    dp[l][r] = 0;
    for (int k = l+1; k < r; k++) dp[l][r] = max(dp[l][r], compute(l,k) + compute(k,r));
    if (canRemove(l,r)) dp[l][r]++;

    return dp[l][r];
}

int main()
{
    freopen("randuri.in","r",stdin);
    freopen("randuri.out","w",stdout);

    while (true) {
        memset(s[n+1],0,sizeof(s[n+1]));
        gets(s[n+1]+1);
        len[n+1] = strlen(s[n+1]+1);

        if (len[n+1] > 0)
            n++;
        else
            break;
    }

    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            dp[i][j] = -1;
    printf("%d", compute(1,n) );


    return 0;
}

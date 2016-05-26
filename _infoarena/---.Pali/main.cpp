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

#define maxN 5111

int n, i, j;
char s[maxN];

bool pali[maxN];
int dp[maxN];

int main()
{
    freopen("pali.in","r",stdin);
    freopen("pali.out","w",stdout);

    scanf("%s", s + 1);
    n = strlen(s + 1);

    for (i = 1; i <= n; i++) {
        for (j = 1; j + 1 < i; j++)
            pali[j] = pali[j + 1] & (s[i] == s[j]);

        if (i > 1) pali[i - 1] = (s[i - 1] == s[i]);
        pali[i] = true;

        dp[i] = maxN;
        for (j = 1; j <= i; j++)
            if (pali[j])
                dp[i] = min(dp[i], dp[j - 1] + 1);
    }

    printf("%d", dp[n]);


    return 0;
}

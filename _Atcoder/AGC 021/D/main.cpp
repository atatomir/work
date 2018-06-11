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

#define maxN 333

int n, k, i, j;
char s[maxN];
int dp[maxN][maxN][maxN];

int compute(int l, int r, int k) {
    if (dp[l][r][k] != 0) return dp[l][r][k];

    int &ans = dp[l][r][k];
    if (r - l + 1 <= 2) {
        if (r == l) ans = 1;
        if (l + 1 == r) {
            if (s[l] == s[r])
                ans = 2;
            else
                ans = (k > 0 ? 2 : 1);
        }
    } else {
        ans = max(ans, compute(l + 1, r, k));
        ans = max(ans, compute(l, r - 1, k));
        if (s[l] == s[r]) ans = max(ans, 2 + compute(l + 1, r - 1, k));
        if (k > 0 && s[l] != s[r]) ans = max(ans, 2 + compute(l + 1, r - 1, k - 1));
    }

    return dp[l][r][k];
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%s%d", s + 1, &k);
    n = strlen(s + 1);
    printf("%d", compute(1, n, k));


    return 0;
}

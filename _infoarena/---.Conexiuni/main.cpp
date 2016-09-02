#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 5011

int n, m, i, j, v;
char A[maxN], B[maxN];
int dp[maxN], cnt[maxN];
ll ans;


int main()
{
    freopen("conexiuni.in","r",stdin);
    freopen("conexiuni.out","w",stdout);

    scanf("%d%d\n%s\n%s", &n, &m, A + 1, B + 1);

    for (i = 1; i <= m; i++) dp[i] = (A[n] == B[i] ? 1 : 0), v += dp[i];
    ans += (v ^ n ^ (n + 1));

    for (i = n - 1; i > 0; i--) {
        memset(cnt, 0, sizeof(cnt));
        v = 0;

        for (j = 1; j <= m; j++) {
            dp[j] = (A[i] == B[j] ? dp[j + 1] + 1 : 0);
            if (dp[j]) {
                v++;
                cnt[dp[j] + 1]--;
            }
        }

        for (j = 1; i + j - 1 <= n; j++) {
            v += cnt[j];
            ans += 1LL * (v ^ i ^ (i + j) );
        }

    }

    printf("%lld", ans);

    return 0;
}

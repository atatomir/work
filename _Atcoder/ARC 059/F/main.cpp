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
     
    #define maxN 5011
    #define mod 1000000007
     
    int n, m, i, j;
    char s[maxN];
    ll dp[maxN][maxN];
     
    ll poww(ll a, ll b) {
        ll ans = 1;
     
        while (b > 0) {
            if (b & 1) ans = (ans * a) % mod;
            b >>= 1;
            a = (a * a) % mod;
        }
     
        return ans;
    }
     
    int main()
    {
       // freopen("test.in","r",stdin);
     
        scanf("%d\n%s", &n, s + 1);
        m = strlen(s + 1);
     
        if (n < m) {
            printf("0");
            return 0;
        }
     
        dp[0][0] = 1;
        for (i = 0; i <= n; i++) {
            for (j = 0; j <= i; j++) {
                dp[i][j] %= mod;
     
                dp[i + 1][max(0, j - 1)] += dp[i][j];
                dp[i + 1][j + 1] += dp[i][j] * 2;
            }
        }
     
        ll aux = poww(poww(2, m), mod - 2);
        ll ans = (dp[n][m] * aux) % mod;
     
        printf("%lld", ans);
     
        return 0;
    }

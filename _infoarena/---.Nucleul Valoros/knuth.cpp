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
  
#define maxN 3111
 
int n, i, j;
ll v[maxN], sum[maxN];
ll dp[maxN][maxN];
int optim[maxN][maxN];
 
  
int main()
{
    freopen("nucleulvaloros2.in","r",stdin);
    freopen("nucleulvaloros2.out","w",stdout);
  
    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%lld", &v[i]);
        sum[i] = sum[i - 1] + v[i];
    }
  
    for (i = n; i > 0; i--) {
        dp[i][i] = v[i];
        optim[i][i] = i;
         
        for (j = i + 1; j <= n; j++) {
            int l = optim[i][j - 1];
            int r = min(optim[i + 1][j], j - 1);
             
            dp[i][j] = 1LL << 60;
            for (int k = l; k <= r; k++) {
                ll new_value = dp[i][k] + dp[k + 1][j] + sum[j] - sum[i - 1];
                if (new_value < dp[i][j]) {
                    dp[i][j] = new_value;
                    optim[i][j] = k;
                }
            }
        }
         
    }
     
    printf("%lld", dp[1][n]);
  
    return 0;
}

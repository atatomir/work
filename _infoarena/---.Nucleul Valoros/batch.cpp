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
 
int l, r;
int Q[maxN];
int dead[maxN];
 
ll dp[maxN][maxN];
 
int low_pow[maxN];
 
int get_dead(int p1, int p2) {
    int ans = p2;
     
    for (int step = 1 << low_pow[n - p2]; step; step >>= 1) 
        if (ans + step <= n)
            if ( dp[i][p1] + dp[p1 + 1][ans + step] <= dp[i][p2] + dp[p2 + 1][ans + step] ) 
                ans += step;
                 
    //if (p1 == 1 && p2 == 2) printf("??%d\n", ans);
                 
    return ans + 1;
}
  
int main()
{
    freopen("nucleulvaloros2.in","r",stdin);
    freopen("nucleulvaloros2.out","w",stdout);
     
    low_pow[1] = 0;
    for (i = 2; i <= 3000; i++) {
        low_pow[i] = low_pow[i - 1];
        if (i <= 1 << (low_pow[i] + 1))
            low_pow[i]++;
    }
  
    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%lld", &v[i]);
        sum[i] = sum[i - 1] + v[i];
    }
  
    for (i = n; i > 0; i--) {
        dp[i][i] = v[i];
         
        l = r = 1;
        Q[1] = i;
         
        for (j = i + 1; j <= n; j++) {
            while (l < r) {
                if (dead[Q[l + 1]] > j) break;    
                l++;
            }   
             
            int pos = Q[l];
            dp[i][j] = sum[j] - sum[i - 1] + dp[i][pos] + dp[pos + 1][j];
             
            //printf("%d %d %d %lld\n", i, j, pos, dp[i][j]);
             
            while (l < r) {
                dead[j] = get_dead(Q[r], j);    
                if (dead[ Q[r] ] < dead[j] ) break;
                r--;
            }
             
            dead[j] = get_dead(Q[r], j);
            Q[++r] = j;
        }
         
    }
     
    //printf("%d\n", dead[2]);
    printf("%lld", dp[1][n]);
  
    return 0;
}

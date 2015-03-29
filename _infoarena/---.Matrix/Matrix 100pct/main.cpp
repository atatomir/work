#include <iostream>
#include <cstdio>
using namespace std;

#define maxN 1005

long n,m,i,j;
char a[maxN][maxN];
long dp[maxN][maxN],val;
bool ans[maxN][maxN];
char s[maxN],c;

long sum['z'];

int main()
{
    freopen("matrix.in","r",stdin);
    freopen("matrix.out","w",stdout);

    scanf("%ld %ld",&n,&m);
    for(i=1;i<=n;i++) scanf("%s",a[i]+1);
    for(i=1;i<=m;i++){
        scanf("%s",s+1);
        for(j=1;j<=m;j++) sum[s[j]]++;
    }

    for(c='a';c<='z';c++){
        for(i=1;i<=n;i++)
            for(j=1;j<=n;j++)
                dp[i][j] = dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1] + (a[i][j] == c?1:0);
        for(i=m;i<=n;i++){
            for(j=m;j<=n;j++){
                if(ans[i][j]) continue;
                val = dp[i][j] - dp[i-m][j] - dp[i][j-m] + dp[i-m][j-m];
                if(val != sum[c]) ans[i][j] = 1;
            }
        }
    }

    long answer = 0;
    for(i=m;i<=n;i++)
        for(j=m;j<=n;j++)
            if(ans[i][j] == 0) answer++;

    printf("%ld",answer);

    return 0;
}

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define maxN 17
#define maxM 7300

long n,m,l,r,i,j;
long a[maxN][maxM];
long ans=-1;

long state;
long sum[maxM];

void TryIt(long pas,long still){
    if(pas==n){
        memset(sum,0,sizeof(sum));
        long i,j;
        for(i=1;i<=n;i++){
            if(state&(1<<(i-1))) continue;
            for(j=1;j<=m;j++){
                sum[j] += a[i][j];
            }
        }

        sort(sum+1,sum+m+1);
        long act = 0;
        for(i=r+1;i<=m;i++) act += sum[i];
        ans = max(ans,act);
        return;
    }

    if(still){
        state |= (1<<pas);
        TryIt(pas+1,still-1);
    }
    if(n-pas!=still){
        if(state&(1<<pas)) state ^= 1<<pas;
        TryIt(pas+1,still);
    }
}

int main()
{
    freopen("elimin.in","r",stdin);
    freopen("elimin.out","w",stdout);

    scanf("%ld %ld %ld %ld",&n,&m,&l,&r);
    if(n<=m){
        for(i=1;i<=n;i++)
            for(j=1;j<=m;j++)
                scanf("%ld",&a[i][j]);
    } else {
        for(i=1;i<=n;i++)
            for(j=1;j<=m;j++)
                scanf("%ld",&a[j][i]);

        swap(n,m); swap(l,r);
    }

    TryIt(0,l);
    printf("%ld",ans);

    return 0;
}

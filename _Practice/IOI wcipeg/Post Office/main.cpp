#include <iostream>
#include <cstdio>

using namespace std;

//#define DEBUG
#define maxN 311
#define maxK 33
#define INF (1LL<<50)
#define long long long

long n,k,i,j,l,pp,q;
long a[maxN],ar[maxN],sum[maxN],sumr[maxN],s[maxN],sr[maxN],need[maxN];
long dp[maxN][maxK];
long prov[maxN][maxK];
long rez[maxN];

void update(long pN,long pK,long val,long sN){
    if(val>=dp[pN][pK]) return;
    dp[pN][pK] = val;
    prov[pN][pK] = sN;
}

int main()
{
    #ifdef DEBUG
        freopen("test.in","r",stdin);
    #endif // DEBUG

    scanf("%lld %lld",&n,&q);
    for(i=1;i<=n;i++) scanf("%lld",&a[i]);
    for(i=1;i<=n;i++) need[i]=a[i];

    for(i=n,a[1]=0;i>1;i--) a[i] = need[i]-need[i-1];
    for(i=n-1,ar[n]=0;i;i--) ar[i] = -(need[i]-need[i+1]);

    for(i=1;i<=n;i++) s[i] = s[i-1]+a[i];
    for(i=1;i<=n;i++) sum[i] = s[i]+sum[i-1];
    for(i=n;i;i--) sr[i] = sr[i+1]+ar[i];
    for(i=n;i;i--) sumr[i] = sr[i] + sumr[i+1];

    for(i=0;i<=n;i++)
        for(k=0;k<=q;k++) dp[i][k]=INF;

    for(i=1;i<=n;i++){
        for(k=1;k<=q;k++){

            pp=i;
            for(l=i-1;l;l--){
                while( need[i]-need[pp-1] < need[pp-1]-need[l] && pp>l+1  ) pp--;

                update(i,k,   dp[l][k-1] + ( (sumr[pp]-sumr[i]) - (i-pp)*sr[i] )
                                         + ( (sum[pp-1]-sum[l]) - (pp-1-l)*s[l] ),l);
            }
            if(k==1) update(i,k, (sumr[1]-sumr[i])-(i-1)*sr[i]  ,0);
        }
    }

    long ans = INF;
    for(i=q;i<=n;i++) {
        if(ans > dp[i][q] + (sum[n]-sum[i])-(n-i)*s[i] ){
            ans = dp[i][q] + (sum[n]-sum[i])-(n-i)*s[i] ;
            pp = i;
        }
    }

    for(i=1;i<=q;i++){
        if(prov[pp][q-i+1]==0){
            i++;i--;
        }

        rez[q-i+1] = pp;
        pp = prov[pp][q-i+1];
    }

    printf("%lld\n",ans);
    for(i=1;i<=q;i++) printf("%lld ", need[ rez[i] ] );

    return 0;
}

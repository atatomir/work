#include <iostream>
#include <cstdio>

using namespace std;

//#define DEBUG
#define maxN 605
#define maxK 211

long n,m,k,i;
long dp[maxN][maxN];
bool us[maxN][maxN];
long x[maxK],y[maxK];

long solve(long nn,long mm){
    if(us[nn][mm]) return dp[nn][mm];
    if(nn==0 || mm==0) return 0;
    us[nn][mm] = true;

    long cnt = nn*mm;
    for(long i=1;i<=k;i++){
        if(x[i] > nn || y[i] > mm) continue;
        cnt = min(cnt, solve(x[i],mm-y[i])+solve(nn-x[i],mm) );
        cnt = min(cnt, solve(nn,mm-y[i])+solve(nn-x[i],y[i]) );
    }
    dp[nn][mm]=cnt;
    return cnt;
}

int main()
{
    #ifdef DEBUG
        freopen("test.in","r",stdin);
    #endif // DEBUG

    scanf("%ld %ld %ld",&n,&m,&k);
    for(i=1;i<=k;i++) scanf("%ld %ld",&x[i],&y[i]);

    printf("%ld ", solve(n,m) );

    return 0;
}

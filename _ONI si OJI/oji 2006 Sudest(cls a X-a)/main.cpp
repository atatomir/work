#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

#define maxN 111
#define maxK 222

long n,i,j,k,p,t;
long a[maxN][maxN],m[maxK];
long pos[maxN*maxN];
long dp[maxN][maxN];
bool from[maxN][maxN];

vector<long> way;

int main()
{
    freopen("sudest.in","r",stdin);
    freopen("sudest.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++) scanf("%ld",&a[i][j]);
    scanf("%ld",&k);
    for(i=1;i<=k;i++) scanf("%ld",&m[i]);

    p = 0;
    for(i=1;i<=k;i++){
        p += m[i];
        pos[p] = m[i];
    }

    dp[1][1] = a[1][1];
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            if(!pos[i+j-2]) continue;
            long go = pos[i+j-2],ans=0,tmp;
            if(i-go>0){
                ans = a[i][j]+dp[i-go][j];
                from[i][j] = 0; // pe linie
            }
            if(j-go>0){
                if(ans < a[i][j]+dp[i][j-go]){
                    ans = a[i][j]+dp[i][j-go];
                    from[i][j] = 1;
                }
            }
            dp[i][j] = ans;
        }
    }

    /*for(i=1;i<=n;i++){
        for(j=1;j<=n;j++) cerr << dp[i][j] << ' ';
        cerr<<'\n';
    }*/

    printf("%ld\n",dp[n][n]);
    i = n; j = n;
    for(t=k;t;t--){
        way.push_back(from[i][j]);
        if(from[i][j]==0)
            i -= m[t];
        else
            j -= m[t];
    }

    i=j=k=1;
    for(t=way.size()-1;t>=0;t--){
        printf("%ld %ld\n",i,j);
        if(way[t]==0)
            i += m[k];
        else
            j += m[k];
        k++;
    }
    printf("%ld %ld\n",i,j);

    return 0;
}

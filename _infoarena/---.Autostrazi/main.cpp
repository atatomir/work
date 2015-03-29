#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

#define maxN 111
#define maxK 25
#define mod 30011

long n,s,k,i,x,y;
vector<long> list[maxN];
bool vis[maxN];
long r[maxK];
vector<long> dp[maxN],nil;

void dfs(long node){
    vis[node] = true; dp[node] = nil;
    if(list[node].size()==1)return;

    vector<long> tmp=nil; tmp[0] = 0;
    long i,iC,iK,iP; // iC-before / iK-builder / iP-for newNode
    for(i=0;i<list[node].size();i++){
        long newNode = list[node][i];
        if(vis[newNode]) continue;
        dfs(newNode);

        for(iC=0;iC<=s;iC++){
            for(iK=0;iK<=k;iK++){
                for(iP=0;iP<=s;iP++){
                    if(iC+iP+r[iK]>s) break;
                    tmp[max(iC,iP+r[iK])] += dp[newNode][iP]*dp[node][iC];
                    tmp[max(iC,iP+r[iK])] %= mod;
                }
            }
        }

        dp[node] = tmp;
        tmp=nil; tmp[0] = 0;
    }
}

int main()
{
    freopen("autostrazi.in","r",stdin);
    freopen("autostrazi.out","w",stdout);

    scanf("%ld %ld %ld",&n,&s,&k);
    for(i=1;i<=k;i++) scanf("%ld",&r[i]);
    for(i=1;i<n;i++){
        scanf("%ld %ld",&x,&y);
        list[x].push_back(y);
        list[y].push_back(x);
    }
    list[1].push_back(1);

    nil.resize(s+1); memset(&nil[0],0,sizeof(nil)); nil[0] = 1;
    dfs(1);

    long ans=0;
    for(i=0;i<=s;i++) {
        ans+= dp[1][i];
        if(ans>=mod) ans-=mod;
    }

    printf("%ld",ans);

    return 0;
}

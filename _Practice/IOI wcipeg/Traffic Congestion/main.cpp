#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>

using namespace std;

//#define DEBUG
#define maxN (1<<20)

long n,i,x,y,ans=2000000000,prov;
long cc[maxN],lvl[maxN],cnt[maxN];
vector<long> list[maxN];

void dfs(long node,long _lvl){
    lvl[node] = _lvl; cnt[node]=cc[node];
    for(long i=0;i<list[node].size();i++){
        long newNode = list[node][i];

        if(lvl[newNode]){
            list[node][i] = list[node][ list[node].size()-1 ];
            list[node].pop_back();
            i--; continue;
        }

        dfs(newNode,_lvl+1);
        cnt[node] += cnt[newNode];
    }
}

int main()
{
    #ifdef DEBUG
        freopen("test.in","r",stdin);
    #endif // DEBUG

    scanf("%ld",&n);
    for(i=1;i<=n;i++) scanf("%ld",&cc[i]);
    for(i=1;i<n;i++){
        scanf("%ld %ld",&x,&y); x++; y++;
        list[x].push_back(y);
        list[y].push_back(x);
    }

    dfs(1,1);
    for(i=1;i<=n;i++){
        long v = 0;
        for(long j=0;j<list[i].size();j++){
            long newNode = list[i][j];
            v = max(v,cnt[newNode]);
        }

        v = max(v,cnt[1]-cnt[i]);

        if(v<ans){ans=v;prov=i;}
    }
    printf("%ld",prov-1);

    return 0;
}

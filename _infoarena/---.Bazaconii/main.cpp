#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

struct Edge{
    long dir,val;
};
Edge mp(long _dir,long _val){
    Edge ans;
    ans.dir=_dir;ans.val=_val;
    return ans;
}

#define maxN 10011

long t,n,m,i,x,y,k;
vector<Edge> list[maxN];
bool used[maxN];
long ans[maxN];

queue<long> Q;
bool good;

int main()
{
    freopen("bazaconii.in","r",stdin);
    freopen("bazaconii.out","w",stdout);

    scanf("%ld",&t);
    for(;t;t--){
        scanf("%ld%ld",&n,&m);

        for(i=1;i<=n;i++) list[i].clear();
        memset(used,0,sizeof(used));
        memset(ans,0,sizeof(ans));
        good = true;

        for(i=1;i<=m;i++){
            scanf("%ld%ld%ld",&x,&y,&k);
            list[x].push_back(mp(y,k));
            list[y].push_back(mp(x,k));
        }

        for(i=1;i<=n;i++){
            if(used[i]) continue;
            while(!Q.empty()) Q.pop();

            used[i]=true; Q.push(i);
            while(!Q.empty()){
                long node = Q.front(); Q.pop();
                for(long j=0;j<list[node].size();j++){
                    Edge act = list[node][j];
                    if(used[act.dir]){
                        long val = ans[node]^act.val;
                        if(val!=ans[act.dir]){
                            good = false;
                            break;
                        }
                    } else{
                        long val = ans[node]^act.val;
                        ans[act.dir]=val; Q.push(act.dir);
                        used[act.dir]=true;
                    }
                }

                if(!good) break;
            }
        }

        if(!good)
            printf("-1\n");
        else{
            for(i=1;i<=n;i++) printf("%ld ",ans[i]);
            printf("\n");
        }
    }

    return 0;
}

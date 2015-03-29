#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

#define maxN 10011

struct Edge{
    long dir;
    bool val;
};
inline Edge mp(long _dir,bool _val){
    Edge ans;
    ans.dir=_dir;ans.val=_val;
    return ans;
}

long n,i,x,ones,zeros;
long where[maxN][3];
vector<Edge> list[maxN];
bool used[maxN];
bool ans[maxN];

queue<long> Q;
long minMove,cnt;

long biperm[2][maxN];

inline long abss(long x){
    if(x<0) return -x;
    return x;
}
inline long sgn(long x){
    if(x<0) return -1;
    return 1;
}

int main()
{
    freopen("biperm.in","r",stdin);
    freopen("biperm.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<=n;i++){
        scanf("%ld",&x);
        where[x][++where[x][0]] = i;

        biperm[0][i]=x;
    }
    for(i=1;i<=n;i++){
        scanf("%ld",&x);
        where[x][++where[x][0]] = -i;

        biperm[1][i]=x;
    }

    for(i=1;i<=n;i++){
        long x=i;
        if(where[x][1]==-where[x][2]){
            used[abss(where[x][1])]=true;
            continue;
        }
        if(sgn(where[x][1])==sgn(where[x][2])){
            where[x][1]=abss(where[x][1]);
            where[x][2]=abss(where[x][2]);

            list[where[x][1]].push_back(mp(where[x][2],1));
            list[where[x][2]].push_back(mp(where[x][1],1));
        } else {
            where[x][1]=abss(where[x][1]);
            where[x][2]=abss(where[x][2]);

            list[where[x][1]].push_back(mp(where[x][2],0));
            list[where[x][2]].push_back(mp(where[x][1],0));
        }
    }

    for(i=1;i<=n;i++){
        if(used[i]) continue;
        ans[i] = 0; used[i]=true;
        Q.push(i); zeros=1;ones=0;

        while(!Q.empty()){
            long node = Q.front(); Q.pop();
            for(long j=0;j<list[node].size();j++){
                long newNode = list[node][j].dir;
                long xorVal  = list[node][j].val;

                if(used[newNode]) continue;
                used[newNode] = true; Q.push(newNode);
                ans[newNode] = ans[node]^xorVal;

                if(ans[newNode]==0) zeros++; else ones++;
            }
        }

        minMove += min(zeros,ones);
        cnt++;
    }

    printf("%ld %ld\n",1<<cnt,minMove);
    for(i=1;i<=n;i++){
        if(ans[i]==true) printf("%ld ",biperm[1][i]); else printf("%ld ",biperm[0][i]);
    } printf("\n");
    for(i=1;i<=n;i++){
        if(ans[i]==true) printf("%ld ",biperm[0][i]); else printf("%ld ",biperm[1][i]);
    } printf("\n");

    return 0;
}

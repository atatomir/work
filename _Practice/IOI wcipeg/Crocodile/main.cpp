#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

//#define DEBUG
#define maxN 100011
#define mp make_pair
#define dir first
#define cost second
#define PI pair<long,long>
#define S 0
#define allSons vector< PI >::iterator it=list[node].begin();it!=list[node].end();it++
#define dist second
#define INF (1<<30)

long n,m,k,i,x,y,z;
vector< PI > list[maxN];
long cc[maxN][2];

struct cmp{
    bool operator()(PI& a,PI& b){return a.cost>b.cost;}
};
priority_queue<PI,vector< PI >,cmp> H;


void dijkstra(){
    for(long i=1;i<=n;i++) cc[i][0]=cc[i][1]=INF;
    long node = S;
    for( allSons ) {
        cc[it->dir][0]=0;cc[it->dir][1]=INF;
        H.push( mp(it->dir,0) );
    }

    while(!H.empty()){
        PI act = H.top(); H.pop();
        long node = act.dir;

        if(act.dist >= cc[node][1]) continue;
        if(act.dist <= cc[node][0]){
            cc[node][1]=cc[node][0];
            cc[node][0]=act.dist;
        }else
        if(act.dist < cc[node][1]) cc[node][1]=act.dist;

        for( allSons ){
            long wh = it->dir;
            long newCc = it->cost + cc[node][1];

            if(cc[wh][1]<=newCc) continue;

            H.push( mp(wh,newCc) );
        }
    }
}

int main()
{
    #ifdef DEBUG
        freopen("test.in","r",stdin);
    #endif // DEBUG

    scanf("%ld %ld %ld",&n,&m,&k);
    for(i=1;i<=m;i++){
        scanf("%ld %ld %ld",&x,&y,&z); x++; y++;
        list[x].push_back( mp(y,z) );
        list[y].push_back( mp(x,z) );
    }

    for(i=1;i<=k;i++){
        scanf("%ld",&x); x++;
        list[S].push_back( mp(x,0) );
    }

    dijkstra();
    printf("%ld",cc[1][1]);

    return 0;
}

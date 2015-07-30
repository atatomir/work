#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

//#define DEBUG
#define maxN 205
#define maxM 2015

struct cmp{
    bool operator()(long a,long b){return a>b;}
};

long n,m,i,x;
priority_queue<long,vector<long>,cmp> H;
long wh[maxM],cost[maxN],weight[maxM];
long ans;
queue<long> id;

void Try(){
    if(id.empty()) return;
    if(H.empty()) return;
    long pos = H.top(); H.pop();
    long who = id.front(); id.pop();

    wh[who]=pos;
    ans += cost[pos]*weight[who];
}

int main()
{
    #ifdef DEBUG
        freopen("test.in","r",stdin);
    #endif // DEBUG

    scanf("%ld %ld",&n,&m);
    for(i=1;i<=n;i++) scanf("%ld",&cost[i]);
    for(i=1;i<=m;i++) scanf("%ld",&weight[i]);

    for(i=1;i<=n;i++) H.push(i);

    for(m<<=1;m;m--){
        scanf("%ld",&x);
        if(x>0){
            id.push(x);
            Try();
        } else {
            x *= -1;
            H.push(wh[x]);
            Try();
        }
    }
    printf("%ld",ans);

    return 0;
}

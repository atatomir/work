#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

#define maxN 2077

struct Canibal{
    long long v1,v2,v3,v4,id;
    bool goodFood(Canibal cmp){
        if(v1==cmp.v1&&v2==cmp.v2&&v3==cmp.v3&&v4==cmp.v4)
            return id<cmp.id;
        return (v1>=cmp.v1&&v2>=cmp.v2&&v3>=cmp.v3&&v4>=cmp.v4);
    }
};

long n,i,j;
Canibal c[maxN];

vector<long> list[maxN<<1];
long l[maxN<<1];
long r[maxN];
bool u[maxN<<1],ch;

bool pairUp(long node){
    vector<long>::iterator it;
    if(u[node]) return false;
    u[node] = true;

    for(it=list[node].begin();it!=list[node].end();it++){
        if(!r[*it]){
            l[node] = *it;
            r[*it] = node;
            return true;
        }
    }
    for(it=list[node].begin();it!=list[node].end();it++){
        if(pairUp(r[*it])){
            l[node] = *it;
            r[*it] = node;
            return true;
        }
    }
    return false;
}

int main()
{
    freopen("canibali.in","r",stdin);
    freopen("canibali.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<=n;i++){
        scanf("%lld%lld%lld%lld",&c[i].v1,&c[i].v2,&c[i].v3,&c[i].v4);
        c[i].id = i;
    }

    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            if(i==j) continue;
            if(!c[i].goodFood(c[j])) continue;
            list[i].push_back(j);
            list[i+n].push_back(j);
        }
    }

    for(ch=true;ch;){
        ch=false;
        memset(u,0,sizeof(u));
        for(i=1;i<=2*n;i++)
            if(!l[i]) ch |= pairUp(i);
    }

    long alive=0;
    for(i=1;i<=n;i++)
        if(!r[i]) alive++;

    printf("%ld",alive);

    return 0;
}

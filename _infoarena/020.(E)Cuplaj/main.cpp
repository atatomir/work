#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

#define maxN 10011
#define itt vector<long>::iterator

long n,m,e,i,x,y;
vector<long> list[maxN];
long l[maxN],r[maxN];
bool used[maxN],change;

bool pairUp(long node){
    if(used[node]) return 0;
    used[node] = true;

    for(itt it=list[node].begin();it!=list[node].end();it++){
        if(r[*it]==0){
            l[node] = *it;
            r[*it] = node;
            return 1;
        }
    }
    for(itt it=list[node].begin();it!=list[node].end();it++){
        if(pairUp(r[*it])){
            l[node] = *it;
            r[*it] = node;
            return 1;
        }
    }
    return 0;
}

int main()
{
    freopen("cuplaj.in","r",stdin);
    freopen("cuplaj.out","w",stdout);

    scanf("%ld%ld%ld",&n,&m,&e);
    for(i=1;i<=e;i++){
        scanf("%ld %ld",&x,&y);
        list[x].push_back(y);
    }

    change=1;
    while(change){
        change = 0;
        memset(used,0,sizeof(used));

        for(i=1;i<=n;i++)
            if(!l[i]) change |= pairUp(i);
    }

    long ans=0;
    for(i=1;i<=n;i++)
        if(l[i]) ans++;

    printf("%ld\n",ans);
    for(i=1;i<=n;i++)
        if(l[i]) printf("%ld %ld\n",i,l[i]);

    return 0;
}

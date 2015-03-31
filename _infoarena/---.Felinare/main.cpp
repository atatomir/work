#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

#define maxN 8200

long n,m,i,x,y;
vector<long> list[maxN];
long l[maxN],r[maxN];
bool sL[maxN],sR[maxN];
bool used[maxN];

bool pairUp(long node){
    vector<long>::iterator it;
    if(used[node]) return false;
    used[node] = true;

    for(it=list[node].begin();it!=list[node].end();it++){
        if(!r[*it]){
            l[node]=*it;
            r[*it] = node;
            return true;
        }
    }

    for(it=list[node].begin();it!=list[node].end();it++){
        if(pairUp(r[*it])){
            l[node]=*it;
            r[*it] = node;
            return true;
        }
    }
    return false;
}

void Support(long node){
    vector<long>::iterator it;

    for(it=list[node].begin();it!=list[node].end();it++){
        if(sR[*it]) continue;
        sR[*it] = true;
        sL[r[*it]] = false;
        Support(r[*it]);
    }
}

int main()
{
    freopen("felinare.in","r",stdin);
    freopen("felinare.out","w",stdout);

    scanf("%ld%ld",&n,&m);
    for(i=1;i<=m;i++){
        scanf("%ld %ld",&x,&y);
        list[x].push_back(y);
    }

    bool change=true;
    while(change){
        memset(used,0,sizeof(used));
        change = false;
        for(i=1;i<=n;i++)
            if(!l[i]) change |= pairUp(i);
    }

    long how = 2*n;
    for(i=1;i<=n;i++)
        if(l[i]) sL[i]=true,how--;

    for(i=1;i<=n;i++)
        if(!sL[i]) Support(i);

    printf("%ld\n",how);

    for(i=1;i<=n;i++){
        long ans=3;
        if(sL[i]) ans ^= 1;
        if(sR[i]) ans ^= 2;
        printf("%ld\n",ans);
    }

    return 0;
}

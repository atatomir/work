#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define maxN 10011

struct Ecuation{
    long pos,val;
};
Ecuation mp(long ppos,long vval){
    Ecuation ans;
    ans.pos=ppos; ans.val = vval;
    return ans;
}
bool cmp(const Ecuation& a,const Ecuation& b){
    return a.pos<b.pos;
}

long t,n,m,i,x,y,v;
vector<Ecuation> E[maxN];
long ans[maxN];

bool refresh(long id){
    sort(E[id].begin(),E[id].end(),cmp);
    long i=0,cnt=0;
    for(;i<E[id].size();i++){
        long def = E[id][i].pos;
        long defV = E[id][i].val;
        E[id][cnt++] = E[id][i];

        while(i<E[id].size()-1&&E[id][i+1].pos==def){
            i++;
            if(E[id][i].val != defV) return false;
        }
    }
    E[id].resize(cnt);

    return true;
}

bool check(){
    long i,j;
    for(i=n;i>1;i--){
        if(E[i].empty()) continue;
        if(!refresh(i)) return false;

        long sz = E[i].size();

        Ecuation act = E[i][sz-1];
        for(j=0;j<sz-1;j++) E[act.pos].push_back(mp(E[i][j].pos,E[i][j].val^act.val));
        E[i].resize(1); E[i][0] = act;
    }

    ans[0]=0;
    for(i=2;i<=n;i++){
        if(E[i].size()==0){
            ans[i]=0;
            continue;
        }
        ans[i] = E[i][0].val^ans[E[i][0].pos];
    }


    return true;
}

int main()
{
    freopen("bazaconii.in","r",stdin);
    freopen("bazaconii.out","w",stdout);

    scanf("%ld",&t);
    for(;t;t--){
        scanf("%ld %ld",&n,&m);
        for(i=1;i<=n;i++) E[i].clear();
        for(i=1;i<=m;i++){
            scanf("%ld%ld%ld",&x,&y,&v);
            if(x>y) swap(x,y);
            E[y].push_back(mp(x,v));
        }

        if(!check())
            printf("-1\n");
        else{
            for(i=1;i<=n;i++) printf("%ld ",ans[i]);
            printf("\n");
        }
    }

    return 0;
}

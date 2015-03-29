#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

#define maxN 100011

struct Record{
    long pos,val;
};
Record mp(long _pos,long _val){
    Record ans;
    ans.pos = _pos; ans.val = _val;
    return ans;
}
bool cmp(const Record& a,const Record& b){
    return a.val < b.val;
}

long n,m,i,cId,act;
long how[maxN];
Record comp[maxN];
Record Q[maxN];
long ans[maxN];

inline void addVal(long pos){
    long l,r,cnt;
    l = how[pos-1]; r = how[pos+1];

    cnt = l+r+1; act = max(act,cnt);
    how[pos-l] = cnt;
    how[pos+r] = cnt;
}

inline void addMore(long lim){
    while(cId<=n && comp[cId].val<=lim){
        addVal(comp[cId].pos);
        cId++;
    }
}

int main()
{
    freopen("secvmax.in","r",stdin);
    freopen("secvmax.out","w",stdout);

    scanf("%ld %ld",&n,&m);
    for(i=1;i<=n;i++){
        scanf("%ld",&comp[i].val);
        comp[i].pos=i;
    }
    for(i=1;i<=m;i++){
        scanf("%ld",&Q[i].val);
        Q[i].pos=i;
    }

    sort(comp+1,comp+n+1,cmp);
    sort(Q+1,Q+m+1,cmp);

    cId=1;
    for(i=1;i<=m;i++){
        addMore(Q[i].val);
        ans[Q[i].pos] = act;
    }

    for(i=1;i<=m;i++) printf("%ld\n",ans[i]);

    return 0;
}

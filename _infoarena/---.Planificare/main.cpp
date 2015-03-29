#include <iostream>
#include <cstdio>
#include <set>
#include <algorithm>

using namespace std;

#define maxN 100111

struct Show{
    long st,en;
};
bool cmp(const Show& a,const Show& b){
    return a.en<b.en;
}

long n,k,i,cnt;
Show sh[maxN];
multiset<long> S;
multiset<long>::iterator it;

int main()
{
    freopen("planificare.in","r",stdin);
    freopen("planificare.out","w",stdout);

    scanf("%ld %ld",&n,&k);
    for(i=1;i<=n;i++) {scanf("%ld%ld",&sh[i].st,&sh[i].en);sh[i].en--;}
    sort(sh+1,sh+n+1,cmp);

    for(i=1;i<=k;i++) S.insert(0);
    for(i=1;i<=n;i++){
        it = S.lower_bound(sh[i].st);
        if(it==S.begin()) continue;
        cnt++;
        it--; S.erase(it);
        S.insert(sh[i].en);
    }

    printf("%ld",cnt);

    return 0;
}

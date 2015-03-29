#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

#define maxN 5011
#define val first
#define pos second
#define mp make_pair

long n,i,j,cnt,def,ans;
pair<long,long> a[maxN];


bool cmp(const pair<long,long>& a,const pair<long,long>& b){
    return a.pos < b.pos;
}

int main()
{
    freopen("secv.in","r",stdin);
    freopen("secv.out","w",stdout);

    scanf("%ld",&n); a[n+1] = mp(-1,-1);
    for(i=1;i<=n;i++){
        scanf("%ld",&a[i].val);
        a[i].pos = i;
    }
    sort(a+1,a+n+1);

    for(i=1;i<=n;){
        cnt++; def = a[i].val;
        for(;a[i].val==def;i++){
            a[i].val=cnt;
        }
    }
    sort(a+1,a+n+1,cmp);

    ans = 1000000000;
    for(i=1;i<=n;i++){
        def = 1;
        for(j=i;j<=n;j++){
            if(def==a[j].val) def++;
            if(def>cnt){
                ans = min(ans,j-i+1);
                break;
            }
        }
    }


    if(ans==1000000000) ans = -1;
    printf("%ld",ans);

    return 0;
}

#include <iostream>
#include <cstdio>

using namespace std;

#define maxVal 1000000
#define maxK 1011

long n,k,i,act,x,def,vals;
long cnt[maxVal+33];
long add[maxVal+33];
long a[maxK],ans[maxK];

int main()
{
    freopen("ausoara.in","r",stdin);
    freopen("ausoara.out","w",stdout);

    scanf("%ld",&n);
    for(act=1;act<=n;act++){
        scanf("%ld",&k);
        for(i=1;i<=k;i++) scanf("%ld",&a[i]);
        for(i=1;i<=k;){
            def = a[i]; vals=1; i++;
            while(i<=k&&def==a[i]){
                vals++; i++;
            }

            add[def]++;
            if(cnt[def]==0 || cnt[def]>vals) cnt[def] = vals;
        }
    }

    for(i=1;i<=maxVal;i++){
        if(add[i]!=n) continue;
        while(cnt[i]){
            cnt[i]--;
            ans[++ans[0]] = i;
        }
    }

    printf("%ld ",ans[0]);
    for(i=1;i<=ans[0];i++) printf("%ld ",ans[i]);

    return 0;
}

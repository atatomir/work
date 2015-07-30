#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

#define maxP 111
#define maxS 375

long t,p,s,i,c,x,y,ans,act,need,now;
vector<long> oc[maxP];

bool used[maxS<<1];

int main()
{
    freopen("defrag.in","r",stdin);
    freopen("defrag.out","w",stdout);

    scanf("%ld",&t);
    scanf("%ld %ld",&p,&s);
    scanf("%ld",&c);
    for(i=1;i<=c;i++){
        scanf("%ld %ld",&x,&y);
        oc[x].push_back(y);
    }

    if(t==1){
        ans = 0;
        for(i=1;i<=p;i++)
            if(oc[i].size()==0) ans++;
        printf("%ld",ans);
        return 0;
    } else {
        for(act=1;act<=p;act++){
            for(i=1;i<=s*2;i++) used[i] = false;
            for(i=0;i<oc[act].size();i++) {
                long pos = oc[act][i];
                used[pos]=used[pos+s]=true;
            }

            ans = -1; need = oc[act].size(); now=0;
            for(i=1;i<need;i++) if(used[i]) now++;
            for(i=need;i<=2*s;i++){
                if(used[i]) now++;
                if(used[i-need]) now--;
                ans = max(ans,now);
            }
            printf("%ld ",need-ans);
        }
    }

    return 0;
}

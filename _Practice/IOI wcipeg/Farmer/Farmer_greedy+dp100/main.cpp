#include <iostream>
#include <cstdio>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

#define maxN 2015
#define maxQ 150000

long q,n,m,i,x,ans;
long ss,how[maxN],ff[maxN];
bool us[maxQ];

long compute(){
    long i,j;
    us[0]=true;
    for(i=1;i<=n;i++){
        for(j= q-ff[i] ;j>=0;j--)
            if(us[j])  us[j+ff[i]]=true;

        if(us[q]) break;
    }
    if(!us[q]) return 1;
    return 0;
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("test.in","r",stdin);
    #endif // ONLINE_JUDGE

    srand(time(NULL));

    scanf("%ld %ld %ld",&q,&n,&m);
    for(i=1;i<=n;i++){
        scanf("%ld",&x);
        ss += x; ff[i] = x;
    }
    for(i=1;i<=m;i++) scanf("%ld",&how[i]);

    if(ss >= q){
        q -= compute();
        printf("%ld", q  );
    } else{
        ans = q; q -= ss;
        sort(how+1,how+m+1);
        for(i=m; q > 0 ;i--){
            q -= how[i];
            ans--;
        }
        printf("%ld",ans);
    }



    return 0;
}

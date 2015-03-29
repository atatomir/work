#include <iostream>
#include <cstdio>

using namespace std;

#define maxN 1024

long n,k,m,i,x,y;
long ans[maxN];
bool enemy[maxN][maxN];
bool used[maxN];

void Back(long pas){
    if(!k) return;
    if(pas==n+1){
        k--;
        return;
    }

    for(long i=1;i<=n;i++){
        if(used[i]) continue;
        if(enemy[i][ans[pas-1]]) continue;

        ans[pas]=i;
        used[i]=true;
            Back(pas+1);if(!k) return;
        used[i]=false;
    }
}

int main()
{
    freopen("dusman.in","r",stdin);
    freopen("dusman.out","w",stdout);

    scanf("%ld%ld%ld",&n,&k,&m);
    for(i=1;i<=m;i++){
        scanf("%ld%ld",&x,&y);
        enemy[x][y]=enemy[y][x]=true;
    }
    Back(1);
    for(i=1;i<=n;i++) printf("%ld ",ans[i]);

    return 0;
}

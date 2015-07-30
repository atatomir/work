#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

#define maxN 505

long t,n,i,conf,x,y;
vector<long> list[maxN];
long ans[maxN];
long gr[maxN];
bool us[maxN];

void bfs(long node){
    if(us[node]) return;

    long i; us[node]=true;
    for(i=0;i<list[node].size();i++)
      if(!us[ list[node][i] ])
        bfs(list[node][i]);
}

long getHow(){
    long i,j;
    for(i=1;i<=n;i++) gr[i]=0;
    for(i=1;i<=n;i++){
      if(conf & (1<<(i-1))) us[i]=true;
      else us[i]=false;
    }

    for(i=1;i<=n;i++){
        if(conf & (1<<(i-1))) continue;

        for(j=0;j<list[i].size();j++){
          long node = list[i][j];
          if( conf &( 1<<(node-1) ) ) continue;
          gr[node]++;
        }
    }

    for(i=1;i<=n;i++){
      if(!us[i]){
          bfs(i);
          break;
      }
    }

    for(i=1;i<=n;i++)
      if(!us[i]) return 0;

    long ans = 0;
    for(i=1;i<=n;i++) ans = max(ans,gr[i]);
    return ans;
}

int main()
{
    freopen("grarbore.in","r",stdin);
    freopen("grarbore.out","w",stdout);

    scanf("%ld",&t);
    for(;t--;){
      scanf("%ld",&n);

        for(i=1;i<=n;i++) list[i].clear();
        for(i=1;i<=n;i++) ans[i]=0;

        for(i=1;i<n;i++) {
            scanf("%ld %ld",&x,&y); x++; y++;
            list[x].push_back(y);
            list[y].push_back(x);
        }

        for(conf = 1;conf < (1<<n);conf++){
            ans[ getHow() ]++;
        }

        for(i=1;i<=n-1;i++) printf("%ld ",ans[i]);
        printf("\n");
    }


    return 0;
}

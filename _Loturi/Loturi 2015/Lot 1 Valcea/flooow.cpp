#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

#define maxN 200011

long n,k,i,l,j;
long long C,cc;
long long a[maxN];
vector<long long> v;
long F[maxN],cost[maxN];

queue<long> Q;
bool inQueue[maxN];
bool us[maxN];
long prov[maxN];
long Flux;

bool flux(){
    long i;
    if(Flux--==0) return false;

    while(!Q.empty()) Q.pop();
    memset(inQueue,0,sizeof(inQueue));
    memset(us,0,sizeof(us));
    memset(prov,0,sizeof(prov));
    memset(cost,0,sizeof(cost));

    us[0] = true; cost[0] = 0;
    Q.push(0); inQueue[0]=true;

    while(!Q.empty()){
        long i;
        long node = Q.front(); Q.pop();
        inQueue[node] = false; cost[0]=0;

        if(node==0){
            for(i=1;i<=l;i++) {
                us[i] = true; cost[i] = 0;
                inQueue[i] = true; Q.push(i);
                prov[i] = 0;
            }
        } else
        if(node==l+1){
            //! nothing
        }else{
            i = node;

            if(i!=1 && F[i-1]){  //! go left
                if(!us[i-1] || cost[i-1]<cost[i]-v[i-1]  ){
                    us[i-1]=true; cost[i-1] = cost[i]-v[i-1];
                    if(!inQueue[i-1]){
                      Q.push(i-1); inQueue[i-1]=true;
                    }

                    prov[i-1] = i;
                }
            }

            if(i!=l && !F[i]){  //! go right
                if(!us[i+1] || cost[i+1]<cost[i]+v[i]){
                    us[i+1] = true; cost[i+1] = cost[i]+v[i];
                    if(!inQueue[i+1]){
                      Q.push(i+1); inQueue[i+1]=true;
                    }

                    prov[i+1]=i;
                }
            }

            if(!us[l+1] || cost[l+1]<cost[i]){  //! go dest
                us[l+1] = true; cost[l+1] = cost[i];

                prov[l+1] = i;
            }

        }
    }

    if(!us[l+1]) return false;

    long long How = 0;
    for(long node = l+1;node!=0;node=prov[node]){
        if(node == l+1 || prov[node]==0){
            continue;
        }else {
            if(prov[node] < node) {F[node-1]++;How+=v[node-1];}
            else                  {F[node]  --;How-=v[node];}
        }
    }

    cc += How;

    return true;
}

void solveLvl(){
    long i;
    long long ans,dif;
    bool fst = true;
    v.clear(); v.push_back(0);

    for(i=1;i<=l;){
        if(a[i]>=0){
            ans = 0;
            while(i<=l && a[i]>=0) ans += a[i++];
            v.push_back(ans);
        } else {
            dif = 0;
            while(i<=l && a[i]<0) dif += a[i++];

            if(fst || i>l) continue;
            v.push_back(dif);
        }

        fst = false;
    }

    l = v.size();

    //! make flux
    memset(F,0,sizeof(F));
    cc=0; Flux = k;
    while(flux());
    C+= cc;
}

int main()
{
    freopen("flooow.in","r",stdin);
    freopen("flooow.out","w",stdout);

    scanf("%ld %ld",&n,&k);
    for(i=1;i<=n;i++){
        scanf("%ld",&l);
        for(j=1;j<=l;j++) scanf("%lld",&a[j]);

        solveLvl();
    }

    printf("%ld %lld\n",k,C);

    return 0;
}

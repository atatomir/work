#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

#define maxN 111
#define maxV 1000000000

long n,i,k,x,j,T;
long timp[maxN],sEarly[maxN],sLate[maxN],p[maxN];
vector<long> list[maxN],listR[maxN];
vector<long> top;

void sortTop(){
    queue<long> Q,nQ;
    long i;

    for(i=1;i<=n;i++)
        if(!p[i]) nQ.push(i);

    while(!nQ.empty()){
        long pos = nQ.front(); nQ.pop();
        Q.push(pos);
        while(!Q.empty()){
            long nod = Q.front(); Q.pop();
            top.push_back(nod);
            for(i=0;i<list[nod].size();i++){
                long newNod = list[nod][i];
                p[newNod]--;
                if(!p[newNod]) Q.push(newNod);
            }
        }
    }
}

int main()
{
    freopen("pm2.in","r",stdin);
    freopen("pm2.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<=n;i++) scanf("%ld",&timp[i]);

    for(i=1;i<=n;i++){
        scanf("%ld",&k);
        for(;k;k--){
            scanf("%ld",&x);
            list[i].push_back(x);
            listR[x].push_back(i);
            p[x]++;
        }
    }

    sortTop();

    for(i=n;i;i--){
        long nod = top[i-1];

        for(j=0;j<list[nod].size();j++){
            long newNod = list[nod][j];
            sEarly[nod] = max(sEarly[nod],sEarly[newNod] + timp[newNod]);
        }
        T = max(T,sEarly[nod]+timp[nod]);
    }

    printf("%ld\n",T);

    for(i=1;i<=n;i++){
        long nod = top[i-1];

        if(!listR[nod].size()){
            sLate[nod] = T-timp[nod];
            continue;
        }

        sLate[nod] = maxV;
        for(j=0;j<listR[nod].size();j++){
            long newNod = listR[nod][j];
            sLate[nod] = min(sLate[nod],sLate[newNod]-timp[nod]);
        }
    }

    for(i=1;i<=n;i++) printf("%ld %ld\n",sEarly[i],sLate[i]);

    return 0;
}

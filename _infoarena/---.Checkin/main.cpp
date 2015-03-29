#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define A first
#define B second
#define maxN 1011
#define INF (1LL<<60)

typedef pair<long,long> Desk;

long n,K,P;
Desk d[maxN];
long long i,j,m;

bool cmp(long long a,long long b){
    return a > b;
}
bool isGood(long long T){
    vector<long long> V;
    long i;

    for(i=1;i<=n;i++){
        long long tmp = T - d[i].B;
        if(tmp < 0) continue;
        V.push_back(tmp/(long long)d[i].A);
    }
    sort(V.begin(),V.end(),cmp);

    long long need = P;
    for(i=0;i<V.size()&&i<K;i++){
        need -= V[i];
        if(need <= 0) return true;
    }
    if(!need) return true;
    return false;
}

int main()
{
    freopen("checkin.in","r",stdin);
    freopen("checkin.out","w",stdout);

    scanf("%ld",&n);
    for(i=1;i<=n;i++) scanf("%ld %ld",&d[i].A,&d[i].B);
    scanf("%ld %ld",&K,&P);

    i = 0; j = INF ;
    while(i<=j){
        m = (i+j)/2;
        if(isGood(m))
            j = m-1;
        else
            i = m+1;
    }
    if(P)
        printf("%ld",i);
    else {
        long Ans=1<<30;
        for(i=1;i<=n;i++)
            Ans = min(Ans,d[i].B);
        printf("%ld",Ans);
    }

    return 0;
}

#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>

using namespace std;

#define INF 2000000000
#define maxN 5000011
#define maxQ 30111

struct Query{
    long n,k,id;
};
Query qMp(long _n,long _k,long _id){
    Query ans;
    ans.n=_n;ans.k=_k;ans.id=_id;
    return ans;
}

long Q;
vector<Query> qq[15];
long NN[15];

bool ans[maxQ];
long dp[maxN],p,i,n,N;

stack<long> S;

int main()
{
    freopen("otilia.in","r",stdin);
    freopen("otilia.out","w",stdout);

    scanf("%ld",&Q);
    for(i=1;i<=Q;i++) {
        long _n,_k,_p;
        scanf("%ld%ld%ld",&_n,&_k,&_p);
        qq[_p].push_back(qMp(_n,_k,i));
        NN[_p] = max(NN[_p],_n);
    }

    for(p=1;p<=10;p++){
        if(qq[p].empty()) continue;

        while(!S.empty()) S.pop();
        dp[1] = INF; dp[2] = 1; N = NN[p];
        S.push(1);S.push(2);

        for(i=3;i<=N;i++){
            while(dp[S.top()] <= (i-S.top())*p) S.pop();
            dp[i] = i-S.top();
            S.push(i);
        }

        for(i=0;i<qq[p].size();i++){
            if(dp[qq[p][i].n] <= qq[p][i].k)
                ans[qq[p][i].id] = true;
            else
                ans[qq[p][i].id] = false;
        }
    }

    for(i=1;i<=Q;i++)
        if(ans[i]) printf("1\n"); else printf("0\n");


    return 0;
}

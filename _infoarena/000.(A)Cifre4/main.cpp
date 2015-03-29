#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

#define maxP 5000111

const long def[4]={2,3,5,7};

long t,n,p,i;
long dp[maxP],cf[maxP];
bool gasit;
vector<long> ans;

int main()
{
    freopen("cifre4.in","r",stdin);
    freopen("cifre4.out","w",stdout);

    scanf("%ld",&t);
    for(;t;t--){
        queue<long> Q;
        scanf("%ld %ld",&n,&p);
        for(i=0;i<p;i++) dp[i] = -1;

        gasit = false;
        for(i=0;i<4;i++){
            if(def[i]%p == 0) continue;
            dp[def[i]%p] = 0;  cf[def[i]%p] = def[i];
            Q.push(def[i]%p);
            if(def[i]%p == n){
                printf("%ld\n",def[i]);
                gasit = true;
                break;
            }
        }
        if(gasit) continue;

        while(!Q.empty()){
            long val = Q.front(); Q.pop();
            for(i=0;i<4;i++){
                long newVal = (val*10 + def[i])% p;
                if(dp[newVal] != -1) continue;
                dp[newVal] = val; cf[newVal] = def[i];
                Q.push(newVal);
            }
            if(dp[n] != -1) break;
        }

        if(dp[n] == -1) {printf("-1\n");continue;}

        ans.clear();
        while(n != 0){
            ans.push_back(cf[n]);
            n = dp[n];
        }

        for(i=ans.size()-1;i>=0;i--) printf("%ld",ans[i]);
        printf("\n");
    }

    return 0;
}

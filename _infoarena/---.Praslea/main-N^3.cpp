#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
 
using namespace std;
 
#define fordef(it,a,b) for(it=a;it<=b;it++)
#define mp make_pair
#define pb push_back
#define ll long long
#define pa(a,b) pair< a,b >
 
#define maxN 520
 
struct Monster{
    int Begin,End;
    int Force,Risk;
 
    void read(){
        scanf("%d%d%d%d",&Begin,&End,&Force,&Risk);
        End++; //! [Begin,End)
    }
    bool Active(const int& bg,const int& en){
        return (bg<End && en>=Begin);
    }
};
 
int n,rmax,i;
Monster Boss[maxN];
vector< int > Time;
long long ans;
 
int dp[maxN];
 
int solve(int t_begin,int t_end){
    memset(dp,0,sizeof(dp));
 
    for (int i=1;i<=n;i++){
        if (!Boss[i].Active(t_begin,t_end)) continue;
 
        int act_risk = Boss[i].Risk;
        int act_force = Boss[i].Force;
 
        for (int pos = rmax-act_risk;pos>=0;pos--){
            if (dp[pos+act_risk]>=dp[pos]+act_force) continue;
            dp[pos+act_risk] = dp[pos]+act_force;
        }
    }
 
    int ans = 0;
    for (int i=0;i<=rmax;i++) ans = max(ans,dp[i]);
    return ans;
}
 
int main()
{
    freopen("praslea.in","r",stdin);
    freopen("praslea.out","w",stdout);
 
    scanf("%d%d",&n,&rmax);
    for (i=1;i<=n;i++){
        Boss[i].read();
        Time.pb( Boss[i].Begin );
        Time.pb( Boss[i].End );
    }
    sort(Time.begin(),Time.end());
 
    for (i=1;i<Time.size();i++) {
        int t1 = Time[i-1];
        int t2 = Time[i]-1;
 
        ans += 1LL*(t2-t1+1)* solve(t1,t2);
    }
 
    printf("%lld",ans);
 
    return 0;
}

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

#define foreach(V) for(auto it=V.begin();it!=V.end();it++)
#define fordef(it,a,b) for(it=a;it<=b;it++)
#define mp make_pair
#define pb push_back
#define ll long long
#define pa(a,b) pair< a,b >

#define maxN 100011

int n,i,t,l;
char s[maxN];
int dp[maxN],how[maxN];
char vaj[maxN];

int ans;
deque< pa(int,int) > DQ;

void add(int v,int pos){
    while(!DQ.empty()){
        if( v > DQ.back().first ) break;
        DQ.pop_back();
    }
    DQ.push_back(mp(v,pos));
}
void check(int deny){
    if(DQ.empty()) return;
    if(DQ.front().second <= deny) DQ.pop_front();
}

int main()
{
    freopen("sirag2.in","r",stdin);
    freopen("sirag2.out","w",stdout);

    for(scanf("%d",&t);t--;){
        scanf("%d%d\n",&n,&l);
        scanf("%s",s+1);

        s[n+1] = vaj[n+1] = '*';
        dp[n+1] = how[n+1] = 0;

        for(i=n;i>0;i--){
            int from = i+l;
            if(from > n) from = n+1;

            if(s[i]=='*'){
                dp[i] = dp[from]+1;
                how[i] = how[from]+1;
                vaj[i] = vaj[from];
            } else {
                if( vaj[from]== s[i] || vaj[from]=='*' ){
                    dp[i] = dp[from]+1;
                    how[i] = 0;
                    vaj[i] = s[i];
                } else {
                    dp[i] = how[from]+1;
                    how[i] = 0;
                    vaj[i] = s[i];
                }
            }
        }

        ans = 1;
        fordef(i,1,l-1) add(dp[i],i);
        fordef(i,l,n){
            add(dp[i],i); check(i-l);
            ans = max(ans, DQ.front().first );
        }

        printf("%d\n",ans*l);
        while(!DQ.empty()) DQ.pop_back();
    }



    return 0;
}

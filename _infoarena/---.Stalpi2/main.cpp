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

#define maxN 55
#define maxD 10011
#define inf (400011)

int n,i,E;
int st[maxN];
int dp[maxN][maxD];
int def[maxD];
deque< pa(int,int) > DQ;

int diff(int a,int b){
    a -= b;
    return (a<0?-a:a);
}
void SlidingWindow(int id,int lim){
    int i;
    while(!DQ.empty()) DQ.pop_back();

    fordef(i,0,st[n]){
        while(!DQ.empty()){
            if(DQ.back().first < dp[id][i]) break;
            DQ.pop_back();
        }
        DQ.push_back( mp(dp[id][i],i) );
        if(DQ.front().second < i-lim) DQ.pop_front();

        dp[id][i] = DQ.front().first;
    }
}
bool good(int lim){
    int i,j;
    fordef(i,0,lim) dp[2][i] = diff(st[2],i);
    fordef(i,lim+1,st[n]) dp[2][i] = inf;

    fordef(i,3,n){
        SlidingWindow(i-1,lim);
        fordef(j,0,st[n])
            dp[i][j] = dp[i-1][j]+ diff(st[i],j);
    }
    return (dp[n][st[n]]<=E);
}

int getAns(){
    int l=0,r=st[n],mid;
    while(l<=r){
        mid = (l+r)>>1;
        if( good(mid) )
            r = mid-1;
        else
            l = mid+1;
    }
    return l;
}

int main()
{
    freopen("stalpi2.in","r",stdin);
    freopen("stalpi2.out","w",stdout);

    scanf("%d%d",&n,&E);
    fordef(i,1,n) scanf("%d",&st[i]);
    sort(st+1,st+n+1);

    printf("%d", getAns() );

    return 0;
}

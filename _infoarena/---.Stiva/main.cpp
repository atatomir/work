#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define foreach(V) for(auto it=V.begin();it!=V.end();it++)
#define fordef(it,a,b) for(it=a;it<=b;it++)
#define mp make_pair
#define pb push_back
#define ll long long
#define pa(a,b) pair< a,b >

#define maxN 511

int n,i,j,ans,pos;
char s[maxN];
int dp[maxN][maxN];

int Compute(int l,int r){
    int i;
    if(dp[l][r]!=-1) return dp[l][r];

    if(l==r) { dp[l][r]=0; return 0; }
    dp[l][r] = 1+Compute(l+1,r);
    fordef(i,l+2,r)
        if(s[i]==s[l]) dp[l][r] = min(dp[l][r], Compute(l+1,i-1)+Compute(i,r)+1 );

    return dp[l][r];
}

int main()
{
    freopen("stiva.in","r",stdin);
    freopen("stiva.out","w",stdout);

    scanf("%s",s+1); n = strlen(s+1);
    pos=1; ans = n;

    fordef(i,0,n)
        fordef(j,0,n)
            dp[i][j]=-1;

    fordef(i,2,n)
        if(s[i]!=s[i-1])
            s[++pos] = s[i];
    n = pos; s[0]='@';

    printf("%d", ans+Compute(0,n)*2 );

    return 0;
}

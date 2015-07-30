#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

#define foreach(V) for(auto it=V.begin();it!=V.end();it++)
#define fordef(it,a,b) for(it=a;it<=b;it++)
#define mp make_pair
#define pb push_back
#define ll long long
#define pa(a,b) pair< a,b >

#define maxN 311
#define dim dp[l][c]

int n,m,i,j,act,k,ans;
int a[maxN][maxN];
int how[maxN*maxN];
int dp[maxN][maxN];

map<int,int> M;
void Normalizare(){
    int i,j,cnt;
    M.clear(); cnt = 0;
    fordef(i,1,n){
        fordef(j,1,m){
            if(M.count(a[i][j])==0) M[ a[i][j] ] = ++cnt;
            a[i][j] = M[ a[i][j] ];
        }
    }
    M.clear();
}

inline void addValue(int v){
    if(!how[v]) act++;
    how[v]++;
}
inline void delValue(int v){
    how[v]--;
    if(!how[v]) act--;
}

void solve(int l,int c){
    memset(how,0,sizeof(how)); act = 0;
    int i;

    while(l<=n&&c<=m){
        dim = dp[l-1][c-1]+1;
        fordef(i,l-dim+1,l) addValue(a[i][c]);
        fordef(i,c-dim+1,c) addValue(a[l][i]);
        delValue(a[l][c]);

        while( act > k ) {
            fordef(i,l-dim+1,l) delValue(a[i][c-dim+1]);
            fordef(i,c-dim+2,c) delValue(a[l-dim+1][i]);
            dim--;
        }

        ans = max(ans,dp[l++][c++]);
    }

}

int main()
{
    freopen("submatrix.in","r",stdin);
    freopen("submatrix.out","w",stdout);

    scanf("%d%d%d",&n,&m,&k);
    fordef(i,1,n)
        fordef(j,1,m)
            scanf("%d",&a[i][j]);

    Normalizare(); ans = 1;
    fordef(i,1,n) solve(i,1);
    fordef(i,2,m) solve(1,i);

    printf("%d",ans);

    return 0;
}

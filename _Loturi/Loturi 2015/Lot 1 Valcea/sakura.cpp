#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

#define maxN 512
#define INF (5000000)
#define long long long

long t,i,n,m,x,y,cc,sumAll;
vector<long> listA[maxN],listB[maxN];
bool usB[maxN],usA[maxN];
long dp[maxN][maxN],mat[maxN][maxN];
long cnt[maxN],sL[maxN],sC[maxN];
bool usLine[maxN],usCol[maxN];

pair<long,long> v[maxN*maxN];

bool cmp(const pair<long,long>& a,const pair<long,long>& b){
    return mat[a.first][a.second] > mat[b.first][b.second];
}

void DfsA(long node){
    long i;
    cnt[node]=1;

    usA[node]=true;
    for(long i=0;i<listA[node].size();i++){
        if(usA[ listA[node][i] ] ){
            listA[node][i] = listA[node][ listA[node].size()-1 ];
            listA[node].pop_back();
            break;
        }
    }

    for(i=0;i<listA[node].size();i++){
        DfsA(listA[node][i]);
        cnt[node] += cnt[ listA[node][i] ];
    }
}
void DfsB(long node){
    usB[node]=true;

    long i;

    for(long i=0;i<listB[node].size();i++){
        if(usB[ listB[node][i] ] ){
            listB[node][i] = listB[node][ listB[node].size()-1 ];
            listB[node].pop_back();
            break;
        }
    }

    for(i=0;i<listB[node].size();i++) {
        DfsB(listB[node][i]);
    }
}

void Dfs(long node){
    long i,j,rf;

    for(i=0;i<listA[node].size();i++) Dfs(listA[node][i]);

    for(rf=0;rf<m;rf++){
        if(listA[node].size() < listB[rf].size()){
            dp[node][rf]=INF;
            continue;
        }

        long sz1 = listA[node].size();
        long sz2 = listB[rf].size();

        for(i=0;i<sz1;i++){
            for(j=0;j<sz2;j++){
                mat[i][j] = dp[ listA[node][i] ][ listB[rf][j] ];
            }
        }
        for(i=0;i<sz1;i++){
            for(j=sz2;j<sz1;j++){
                mat[i][j] = cnt[ listA[node][i] ];
            }
        }

        //! make sums
        for(i=0;i<sz1;i++) sL[i]=sC[i]=0;
        for(i=0;i<sz1;i++)
            for(j=0;j<sz1;j++){ sL[i]+=mat[i][j]; sC[j]+=mat[i][j]; }

        sumAll = 0;
        for(i=0;i<sz1;i++) sumAll += 1LL*sL[i]+1LL*sC[i];

        //! calc mat
        cc=0;
        for(i=0;i<sz1;i++)
            for(j=0;j<sz1;j++) {
                mat[i][j] = sL[i]+sC[j]-2*mat[i][j];
                v[++cc] = make_pair(i,j);
            }

        sort(v+1,v+cc+1,cmp);
        long ans=0;
        memset(usLine,0,sizeof(usLine));
        memset(usCol,0,sizeof(usCol));

        for(i=1;i<=cc;i++){
            if(usLine[ v[i].first ] || usCol[ v[i].second ]) continue;
            usLine[ v[i].first ] = usCol[ v[i].second ] = true;

            ans += mat[ v[i].first ][ v[i].second ];
        }

        dp[node][rf] = (sumAll - ans)>>1;
    }
}

int main()
{
    freopen("sakura.in","r",stdin);
    freopen("sakura.out","w",stdout);

    scanf("%lld",&t);
    for(;t--;){
        scanf("%lld",&n);
        for(i=0;i<n;i++) listA[i].clear();
        memset(usA,0,sizeof(usA));

        for(i=1;i<n;i++){
            scanf("%lld %lld",&x,&y);
            listA[x].push_back(y);
            listA[y].push_back(x);
        }

        scanf("%lld",&m);
        for(i=0;i<m;i++) listB[i].clear();
        memset(usB,0,sizeof(usB));

        for(i=1;i<m;i++){
            scanf("%lld %lld",&x,&y);
            listB[x].push_back(y);
            listB[y].push_back(x);
        }

        DfsB(0);
        DfsA(0);
        Dfs(0);

        if(n < m) dp[0][0]=INF;
        if(dp[0][0]>=INF) printf("-1\n"); else{
            if(dp[0][0] != n-m) dp[0][0] = n-m;
            printf("%lld\n",dp[0][0]);
        }

    }

    return 0;
}

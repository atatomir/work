#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

#define maxCnt 211
#define maxL 13
#define maxS 200011

long n,i;
char sm[maxCnt][maxL];
char S [maxS],ss[maxS];
vector<long> list[maxS];

char aa[maxL];
long pr[maxL];
bool vis[maxS];
long ans,sDim;

void make_pref(long n){
    long i,q;
    pr[1]=0; q=0;
    for(i=2;i<=n;i++){
        while( q && aa[i] != aa[q+1] )
            q = pr[q];
        if(aa[i] == aa[q+1]) q++;
        pr[i] = q;
    }
}

void setEdges(long id){
    long i,n; n=0;
    for(i=1;;i++){
        aa[i] = sm[id][i];
        if(aa[i]<'A'||'Z'<aa[i]) break;
    } n = i-1;

    make_pref(n);
    long q = 0;
    for(i=1;i<= sDim ;i++){
        while(q && S[i] != aa[q+1]) q = pr[q];
        if(S[i]==aa[q+1]) q++;
        if(q==n){
            list[ i-n ].push_back(i);
            q = pr[q];
        }
    }
}

void dfs(long node){
    if(vis[node])return;
    vis[node] = true;

    for(long i=0;i<list[node].size();i++){
        long wh = list[node][i];
        if(vis[wh]) return;
        dfs(wh);
    }

    ans = max(ans,node);
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("test.in","r",stdin);
    #endif

    while( 1>0 ){
        scanf("%s", sm[++n]+1 );
        if(sm[n][1]=='.') break;
    } n--;

    while( 0<1){
        scanf("%s",S+sDim+1);
        long _last = sDim;
        sDim += strlen(S+sDim+1);
        if(_last == sDim) break;
    } sDim = strlen(S+1);

    for(i=1;i<=n;i++) setEdges(i);
    dfs(0);

    printf("%ld",ans);

    return 0;
}

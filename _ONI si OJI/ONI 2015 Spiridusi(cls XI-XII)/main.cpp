#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

#define maxN 100001
#define max(a,b) (a<b?b:a)
#define maxLog 18

int n,c,i,x,y;
vector<int> list[maxN];
int s[maxN]; //! cnt spiridusi
long long p[maxN]; //! coeficient
long par[maxN];
bool us[maxN];
long long ans=-(1LL<<60);

int who[maxN];
int posL,posR;

int where[maxLog][maxN];
long long dp[maxLog][maxN];
int logId[maxN];

int ll[maxN];

void dfsIni(int node){
    us[node] = true;
    for(int i=0;i<list[node].size();i++){
        int newNode = list[node][i];
        if(us[newNode]) continue;

        par[newNode] = node;
        s[newNode] += s[node];
        p[newNode] += p[node];
        dfsIni(newNode);
    }
}

//! folosim smenul de la stramosi ca un rmq
void do_magic(){
    int i,j;
    for(i=1;i<=n;i++) {where[0][i]=par[i];dp[0][i]=p[i];}

    for(i=1;i<maxLog;i++){
        int def = (1<<i);
        for(j=0;j<=n;j++){
            where[i][j] = where[i-1][ where[i-1][j] ];
            dp[i][j] = min(dp[i-1][j], dp[i-1][ where[i-1][j] ] );
        }
    }

    logId[1]=0;
    for(i=2;i<=n;i++){
        logId[i] = logId[i-1];
        if( i == (1<<(logId[i]+1)) ) logId[i]++;
    }
}

long long getMagic( ){
    long long ans = (1LL<<60);

    int i = ll[ who[posR-1] ],j=posR-1,mid;
    while(i<=j){
        mid = (i+j)>>1;
        if( s[ who[posR] ]-s[ who[mid] ] <= c )
            j = mid-1;
        else
            i = mid+1;
    }
    posL = ll[who[posR]] = i;

    //! am determinat intervalul

    int dim = posR-posL;
    int logg = logId[dim];
    int src1 = who[posR-1];
    int src2 = who[posL+(1<<logg)-1];

    return p[ who[posR] ]-min(dp[logg][src1],dp[logg][src2]);
}

void dfs(int node){
    who[++posR] = node;

    long long val = getMagic();
    ans = max(ans,val);

    for(int i=0;i<list[node].size();i++){
        if( par[list[node][i]]==node )
            dfs(list[node][i]);
    }

    posR--;
}

int main()
{
    freopen("spiridusi.in","r",stdin);
    freopen("spiridusi.out","w",stdout);

    scanf("%d %d",&n,&c);
    for(i=1;i<=n;i++) scanf("%d",&s[i]);
    for(i=1;i<=n;i++) scanf("%lld",&p[i]);
    for(i=1;i<n;i++){
        scanf("%d %d",&x,&y);
        list[x].push_back(y);
        list[y].push_back(x);
    }

    par[1] = 0;
    dfsIni(1);

    do_magic();

    posR=0; dfs(1);

    printf("%lld",ans);
    cerr << ans;

    return 0;
}

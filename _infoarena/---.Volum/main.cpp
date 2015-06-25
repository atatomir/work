#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

#define maxN 785
#define mp make_pair
#define xx first
#define yy second

const long defX[4]={-1,1,0,0};
const long defY[4]={0,0,-1,1};

long n,m,i,j,hlim;
long h[maxN][maxN];
bool us[maxN][maxN];
bool added[maxN][maxN];
long long ans;

struct cmp{
    bool operator()(const pair<long,long>& a,const pair<long,long>& b){
        return h[a.xx][a.yy] > h[b.xx][b.yy];
    }
};
priority_queue< pair<long,long>,vector< pair<long,long> >,cmp > H;
queue<pair<long,long> > Q;

void dfs(long x,long y){
    //! trecem la bfs...
    us[x][y] = true; Q.push( mp(x,y) );
    while(!Q.empty()){
        pair<long,long> act = Q.front();Q.pop();
        x = act.xx; y = act.yy;

        ans += 1LL*(hlim-h[x][y]);
        for(long i=0;i<4;i++){
            long _x = x + defX[i];
            long _y = y + defY[i];

            if(us[_x][_y]) continue;
            if(h[_x][_y]>hlim) {
                if(!added[_x][_y]) H.push( mp(_x,_y) );
                added[_x][_y]=true;
                continue;
            }
            us[_x][_y]=true;
            Q.push(mp(_x,_y));
        }
    }

    /*us[x][y] = true;

    ans += 1LL*(hlim-h[x][y]);
    for(long i=0;i<4;i++){
        long _x = x + defX[i];
        long _y = y + defY[i];

        if(us[_x][_y]) continue;
        if(h[_x][_y]>hlim) {
            if(!added[_x][_y]) H.push( mp(_x,_y) );
            added[_x][_y]=true;
            continue;
        }
        dfs(_x,_y);
    }*/
}

void see(){
    //! only for my pleasure

    cerr << "\n";
    for(long i=1;i<=n;i++){
        for(long j=1;j<=m;j++){
            if(us[i][j]) cerr << "/ "; else
            if(added[i][j]) cerr << "H "; else
            cerr << "o ";
        }
        cerr << '\n';
    }

    cerr << "\n";
}

int main()
{
    freopen("volum.in","r",stdin);
    freopen("volum.out","w",stdout);

    scanf("%ld %ld",&n,&m);
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            scanf("%ld",&h[i][j]);

    for(i=1;i<=n;i++) us[i][0]=us[i][m+1]=true;
    for(i=1;i<=m;i++) us[0][i]=us[n+1][i]=true;

    for(i=1;i<=n;i++) {H.push( mp(i,1) );H.push( mp(i,m) ); added[i][1]=added[i][m]=true;}
    for(i=1;i<=m;i++) {H.push( mp(1,i) );H.push( mp(n,i) ); added[1][i]=added[n][i]=true;}

    while(!H.empty()){
        //see();

        pair<long,long> act = H.top(); H.pop();
        if(us[act.xx][act.yy]) continue;

        hlim = h[act.xx][act.yy];
        dfs(act.xx,act.yy);
    }

    printf("%lld",ans);


    return 0;
}

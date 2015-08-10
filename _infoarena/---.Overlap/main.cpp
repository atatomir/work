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

#define maxN 815
#define mod 717

const int sinAlfa[4]={0,1,0,-1};
const int cosAlfa[4]={1,0,-1,0};

struct Point{
    int x,y;
    int id;

    void init(int _id){
        scanf("%d %d",&x,&y);
        id = _id;
    }
    void Rotate(int how){
        int _x = x,_y = y;
        x = cosAlfa[how]*_x - sinAlfa[how]*_y;
        y = sinAlfa[how]*_x + cosAlfa[how]*_y;
    }
    void Shift(int sh_x,int sh_y){
        x += sh_x;
        y += sh_y;
    }
    bool operator==(const Point& who){
        return (x==who.x)&&(y==who.y);
    }
};

struct Hash{
    vector< Point > C[mod];

    int abss(int x){
        if(x<0) return -x;
        return x;
    }
    int getKey(const Point& p){
        return (abss(p.x)*117+abss(p.y))%mod;
    }
    void init(){
        for(int i=0;i<mod;i++) C[i].clear();
    }
    void add(Point p){
        C[ getKey(p) ].pb(p);
    }
    int Find(Point p){
        int key = getKey(p);
        for(auto e:C[key])
            if(e==p) return e.id;
        return -1;
    }
};

int n,i,cnt;
Point P[maxN];
Point aux[maxN];
Hash H;
int Rotation,Sh_x,Sh_y;
int dir[maxN],dir2[maxN];
bool us[maxN];
int ans[maxN];

void dfs(int node){
    if(us[node]) return;
    us[node] = true; cnt++;
    if(dir[node]) dfs(dir[node]);
}

bool Test_Answer(){
    int i;
    memset(dir,0,sizeof(dir));
    memset(dir2,0,sizeof(dir2));
    memset(us,0,sizeof(us));

    for(i=1;i<=n;i++){
        Point act = aux[i];
        act.Shift(Sh_x,Sh_y);

        int id = H.Find(act);
        if(id!=-1) { dir[ i ] = id ; dir2[ id ] = i ; }
    }

    for(i=1;i<=n;i++){
        if(us[i]) continue;
        if(dir2[i]!=0) continue;
        cnt = 0;

        dfs(i);
        if( (cnt&1)==1 ) return false;
    }
    for(i=1;i<=n;i++){
        if(us[i]) continue;
        cnt = 0;

        dfs(i);
        if( (cnt&1)==1 ) return false;
    }
    return true;
}

void dfsAns(int node){
    if(us[node]) return;
    us[node] = true; cnt ^= 1;
    ans[node] = cnt+1;
    if(dir[node]) dfsAns(dir[node]);
}

bool Set_Answer(){
    int i;
    memset(dir,0,sizeof(dir));
    memset(dir2,0,sizeof(dir2));
    memset(us,0,sizeof(us));

    for(i=1;i<=n;i++){
        Point act = aux[i];
        act.Shift(Sh_x,Sh_y);

        int id = H.Find(act);
        if(id!=-1) { dir[ i ] = id ; dir2[ id ] = i ; }
    }

    for(i=1;i<=n;i++){
        if(us[i]) continue;
        cnt = 0;

        if(dir2[i]==0)dfsAns(i);
    }
    for(i=1;i<=n;i++){
        if(us[i]) continue;
        cnt = 0;

        dfsAns(i);
    }
    return true;
}

int main()
{
    freopen("overlap.in","r",stdin);
    freopen("overlap.out","w",stdout);

    scanf("%d",&n); H.init();
    for(i=1;i<=n;i++) {
        P[i].init(i);
        H.add(P[i]);
    }

    for(Rotation=0;Rotation<4;Rotation++){
        for(i=1;i<=n;i++){
            aux[i] = P[i];
            aux[i].Rotate(Rotation);
        }

        for(i=2;i<=n;i++){
            Sh_x = P[1].x-aux[i].x;
            Sh_y = P[1].y-aux[i].y;

            if( Test_Answer() ){
                Set_Answer();
                for(int j=1;j<=n;j++) printf("%d\n",ans[j]);

                return 0;
            }
        }
    }


    return 0;
}

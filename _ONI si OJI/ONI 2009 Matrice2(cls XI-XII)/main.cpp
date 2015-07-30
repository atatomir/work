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

#define maxN 311
#define maxQ 20011

const int defX[4]={0,0,-1,1};
const int defY[4]={-1,1,0,0};

struct Cell{
    int x,y,v;
    bool operator<(const Cell& who)const{
        return v > who.v;
    }
};

struct Query{
    pa(int,int) from,to;
    int ans,id;

    void read(int _id ){
        int _x1,_y1,_x2,_y2;
        scanf("%d%d%d%d",&_x1,&_y1,&_x2,&_y2);

        from = mp(_x1,_y1);
        to = mp(_x2,_y2);
        ans = 0; id = _id;
    }
    bool operator<(const Query& who)const{
        return ans > who.ans;
    }
};

int n,i,j,q,cnt,v,k,wh;
int id[maxN][maxN];
Cell e[maxN*maxN];
vector<int> list[maxN*maxN];
Query Q[maxQ];

int dad[maxN*maxN];
bool us[maxN][maxN];
bool uss[maxN*maxN];

int Find(int node){
    if(dad[node]==node) return node;
    dad[node] = Find(dad[node]);
    return dad[node];
}
void Merge(int x,int y){
    x = Find(x); y = Find(y);
    if(x!=y) dad[y]=x;
}

bool cmp(const Query& a,const Query& b){
    return a.id < b.id;
}

int main()
{
    freopen("matrice2.in","r",stdin);
    freopen("matrice2.out","w",stdout);

    scanf("%d%d",&n,&q);
    fordef(i,1,n){
        fordef(j,1,n){
            id[i][j] = ++cnt;
            scanf("%d",&v);
            e[cnt].x = i;
            e[cnt].y = j;
            e[cnt].v = v;
        }
    }
    fordef(i,1,n){
        fordef(j,1,n){
           fordef(k,0,3){
                int xx = i + defX[k];
                int yy = j + defY[k];

                if(!id[xx][yy]) continue;
                list[ id[i][j] ].pb( id[xx][yy] );
           }
        }
    }
    sort(e+1,e+cnt+1);
    fordef(i,1,q) Q[i].read(i);

    for(int pas=1<<20;pas;pas>>=1){
        sort(Q+1,Q+q+1);
        fordef(i,1,cnt) dad[i]=i; wh = 1;
        memset(us,0,sizeof(us));
        memset(uss,0,sizeof(uss));

        //! work hard
        fordef(i,1,q){
            while(wh<=cnt && Q[i].ans+pas <= e[wh].v) {
                Cell act = e[wh++];
                us[act.x][act.y]=true;
                uss[ id[act.x][act.y] ]=true;

                foreach(list[ id[act.x][act.y] ]){
                    if(!uss[*it]) continue;
                    Merge(id[act.x][act.y],*it);
                }
            }

            int R1 = Find( id[ Q[i].from.first ][ Q[i].from.second ] );
            int R2 = Find( id[ Q[i].to.first ][ Q[i].to.second ] );

            if(R1==R2) Q[i].ans+=pas;
        }
    }

    sort(Q+1,Q+q+1,cmp);
    fordef(i,1,q) printf("%d\n",Q[i].ans);


    return 0;
}

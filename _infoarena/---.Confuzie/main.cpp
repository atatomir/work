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

#define maxN 200011
#define maxLog 20

class Batog{
    private:
        int *R;
        int *smen;
        int n,dim,cnt;

        int getBlock(int pos){ return (pos+dim-1)/dim; }
        int getHigh(int id) { return id*dim; }
        int getLow(int id) { return (id-1)*dim+1; }

    public:
        void init(int _n,int *_R,int *_smen){
            R = _R; smen = _smen; n = _n;
            dim = (int)sqrt(n);
            cnt = (n+dim-1)/dim;
        }
        void update(int l,int r,int val){
            int i;
            int fBlock = getBlock(l);
            int lBlock = getBlock(r);

            if(lBlock-fBlock<=1){
                fordef(i,l,r) R[i] +=val;
                return;
            }

            fordef(i,fBlock+1,lBlock-1) smen[i]+=val;
            int high = getHigh(fBlock);
            fordef(i,l,high) R[i] += val;
            int low = getLow(lBlock);
            fordef(i,low,r) R[i] += val;
        }
        int query(int pos){
            return R[pos] + smen[ getBlock(pos) ];
        }
};

int n,i,m,op,x,y,cnt;
vector<int> list[maxN];
int state[maxN],lvl[maxN];
int up[maxLog][maxN];
int ls[maxN],lr[maxN];
//!----------------------
    int way[maxN];
    int Rc[maxN];
    int smenc[maxN];
    Batog smen;
//!----------------------

void dfs(int node){
    way[++cnt] = node; ls[node] = cnt;
    foreach(list[node]){
        if(lvl[*it]) continue;
        lvl[*it] = lvl[node]+1;
        up[0][*it] = node;
        dfs(*it);
    }
    lr[node] = cnt;
}
void make_stramosi(){
    int i,j;
    for(i=1;(1<<i)<=n;i++){
        int def = (1<<(i-1));
        for(j=1;j<=n;j++) up[i][j] = up[i-1][ up[i-1][j] ];
    }
}
int getAns(int x,int y){
    if(state[x]==1) return x;

    int src = smen.query(ls[x])+1;

    int i=maxLog;
    for(int pas = 1<<maxLog;pas;pas>>=1,i--){
        if(lvl[x] > lvl[y]-pas) continue;
        int dir = up[i][y];
        if(smen.query(ls[dir]) >= src) y = dir;
    }
    return y;
}

int main()
{
    freopen("confuzie.in","r",stdin);
    freopen("confuzie.out","w",stdout);

    scanf("%d%d",&n,&m);
    fordef(i,2,n){
        scanf("%d%d",&x,&y);
        list[x].push_back(y);
        list[y].push_back(x);
    }

    lvl[1] = 1;
    dfs(1);
    make_stramosi();
    smen.init(n,Rc,smenc);

    for(;m--;){
        scanf("%d",&op);
        if(op==0){
            scanf("%d",&x);
            if(state[x]==0) smen.update(ls[x],lr[x],+1);
            else            smen.update(ls[x],lr[x],-1);
            state[x] ^= 1;
        } else {
            scanf("%d%d",&x,&y);
            if(smen.query(ls[x])==smen.query(ls[y])){
                if(state[x]) printf("%d\n",x);
                else         printf("-1\n");
                continue;
            }

            printf("%d\n",getAns(x,y));
        }
    }

    return 0;
}

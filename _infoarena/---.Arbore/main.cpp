#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <bitset>

using namespace std;

#define foreach(V) for(auto it=V.begin();it!=V.end();it++)
#define fordef(it,a,b) for(it=a;it<=b;it++)
#define mp make_pair
#define pb push_back
#define ll long long
#define pa(a,b) pair< a,b >

#define maxN 100011
#define maxSqrt 350
#define Elem pair<int,int>

bitset<1000005> BS[maxSqrt];

class Hash{
    private:
        int id;

    public:
        void init(int _id){
            id = _id;
            BS[id].reset();
        }
        void add(int v){
            BS[id].set(v,1);
        }
        void rm(int v){
            BS[id].set(v,0);
        }
        bool Find(int v){
            if(v < 0 || v > 1000000) return false;
            return BS[id].test(v);
        }
};

class Batog{
    private:
        int n,dim;
        int *R;
        int *bonus;
        Hash *Smen;

        int getBlock(int pos){
            return (pos+dim-1)/dim;
        }
        int getStart(int x){
            return dim*(x-1)+1;
        }
        int getStop(int x){
            return min(dim*x,n);
        }
        void changeVal(int pos,int val){
            int actBlock = getBlock(pos);

            Smen[actBlock].rm( R[pos]);
            R[pos] += val;
            Smen[actBlock].add( R[pos] );
        }
        void Refresh(int id){
            int lim = getStop(id);
            for(int i=getStart(id); i<=lim ;i++)
                Smen[id].add(R[i]);

            //cerr << Smen[1].Find(1) << '\n';
        }

    public:
        void init(int _n,int *_R,Hash *_Smen,int *_bonus){
            n = _n; R = _R; Smen = _Smen; bonus = _bonus;
            dim = (int)sqrt(1.00*n);

            int lim = getBlock(n);
            for(int i=1;i<= lim ;i++) {
                Smen[i].init(i); bonus[i]=0;
                Smen[i].add(0);
            }
        }
        void add(int l,int r,int val){
            int fBlock = getBlock(l);
            int lBlock = getBlock(r);

            if(lBlock-fBlock<=1){
                for(int i=l;i<=r;i++) changeVal(i,val);
                Refresh(lBlock);
                Refresh(fBlock);
                return;
            }

            int lim = getStop(fBlock);
            for(int i = l ; i <= lim ; i++) {Smen[fBlock].rm( R[i] ); R[i] += val;}
            for(int i = getStart(lBlock) ; i <= r ; i++) {Smen[lBlock].rm( R[i] ); R[i] += val;}
            Refresh(fBlock);
            Refresh(lBlock);
            for(int i=fBlock+1;i<lBlock;i++) bonus[i]+=val;
        }
        int Query(int s){
            int lim = getBlock(n);
            for(int i=1;i<=lim;i++){
                int aux = s - bonus[i];

                if( Smen[i].Find(aux) ){
                    int stop = getStop(i);
                    for(int j = getStart(i); j<= stop;j++ )
                        if(R[j]==aux) return j;
                }
            }
            return -1;
        }
};

int n,m,i,x,y,cnt,op,s;
int vals[maxN];
vector<int> list[maxN];
bool us[maxN];
int lf[maxN],rh[maxN];

//!----------------------
int R[maxN];
int bonus[maxSqrt];
Hash Smen[maxSqrt];

Batog Work;
//!----------------------


void dfs(int node){
    us[node] = true;
    lf[node] = ++cnt; vals[cnt]=node;
    for(auto e:list[node]){
        if(us[e]) continue;
        dfs(e);
    }
    rh[node] = cnt;
}

int main()
{
    freopen("arbore.in","r",stdin);
    freopen("arbore.out","w",stdout);

    scanf("%d %d",&n,&m);
    for(i=1;i<n;i++){
        scanf("%d%d",&x,&y);
        list[x].pb(y);
        list[y].pb(x);
    }

    dfs(1);
    Work.init(n,R,Smen,bonus);

    for(;m--;){
        scanf("%d",&op);
        if(op==1){
            scanf("%d%d",&x,&y);
            Work.add(lf[x],rh[x],y);
        } else {
            scanf("%d",&s);
            int ans = Work.Query(s);
            printf("%d\n", (ans==-1?-1:vals[ans]) );
        }
    }


    return 0;
}

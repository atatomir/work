#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

#define maxM 500011
#define maxN 530
#define opUpdate 1
#define opQuery 2
#define opUndo 3

struct Query{
    long qX,qY,id;
    Query(long _qX,long _qY,long _id){
        qX = _qX; qY = _qY; id = _id;
    }
};
struct Node{
    long qX,qY,qV,dad;
    vector<Query> Q;
    vector<long> list;

    Node(){
        qX=qY=qV=dad=0;
        list.clear();
        Q.clear();
    }
    Node(long _qX,long _qY,long _qV,long _dad){
        qX=_qX;qY=_qY;qV=_qV;dad=_dad;
        list.clear();
        Q.clear();
    }
};

class AIB{
    private:
        long C[maxN][maxN];
        long nn;

        inline long zrs(long x){ return (x^(x-1))&x; }
    public:
        AIB(){}
        AIB(long _nn){
            memset(C,0,sizeof(C));
            nn=_nn;
        }

        void add(long x,long y,long v){
            while(x<=nn){
                long _y=y;
                while(y<=nn){
                    C[x][y]+=v;
                    y+=zrs(y);
                }
                y=_y;
                x+=zrs(x);
            }
        }
        long sum(long x,long y){
            long ans =0;
            while(x){
                long _y = y;
                while(y){
                    ans += C[x][y];
                    y-=zrs(y);
                }
                y=_y;
                x-=zrs(x);
            }
            return ans;
        }
};

long n,m,i,pos,act,op,x,y,z,cnt,qCnt;
Node Tree[maxM];
long wh[maxM];
long ans[maxM];
AIB aib;

void dfs(long node){
    long i;
    if(node)aib.add(Tree[node].qX,Tree[node].qY,Tree[node].qV);

    if(node)
    for(i=0;i<Tree[node].Q.size();i++){
        Query act = Tree[node].Q[i];
        ans[act.id] = aib.sum(act.qX,act.qY);
    }
    for(i=0;i<Tree[node].list.size();i++)
        dfs(Tree[node].list[i]);

    if(node)aib.add(Tree[node].qX,Tree[node].qY,-Tree[node].qV);
}

int main()
{
    freopen("undo.in","r",stdin);
    freopen("undo.out","w",stdout);

    scanf("%ld %ld",&n,&m);
    aib = AIB(n);
    for(;m;m--){
        scanf("%ld",&op);
        if(op==opUpdate){
            scanf("%ld %ld %ld",&x,&y,&z);
            Tree[++pos] = Node(x,y,z,act);
            Tree[act].list.push_back(pos);
            act = pos;

            wh[++cnt]=pos;
        }else
        if(op==opQuery){
            scanf("%ld %ld",&x,&y);
            Tree[act].Q.push_back( Query(x,y,++qCnt) );
        }else{
            scanf("%ld",&x);
            act = wh[cnt-x];
            wh[++cnt] = act;
        }
    }

    dfs(0);
    for(i=1;i<=qCnt;i++) printf("%ld\n",ans[i]);

    return 0;
}

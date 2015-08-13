#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define fordef(it,a,b) for(it=a;it<=b;it++)
#define mp make_pair
#define pb push_back
#define ll long long
#define pa(a,b) pair< a,b >

#define maxN 50011
#define lSon (node<<1)
#define rSon (lSon|1)
#define logg 16

struct Trie{
    Trie *lfSon,*rhSon;
    int cnt;

    Trie(){
        lfSon = rhSon = NULL;
        cnt = 0;
    }
    Trie* goLeft(){
        if (lfSon==NULL) lfSon = new Trie();
        return lfSon;
    }
    Trie* goRight(){
        if (rhSon==NULL) rhSon = new Trie();
        return rhSon;
    }
};

struct myTrieManager{
    //! just some functions that manage a Trie

    int getCount(Trie* act,int val){
        for (int actLog = logg;actLog>=0;actLog--){
            int def = 1<<actLog;
            if (act->cnt==0) return 0;
            if ( (val&def)>0 )
                act = act->goRight();
            else
                act = act->goLeft();
        }
        return act->cnt;
    }
    void update(Trie* act,int pos,int val){
        for (int actLog = logg;actLog>=0;actLog--){
            int def = 1<<actLog;
            act->cnt += val;
            if ( (pos&def)>0 )
                act = act->goRight();
            else
                act = act->goLeft();
        }
        act->cnt += val;
    }
} TrieManager ;

Trie* White[maxN<<2];
Trie* Black[maxN<<2];
vector<Trie*> qNodes;
class myTree{
    public:
        void init(int _n){
            n = _n;
            makeTree(1,1,n);
        }
        void Update_Type_One(int child,int type,int color,int howMany){
            _tip = type; _color = color; _howMany = howMany;
            update(1,1,n,child);
        }
        void Update_Type_Two(int child,int type){
            int node = getId(1,1,n,child);
            int countWhite = TrieManager.getCount(White[node],type);
            int countBlack = TrieManager.getCount(Black[node],type);

            _tip = type; _color = 0; _howMany = -countWhite;
            update(1,1,n,child);
            _tip = type; _color = 0; _howMany = +countBlack;
            update(1,1,n,child);

            _tip = type; _color = 1; _howMany = -countBlack;
            update(1,1,n,child);
            _tip = type; _color = 1; _howMany = +countWhite;
            update(1,1,n,child);
        }
        int  Query(int l,int r,int color,int k){
            qNodes.clear();  _color = color;
            query(1,1,n,l,r);

            return getValueOnPosition(k);
        }

    private:
        int n;
        int _color,_tip,_howMany;

        void makeTree(int node,int l,int r){
            White[node] = new Trie();
            Black[node] = new Trie();
            if (l==r) return;

            int mid = (l+r)>>1;
            makeTree(lSon,l,mid);
            makeTree(rSon,mid+1,r);
        }

        void update(int node,int l,int r,int pos){
            if (_color == 0)
                TrieManager.update(White[node],_tip,_howMany);
            else
                TrieManager.update(Black[node],_tip,_howMany);

            if (l==r) return;
            int mid = (l+r)>>1;
            if (pos<=mid)
                update(lSon,l,mid,pos);
            else
                update(rSon,mid+1,r,pos);
        }

        int getId(int node,int l,int r,int pos){
            if (l==r) return node;

            int mid = (l+r)>>1;
            if (pos<=mid)
                return getId(lSon,l,mid,pos);
            else
                return getId(rSon,mid+1,r,pos);
        }

        void query(int node,int l,int r,int qL,int qR){
            if (qL<=l&&r<=qR) {
                if (_color==0)
                    qNodes.pb( White[node] );
                else
                    qNodes.pb( Black[node] );
                return;
            }

            int mid = (l+r)>>1;
            if (qL<=mid)
                query(lSon,l,mid,qL,qR);
            if (qR> mid)
                query(rSon,mid+1,r,qL,qR);
        }

        int getValueOnPosition(int k){
            int ans = 0;
            for (int actLog = logg;actLog>=0;actLog--){
                int howMany_left = 0;
                int def = 1<<actLog;

                Trie* aux;
                for (auto e:qNodes){
                    aux = e->goLeft();
                    howMany_left += aux->cnt;
                }

                if (k<=howMany_left){
                    for (int i=0;i<qNodes.size();i++){
                        qNodes[i] = qNodes[i]->goLeft();
                    }
                } else {
                    k -= howMany_left;
                    for (int i=0;i<qNodes.size();i++){
                        qNodes[i] = qNodes[i]->goRight();
                    }
                    ans |= def;
                }

                for (int i=0;i<qNodes.size();i++){
                    if (qNodes[i]->cnt!=0) continue;
                    qNodes[i] = qNodes[ qNodes.size()-1 ];
                    qNodes.pop_back(); i--;
                }
            }

            return ans;
        }
};


int n,m,t,i,op;
myTree aint;

int child_,howMany_,type_,color_;
int a_,b_;

int main()
{
    freopen("kinder.in","r",stdin);
    freopen("kinder.out","w",stdout);

    scanf("%d%d%d",&n,&m,&t);
    aint.init(n);

    for (;t--;){
        scanf("%d",&op);
        if (op==1) {
            scanf("%d%d%d%d",&child_,&type_,&color_,&howMany_);
            aint.Update_Type_One(child_,type_,color_,howMany_);
        } else
        if (op==2) {
            scanf("%d%d",&child_,&type_);
            aint.Update_Type_Two(child_,type_);
        } else {
            scanf("%d%d%d%d",&a_,&b_,&color_,&howMany_);
            printf("%d\n",aint.Query(a_,b_,color_,howMany_));
        }
    }


    return 0;
}

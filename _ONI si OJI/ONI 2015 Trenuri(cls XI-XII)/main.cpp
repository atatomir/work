#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

#define maxN 100011
#define lSon (node<<1)
#define rSon (lSon|1)

class Aint{
    private:
        int *R;      //! containerul
        int *lR;    //! container pt lazy
        int n;     //! dimensiunea
        int *tmp; //! vectorul initial

        void lazy(int node){
            if(lR[node]==0) return;

            lR[lSon] += lR[node]; R[lSon] -= lR[node];
            lR[rSon] += lR[node]; R[rSon] -= lR[node];
            lR[node] = 0;
        }
        void makeTree(int node,int l,int r){
            if(l==r){
                R[node] = tmp[l];
                return;
            }

            int mid = (l+r)>>1;
            makeTree(lSon,l,mid);
            makeTree(rSon,mid+1,r);

            R[node] = min(R[lSon],R[rSon]);
        }
        int _query(int node,int l,int r,int qL,int qR){
            if(l!=r) lazy(node);
            if(qL<=l&&r<=qR) return R[node];

            int ans = (1<<30);

            int mid = (l+r)>>1;
            if(qL<=mid) ans = min(ans, _query(lSon,l,mid,qL,qR) );
            if(qR> mid) ans = min(ans, _query(rSon,mid+1,r,qL,qR) );

            return ans;
        }
        void _update(int node,int l,int r,int qL,int qR){
            if(l!=r) lazy(node);
            if(qL<=l&&r<=qR) { R[node]--; lR[node]++;return;}

            int mid = (l+r)>>1;
            if(qL<=mid) _update(lSon,l,mid,qL,qR) ;
            if(qR> mid) _update(rSon,mid+1,r,qL,qR) ;

            R[node] = min(R[lSon],R[rSon]);
        }

    public:
        void init(int _n,int *_R,int *_lR,int *_tmp){
            n = _n; R = _R; lR = _lR; tmp = _tmp;
            makeTree(1,1,n);
        }
        int isGood(int l,int r){
            return _query(1,1,n,l,r) > 0;
        }
        void setIntr(int l,int r){
            _update(1,1,n,l,r);
        }

        //! for debug
        void show(int node,int l,int r){
            if(l!=r)lazy(node);
            cerr << l << ' ' << r << ' ' << R[node] << '\n';
            if(l==r) return;
            int mid = (l+r)>>1;
            show(lSon,l,mid);
            show(rSon,mid+1,r);
        }
};

struct Train{
    int dist,c,id;
    void read(int idd){ scanf("%d%d",&dist,&c); id = idd; }

    Train(){}
    Train(int _dist,int _c,int _id){
        dist = _dist; c = _c; id = _id;
    }
};
struct Person{
    int st,en,id;
    void read(int idd){ scanf("%d%d",&st,&en); id = idd; }

    bool operator<(const Person& who)const{
        return en < who.en;
    }
};
struct hcmp{
    bool operator()(const Train& a,const Train& b)const{
        return a.dist < b.dist;
    }
};

int n,m,i;
Train Tr[maxN];
Person Pr[maxN];
int list[maxN<<1],cnt,vaj;
int vals[maxN<<1];
int sol[maxN];

vector<int> ans;
priority_queue< Train,vector<Train>,hcmp > H;

//! just for aint
    Aint aint;
    int aContainer[maxN<<3];
    int alContainer[maxN<<3];
//! -------------

int cb(int x){
    int l=1,r=cnt,mid;
    while(l<=r){
        mid = (l+r)>>1;
        if( x < list[mid] )
            r = mid-1;
        else
            l = mid+1;
    }
    return r;
}

bool cmp(const int a,const int b){
    return Pr[a].en > Pr[b].en;
}

int main()
{
    freopen("trenuri3.in","r",stdin);
    freopen("trenuri3.out","w",stdout);

    scanf("%d %d",&n,&m);
    for(i=1;i<=n;i++) Tr[i].read(i);
    for(i=1;i<=m;i++){
        Pr[i].read(i);
        list[ ++cnt ] = Pr[i].st;
        list[ ++cnt ] = Pr[i].en;
    }

    //! -------------------
        sort(list+1,list+cnt+1);
        vaj = 1;
        for(i=2;i<=cnt;i++)
            if(list[i]!=list[i-1]) list[++vaj] = list[i];
        cnt = vaj;
    //! -------------------

    for(i=1;i<=n;i++){
        int pos = cb(Tr[i].dist);
        if(Tr[i].c > 100000) Tr[i].c = 100000;
        vals[pos] += Tr[i].c;
    }
    for(i=cnt;i;i--){
        vals[i] += vals[i+1];
        if(vals[i] > 100000) vals[i] = 100000;
    }

    aint.init(cnt,aContainer,alContainer,vals);
    sort(Pr+1,Pr+m+1);

    for(i=1;i<=m;i++){
        Person act = Pr[i];
        //if(Pr[i].st == Pr[i].en+1) { ans.push_back(i); continue; }
        int pos1 = cb(Pr[i].st);
        int pos2 = cb(Pr[i].en);

        if(!aint.isGood( pos1+1,pos2 )) continue;
        ans.push_back(i);
        aint.setIntr( pos1+1, pos2 );

        //aint.show(1,1,cnt);
        //cerr << '\n';
    }

    printf("%d\n",ans.size());
    sort(ans.begin(),ans.end(),cmp);

    for(i=1;i<=n;i++) H.push( Tr[i] );
    for(i=0;i<ans.size();i++){
        Person act = Pr[ans[i]];
        Train actTr = H.top(); H.pop();

        sol[ act.id ] = actTr.id;
        H.push( Train(act.st,1,actTr.id) );
        if(actTr.c>1) H.push( Train(actTr.dist,actTr.c-1,actTr.id) );
    }

    for(i=1;i<=m;i++) printf("%d\n",sol[i]);

    return 0;
}

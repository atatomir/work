#include <iostream>
#include <cstdio>

using namespace std;

#define DEBUG

long cnt=0;

struct Node{
    Node *lSon,*rSon;
    long long en,best,how;
    bool flag;

    Node(){ cnt++;
        lSon = rSon = NULL;
        en = best = how = 0;
        flag = false;
    }
    Node(long long v,long l,long r){ cnt++;
        lSon = rSon = NULL;
        how = v;
        en = 1LL*(r-l+1)*v;
        best = max(how,en);
        flag = false;
    }

    void update(){
        if(!lSon) return;
        how = -1;
        en = lSon->en + rSon->en;
        best = max(lSon->best,lSon->en+rSon->best);
    }

    void needExpand(long l,long r){
        if(l==r) return;
        if(lSon) return;
        long m = (l+r)>>1;
        lSon = new Node(how , l  , m);
        rSon = new Node(how , m+1, r);
    }
    void beLazy(long l,long r){
        needExpand(l,r);
        if(!flag) return;
        flag = false;
        if(l==r) return;

        long m=(l+r)>>1;
        lSon->how = how;
        lSon->en  = (m-l+1)*how;
        lSon->best = max(how,lSon->en);
        lSon->flag = true;

        rSon->how = how;
        rSon->en  = (r-m)*how;
        rSon->best = max(how,rSon->en);
        rSon->flag = true;
    }
};

long n,i;
char ch;
long a,b;
long long h;

Node *R;

void aintUpdate(Node* &act,long l,long r,long qL,long qR){
    act->beLazy(l,r);
    if(qL<=l && r<=qR){
        Node* tmp = new Node(h,l,r);

        act->en = tmp->en;
        act->best = tmp->best;
        act->how = tmp->how;
        act->flag = true;

        delete tmp; cnt--;

        return ;
    }

    long m = (l+r)>>1;
    if(qL<=m) aintUpdate(act->lSon,l,m,qL,qR);
    if(qR> m) aintUpdate(act->rSon,m+1,r,qL,qR);

    act->update();
}

long aintQuery(Node* &act,long l,long r){
    act->beLazy(l,r);

    if(h >= act->best) return r;
    if(act->lSon == NULL) return l-1;
    if(h >= act->lSon->best) {
        h -= act->lSon->en;
        return aintQuery(act->rSon, ((l+r)>>1)+1,r );
    }
    return aintQuery(act->lSon,l,(l+r)>>1);

}

int main()
{
    #ifdef DEBUG
        freopen("test.in","r",stdin);
    #endif // DEBUG

    R = new Node();
    scanf("%ld\n",&n);
    while(true){
        scanf("%c",&ch);
        if(ch == 'E') {
            #ifdef DEBUG
                cerr << "\n" << cnt;
            #endif // DEBUG
            return 0;
        }
        if(ch=='I'){
            scanf("%ld %ld %lld\n",&a,&b,&h);
            aintUpdate(R,1,n,a,b);
        }else{
            scanf("%lld\n",&h);
            printf("%ld\n", aintQuery(R,1,n) );
        }
    }

    return 0;
}

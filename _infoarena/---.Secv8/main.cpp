#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstdlib>

using namespace std;

#define mod 666013

struct Treap{
    Treap *lSon,*rSon;
    long key,pr;
    long cnt;
    bool rev;


    Treap(){}
    Treap(Treap* _lSon,Treap* _rSon,long _key,long _pr){
        lSon = _lSon;
        rSon = _rSon;
        key = _key; pr = _pr;
        cnt = 1; rev = false;
    }
}*root,*nil;

void lazyDeep(Treap *t){
    if(t==nil) return;
    if(t->rev){
        t->rev = false;
        swap(t->lSon,t->rSon);
        t -> lSon -> rev ^= true;
        t -> rSon -> rev ^= true;
    }
}
void reLoad(Treap* t){
    if(t==nil) t->cnt=0; else
    t->cnt = t->lSon->cnt+t->rSon->cnt+1;
}
void rotLeft(Treap* &t){
    Treap* aux = t->lSon;
    t -> lSon = aux->rSon; aux->rSon = t;
    t = aux;

    reLoad(t);
    reLoad(t->lSon); reLoad(t->rSon);
}
void rotRight(Treap* &t){
    Treap* aux = t->rSon;
    t -> rSon = aux->lSon; aux->lSon = t;
    t = aux;

    reLoad(t);
    reLoad(t->lSon); reLoad(t->rSon);
}
void balance(Treap* &t){
    lazyDeep(t);
    lazyDeep(t->lSon);lazyDeep(t->rSon);

    if(t->pr < t->lSon->pr) rotLeft(t);
    else
    if(t->pr < t->rSon->pr) rotRight(t);
}

void insert(Treap* &t,long pos,long key,long pr){
    lazyDeep(t);

    if(t == nil){
        t = new Treap(nil,nil,key,pr);
        return;
    }

    long v = t->lSon->cnt+1;
    if(pos<=v) insert(t->lSon,pos,key,pr);
    else       insert(t->rSon,pos-v,key,pr);

    balance(t);
    reLoad(t);
}
void remove(Treap* &t,long pos){
    lazyDeep(t);
    lazyDeep(t->lSon); lazyDeep(t->rSon);
    //cerr <<" go to remove " << t->key << "  " << pos << '\n';

    long lft = t->lSon->cnt+1;
    if(pos==lft && t->lSon == nil && t->rSon == nil){
        delete t;
        t = nil;
        return;
    }

    if(pos==lft){
        if(t->lSon->pr < t->rSon->pr) rotRight(t);
        else                          rotLeft(t);

        remove(t,pos);
    }else
    if(pos<lft) remove(t->lSon,pos);
    else        remove(t->rSon,pos-lft);

    reLoad(t);
}
long acces(Treap* t,long pos){
    lazyDeep(t);

    long lft = t->lSon->cnt+1;
    if(pos==lft) return t->key;
    if(pos<lft) return acces(t->lSon,pos);
    else        return acces(t->rSon,pos-lft);
}
void Print(Treap *t){
    lazyDeep(t);

    if(t==nil) return;
    Print(t->lSon);
    printf("%ld ",t->key); //cerr << t->key << ' ';
    Print(t->rSon);
}
void split(Treap* &R,Treap* &R1,Treap* &R2,long pos){
    insert(R,pos+1,-1,1<<20);
    R1 = R->lSon; R2 = R->rSon;
    delete R;
}
void join(Treap* &R,Treap* R1,Treap* R2){
    R = new Treap(R1,R2,-3,1<<20);
    reLoad(R);
    remove(R,R1->cnt+1);
}

long n,inutil,i,k,e,l,r;
char c;

int main()
{
    freopen("secv8.in","r",stdin);
    freopen("secv8.out","w",stdout);

    srand(time(NULL));
    nil = new Treap(NULL,NULL,-2,-1); nil->cnt=0;
    root = nil;

    scanf("%ld %ld\n",&n,&inutil);
    for(;n--;){
        scanf("%c ",&c);
        if(c=='I'){
            scanf("%ld %ld\n",&k,&e);
            insert(root,k,e,rand()%mod);
        }
        if(c=='A'){
            scanf("%ld\n",&k);
            printf("%ld\n" , acces(root,k) );
            //cerr << "!!" <<  acces(root,k) << '\n';
        }
        if(c=='R'){
            scanf("%ld %ld\n",&l,&r);
            Treap *t1,*tt,*t2,*t3;
            split(root,t1,tt,l-1);
            split(tt,t2,t3,r-l+1);
            t2->rev = true;

            join(tt,t1,t2);
            join(root,tt,t3);
        }
        if(c=='D'){
            scanf("%ld %ld\n",&l,&r);
            Treap *t1,*tt,*t2,*t3;
            split(root,t1,tt,l-1);
            split(tt,t2,t3,r-l+1);

            join(root,t1,t3);
        }

        //cerr << "op " << c << "  finished\n";
        //Print(root); cerr << '\n';
    }

    Print(root);

    return 0;
}

#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstdio>

using namespace std;

#define mod 666013

struct Treap{
    Treap *lSon,*rSon;
    long key,pr;

    Treap(Treap * _l,Treap* _r,long _key,long _pr){
        lSon = _l; rSon = _r;
        key = _key; pr = _pr;
    }
};

long n,i,op,x;
Treap *nil,*root;

void rotLeft(Treap* &node){
    Treap *t = node -> lSon;
    node -> lSon = t -> rSon; t -> rSon = node;
    node = t;
}

void rotRight(Treap* &node){
    Treap *t = node -> rSon;
    node -> rSon = t -> lSon; t -> lSon = node;
    node = t;
}

void balance(Treap* &node){
    if( node->pr < node->lSon->pr ) rotLeft(node); else
    if( node->pr < node->rSon->pr ) rotRight(node);
}

void insert(Treap* &n,long key){
    if(n == nil) {
        n = new Treap(nil,nil,key,rand()%mod);
        return ;
    }

    if(key < n->key)
        insert(n->lSon,key);
    if(key > n->key)
        insert(n->rSon,key);

    balance(n);
}

void remove(Treap* &n,long key){
    if(n == nil) return;
    if(n->lSon == nil && n->rSon == nil && key == n->key){
        delete n;
        n = nil;
        return ;
    }

    if(key < n->key)
        remove(n->lSon,key);
    if(key > n->key)
        remove(n->rSon,key);
    if(key == n->key){
        if(n->lSon->pr > n->rSon->pr) rotLeft(n); else rotRight(n);
        remove(n,key);
    }
}

bool count(Treap *n,long key){
    if(n == nil) return false;
    if(n -> key == key) return true;

    if(key < n -> key) return count(n->lSon,key);
    else               return count(n->rSon,key);
}

void afis(Treap* n){
    if(n==nil) return;
    afis(n->lSon);
    printf("%ld ",n->key);
    afis(n->rSon);
}

int main()
{
    freopen("hashuri.in","r",stdin);
    freopen("hashuri.out","w",stdout);
    srand(time(NULL));

    nil = new Treap(NULL,NULL,0,-1);
    root = nil;

    scanf("%ld",&n);
    for(;n--;){
        scanf("%ld%ld",&op,&x);
        if(op==1) insert(root,x);
        if(op==2) remove(root,x);
        if(op==3) printf("%ld\n", (count(root,x)?1:0) );

        //afis(root); printf("\n");
    }

    return 0;
}

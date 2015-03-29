#include <iostream>
#include <cstdio>

using namespace std;

#define mBit 20

long Best=-1,iBest,jBest;

struct Trie{
    long sour;
    Trie *child[2];

    Trie(){
        sour = 0;
        child[0] = child[1] = NULL;
    }

    void Add(long val,long ssour){
        Trie *act = this;
        for(long Bit=1<<mBit;Bit;Bit>>=1){
            long dest = val & Bit;
            if(dest) dest = 1;

            if(act->child[dest] == NULL) act->child[dest] = new Trie();
            act = act->child[dest];
        }
        act->sour = ssour;
    }
    void Check(long val,long fPos){
        Trie *act = this;
        for(long Bit=1<<mBit;Bit;Bit>>=1){
            long dest = val & Bit;
            if(dest) dest = 1; dest ^= 1;

            if(act->child[dest] == NULL) dest ^= 1;
            act = act->child[dest];

            val ^= Bit*dest;
        }

        if(val > Best){
            Best = val;
            iBest = act -> sour;
            jBest = fPos;
        }
    }
};

long n,i,x;
long xorAct;
Trie *myTrie;

int main()
{
    freopen("xormax.in","r",stdin);
    freopen("xormax.out","w",stdout);

    myTrie = new Trie();
    myTrie->Add(0,0);

    scanf("%ld",&n);
    for(i=1;i<=n;i++){
        scanf("%ld",&x);
        xorAct ^= x;

        myTrie->Check(xorAct,i);
        myTrie->Add(xorAct,i);
    }

    printf("%ld %ld %ld",Best,iBest+1,jBest);

    return 0;
}

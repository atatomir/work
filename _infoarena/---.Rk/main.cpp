#include <iostream>
#include <cstdio>

using namespace std;

struct Trie{
    long cnt;
    Trie *lSon,*rSon;

    Trie(){
        cnt = 0;
        lSon = rSon = NULL;
    }
};

#define defBit 33

long n,q,i,x,bit,r,k,ans;
Trie* Head;
Trie* act;

//#define maxN 200011
//long v[maxN];

int main()
{
    freopen("rk.in","r",stdin);
    freopen("rk.out","w",stdout);

    Head = new Trie();
    scanf("%ld",&n);
    for(i=1;i<=n;i++){
        scanf("%ld",&x);

            //v[i] = x;

        act = Head;
        for(bit = 1;bit<=defBit;bit++,x>>=1){
            if(x&1){ //! 1
                if(act->rSon == NULL) act->rSon = new Trie();
                act = act->rSon;
                act->cnt++;
            } else { //! 0
                if(act->lSon == NULL) act->lSon = new Trie();
                act = act->lSon;
                act->cnt++;
            }
        }
    }

    scanf("%ld",&q);
    for(;q--;){
        scanf("%ld %ld",&r,&k); //long rr = r;

        if(k==0){
            printf("%ld\n",n);
            continue;
        }

        act = Head;
        for(bit = 1;bit<=k;bit++,r>>=1){
            if(r&1){  //! 1
                if(act->rSon == NULL) {ans = 0; break;}
                act = act->rSon;
            } else {  //! 0
                if(act->lSon == NULL) {ans = 0; break;}
                act = act->lSon;
            }

            ans = act->cnt;
        }

        /*long cc = 0;
        for(i=1;i<=n;i++)
            if(v[i] % (1<<k) == rr) cc++;*/

        printf("%ld\n",ans);
    }

    return 0;
}

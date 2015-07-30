#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

#define let 26
struct Trie{
    Trie* son[26];
    Trie(){
        static long i;
        for(i=0;i<let;i++) son[i] = NULL;
    }

    Trie* goFor(char c){
        long id = c-'a';
        if(son[id]==NULL) son[id] = new Trie();
        return son[id];
    }
};

#define dimMax 2015
#define maxN 10024

long n,m,i,j,len,k,p;
Trie* Head;

char s[dimMax];
vector<Trie*> wh[maxN];
long id[20];

bool Equal(long pos){
    Trie* cmp = wh[ id[1] ][pos];

    for(long i=2;i<=k;i++)
        if(wh[ id[i] ][pos] != cmp) return false;

    return true;
}

int main()
{
    freopen("ratina.in","r",stdin);
    freopen("ratina.out","w",stdout);

    scanf("%ld %ld",&n,&m);
    Head = new Trie();

    for(i=1;i<=n;i++){
        memset(s,0,sizeof(s));
        scanf("%s\n",s+1);
        len = strlen(s+1);

        wh[i].resize(len);

        Trie* act = Head;
        for(j=1;j<=len;j++){
            act = act->goFor(s[j]);
            wh[i][j-1] = act;
        }
    }

    for(;m--;){
        scanf("%ld",&k);

        i = 0; j = dimMax;
        for(p=1;p<=k;p++) {
            scanf("%ld",&id[p]);
            j = min(j,(long)wh[ id[p] ].size()-1);
        }

        while(i<=j){
            long mid = (i+j)>>1;
            if( Equal(mid) )
                i = mid+1;
            else
                j = mid-1;
        }

        printf("%ld\n",j+1);
    }

    return 0;
}

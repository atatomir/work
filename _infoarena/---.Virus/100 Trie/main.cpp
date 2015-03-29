#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

#define maxL 100011
#define maxK 1011

long l,n,k,i,j,q;
char s[maxL],d[maxK];

struct myTrie{
    public:
        vector<long> id;

        myTrie(){
            Son[0]=Son[1] = NULL;
            id.clear();
        }
        void add(char *s){
            myTrie *tmp = this;
            for(long i=1;i<=k;i++){
                long dir = s[i]-'0';
                if(tmp->Son[dir] == NULL) tmp->Son[dir] = new myTrie();
                tmp = tmp->Son[dir];
            }
            tmp->id.push_back(++q);
        }
        myTrie* next(long dir){
            return this->Son[dir];
        }

    private:
        myTrie* Son[2];
};

myTrie* Trie;
myTrie* list[maxL];
long cnt,tmp;
long ans[1011];

int main()
{
    freopen("virus.in","r",stdin);
    freopen("virus.out","w",stdout);

    Trie = new myTrie();

    scanf("%ld%ld\n%s\n",&l,&n,s+1);
    for(i=1;i<=n;i++){
        scanf("%ld\n%s\n",&k,d+1);
        Trie->add(d);
    }

    myTrie *act;
    for(i=1;i<=l;i++){
        list[++cnt] = Trie; tmp = cnt; cnt = 0;
        for(j=1;j<=tmp;j++){
            act = list[j]->next(s[i]-'0');
            if(act != NULL){
                list[++cnt] = act;
                for(long tt = 0;tt<act->id.size();tt++)
                    ans[act->id[tt]]++;
            }
        }
    }

    for(i=1;i<=n;i++){
        printf("%ld\n",ans[i]);
    }

    return 0;
}

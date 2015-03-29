#include <iostream>
#include <cstdio>
#include <map>
#include <vector>

using namespace std;

#define maxS 100011

char s[maxS];
long n,i;
long long ant;

struct myTrie{
    vector<pair<long,myTrie*> > Child;
    long start,stop;

    inline long getId(char c){
        if(c <= 'Z') return c-'A';
        return c-'a' + 26;
    }
    myTrie(){
        Child.clear();
    }

    long long setW(long pos){
        long long Ans=0;

        myTrie *tmp = this;
        while(pos){
            long id = getId(s[pos]);

            long found = -1;
            for(long i=0;i<tmp->Child.size();i++){
                if(tmp->Child[i].first == id)
                    found = i;
            }

            if(found == -1){
                myTrie* newTrie = new myTrie();
                newTrie->start = 1; newTrie->stop = pos;
                tmp->Child.push_back(make_pair(id,newTrie));
                Ans = Ans + pos; pos = 0;
            } else {
                long common = pos;
                long tStop = tmp->Child[found].second->stop;
                while(tStop >= tmp->Child[found].second->start && s[common] == s[tStop]){
                    common--; tStop--;
                }
                if(tStop < tmp->Child[found].second->start){
                    tmp = tmp->Child[found].second;
                    pos -= tmp->stop-tmp->start+1;
                } else {
                    myTrie *last = tmp->Child[found].second;

                    tmp->Child[found].second = new myTrie();
                    tmp->Child[found].second->start = tStop+1;
                    tmp->Child[found].second->stop  = last->stop;

                    last->stop = tStop;

                    tmp->Child[found].second->Child.push_back(make_pair(getId(s[last->stop]),last));

                    myTrie* newTrie = new myTrie();
                    newTrie->start = 1; newTrie->stop = common;
                    tmp->Child[found].second->Child.push_back(make_pair(getId(s[common]),newTrie));
                    Ans = Ans + common; pos = 0;
                }

            }

        }

        return Ans;
    }
};

myTrie *Trie;

int main()
{
    freopen("prefix2.in","r",stdin);
    freopen("prefix2.out","w",stdout);

    Trie = new myTrie();
    scanf("%s",s+1);

    ant = 0; i = 1;
    while(s[i] != '\0'){
        ant += Trie->setW(i);
        if(ant > 2000000000)
            printf("%lld\n",ant);
        else
            printf("%ld\n",(long)ant);
        i++;
    }

    return 0;
}

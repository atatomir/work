#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define maxSize 25

struct Trie{
    long ap,apT;
    Trie* child[26];

    Trie(){
        ap = apT = 0;
        for(long i=0;i<26;i++) child[i] = NULL;
    }

    void Change(char s[maxSize],long val){
        Trie *act = this;
        for(long i=0;i<strlen(s);i++){
            long dir = s[i] - 'a';
            if(act->child[dir] == NULL) act->child[dir] = new Trie();
            act = act->child[dir];
            act->apT += val;
        }
        act->ap += val;
    }
    long Count(char s[maxSize]){
        Trie *act = this;
        for(long i=0;i<strlen(s);i++){
            long dir = s[i] - 'a';
            if(act->child[dir] == NULL) return 0;
            act = act->child[dir];
        }
        return act->ap;
    }
    long Check(char s[maxSize]){
        Trie *act = this;
        for(long i=0;i<strlen(s);i++){
            long dir = s[i] - 'a';
            if(act->child[dir] == NULL) return i;
            act = act->child[dir];
            if(act->apT == 0) return i;
        }
        return strlen(s);
    }

};

long op;
char s[maxSize];
Trie *myTrie;

int main()
{
    freopen("trie.in","r",stdin);
    freopen("trie.out","w",stdout);

    myTrie = new Trie();

    while(!feof(stdin)){
        scanf("%ld %s\n",&op,s);
        switch(op){
            case 0 : myTrie->Change(s,1); break;
            case 1 : myTrie->Change(s,-1); break;
            case 2 : printf("%ld\n",myTrie->Count(s)); break;
            case 3 : printf("%ld\n",myTrie->Check(s)); break;
        }
    }

    return 0;
}

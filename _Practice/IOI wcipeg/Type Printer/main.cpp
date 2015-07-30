#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

//#define DEBUG
#define maxN 25011
#define maxL 25

long cnt=-1;

struct Node{
    Node* son[26];
    bool flag;
    long pp;

    Node(){ for(long i=0;i<26;i++) son[i]=NULL; cnt++; flag = false; pp=0;}
    Node* goFor(char c){
        long dir = c-'a';
        if(!son[dir]) son[dir] = new Node();
        return son[dir];
    }
};

long n,i,dim,maxx,nn;
char s[maxL];
char who[maxL];
Node* R,*act;

void printIt(Node* act){
    long i;

    for(i=0;i<26;i++){
        if(!act->son[i]) continue;
        if(act->son[i]->flag) continue;

        printf("%c\n",i+'a');
        printIt(act->son[i]);
        printf("-\n");

        delete act->son[i];
        act->son[i]=NULL;
    }

    while(act->pp--) printf("P\n");

    for(i=0;i<26;i++){
        if(!act->son[i]) continue;

        printf("%c\n",i+'a');
        printIt(act->son[i]);

        return;
    }
}

int main()
{
    #ifdef DEBUG
        freopen("test.in","r",stdin);
    #endif // DEBUG

    R = new Node();
    scanf("%ld\n",&n); nn=n;
    for(;n--;){
        memset(s,0,sizeof(s));
        scanf("%s\n",s+1);

        dim = strlen(s+1); act = R;
        if(maxx < dim){
            maxx = dim;
            for(i=1;i<=maxx;i++) who[i] = s[i];
        }
        for(i=1;i<=dim;i++) act = act->goFor(s[i]);
        act->pp++;
    }

    act = R;
    for(i=1;i<=maxx;i++){
        act = act->goFor(who[i]);
        act->flag = true;
    }

    printf("%ld\n", 2*cnt+nn-maxx );
    printIt(R);

    return 0;
}

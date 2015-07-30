#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

//#define DEBUG
#define maxN (1<<20)
#define PI pair<long,long>
#define mp make_pair
#define id first
#define qPos second

struct Node{
    char ch;
    vector< PI > Q;
    vector<long> son;

    void init(){
        ch = '@';
        Q.clear(); son.clear();
    }
};

long n,i,x,qq,cnt,pos;
char ch;
Node Tree[maxN];
long wh[maxN],act;
char ans[maxN],tt[maxN];

void dfs(long node){
    long i;
    if(node)tt[++pos] = Tree[node].ch;

    for(i=0;i<Tree[node].Q.size();i++){
        PI act = Tree[node].Q[i];
        ans[ act.id ] = tt[ act.qPos+1 ];
    }
    for(i=0;i<Tree[node].son.size();i++){
        long newNode = Tree[node].son[i];
        dfs(newNode);
    }

    pos--;
}

int main()
{
    #ifdef DEBUG
        freopen("test.in","r",stdin);
    #endif // DEBUG

    scanf("%ld\n",&n);
    for(i=1;i<=n;i++) Tree[i].init();

    wh[0] = act = pos = cnt = 0;
    for(i=1;i<=n;i++){
        scanf("%c ",&ch);
        if(ch=='T'){ //! varaja Type
            scanf("%c\n",&ch);
            Tree[++cnt].ch = ch;
            Tree[  act].son.push_back(cnt);
            act = cnt;
        }else
        if(ch=='U'){ //! varaja Undo
            scanf("%ld\n",&x);
            act = wh[pos-x];
        }else{ //! varaja Print
            scanf("%ld\n",&x);
            Tree[act].Q.push_back( mp(++qq,x) );
            continue;
        }

        wh[++pos] = act;
    }

    pos=0;
    dfs(0);
    for(i=1;i<=qq;i++) printf("%c\n",ans[i]);

    return 0;
}

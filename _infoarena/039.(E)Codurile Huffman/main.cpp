#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

typedef pair<long long,pair<long,long> > MyNod ;

#define maxN 1000010
#define maxBuf 1000000
#define v first
#define n1 second.first
#define n2 second.second

long n,i,k,nn;
MyNod nodes[maxN << 1];
queue<long> iQ,Q;

long leng[maxN];
long long Ans,codes[maxN];

long pos;
char Buff[maxBuf];


inline bool isDigit(char c){
    return c >= '0' && c <= '9';
}
long long getLong(){
    while(!isDigit(Buff[pos])){
        pos++;
        if(pos == maxBuf){
            pos = 0;
            fread(Buff,1,maxBuf,stdin);
        }
    }
    long long Ans=0;
    while(isDigit(Buff[pos])){
        Ans = Ans*10 + Buff[pos++] - '0';
        if(pos == maxBuf){
            pos = 0;
            fread(Buff,1,maxBuf,stdin);
        }
    }
    return Ans;
}

void DFS(long pos,long long cod,long level){
    if(pos <= nn){
        leng[pos] = level;
        codes[pos] = cod;
        Ans += nodes[pos].v * level;
        return;
    }
    DFS(nodes[pos].n1,cod*2,level+1);
    DFS(nodes[pos].n2,cod*2+1,level+1);
}

void solve(){
    long i,j,nod[2];
    bool second;

    while(n > 1){
        k++; n--;
        for(i=0;i<2;i++){
            second = false;
            if(!iQ.empty()) nod[i] = iQ.front(); else nod[i] = 0;
            if(!Q.empty()) {
                if(nod[i] == 0 || nodes[Q.front()].v < nodes[nod[i]].v ) nod[i] = Q.front(),second=true;
            }

            if(!second) iQ.pop(); else Q.pop();
        }
        nodes[k].v = nodes[nod[0]].v + nodes[nod[1]].v;
        nodes[k].n1 = nod[0]; nodes[k].n2 = nod[1];
        Q.push(k);
    }

    DFS(k,0,0);
}

int main()
{
    freopen("huffman.in","r",stdin);
    freopen("huffman.out","w",stdout);
    fread(Buff,1,maxBuf,stdin);

    n = getLong(); k=n; nn=n;
    for(i=1;i<=n;i++){
        nodes[i].v = getLong();
        iQ.push(i);
    }

    solve();

    printf("%lld\n",Ans);
    for(i=1;i<=nn;i++) printf("%ld %lld\n",leng[i],codes[i]);

    return 0;
}

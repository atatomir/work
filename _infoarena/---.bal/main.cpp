//! Testele nu pun in valoare cazul in care apare acelasi bilet de la acelasi baiat de mai mult ori
//! sad :(


#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <set>

using namespace std;

class Buffer{
    public:
        long maxBuf,pos;
        vector<char> Buff;

        Buffer(char fileName[],long buffSize){
            freopen(fileName,"r",stdin);
            maxBuf = buffSize; Buff.resize(maxBuf);
            reFill();
        }

        Buffer& operator>>(long &dest){
            while(!isDigit(Buff[pos])){
                pos++;
                if(pos == maxBuf) reFill();
            }
            dest = 0;
            while(isDigit(Buff[pos])){
                dest = dest*10 + Buff[pos++] - '0';
                if(pos == maxBuf) reFill();
            }
            return *this;
        }
        Buffer& operator>>(long long &dest){
            while(!isDigit(Buff[pos])){
                pos++;
                if(pos == maxBuf) reFill();
            }
            dest = 0;
            while(isDigit(Buff[pos])){
                dest = dest*10 + Buff[pos++] - '0';
                if(pos == maxBuf) reFill();
            }
            return *this;
        }

    private:
        bool isDigit(char c){
            return c >= '0' & c <= '9';
        }
        void reFill(){
            fread(&Buff[0],1,maxBuf,stdin); pos = 0;
        }
};

#define mod 13013
class Hash{
    private :
        vector<long long> C[mod];

    public:
        Hash(){
            for(long i=0;i<mod;i++) C[i].clear();
        }
        bool alrdn(long long v){
            long id = v%mod;
            for(auto it = C[id].begin();it!=C[id].end();it++)
                if(*it == v) return true;
            return false;
        }
        void operator<<(long long v){
            long id = v%mod;
            C[id].push_back(v);
        }
};
void nope(){
    printf("NU\n");
    exit(0);
}
void dap(vector<long>& ans,long n){
    printf("DA\n");
    for(long i=1;i<=n;i++) printf("%ld\n",ans[i]);
    exit(0);
}

#define maxN 100011

long n,m,i;
//Hash H;
long long x,y;

long grL[maxN],grR[maxN];
vector<long> listL[maxN],listR[maxN];
queue<long> Q;
vector<long> l;

bool us[maxN<<1];

void rmvBoy(long node){
    for(auto it=listL[node].begin();it!=listL[node].end();it++){
        if(grR[*it]<0) continue;
        if(--grR[*it] == 1 && us[*it+n]==false) {Q.push(*it+n);us[*it+n]=true;}
    }
    grL[node] = -1;
}

void rmvGirl(long node){
    for(auto it=listR[node].begin();it!=listR[node].end();it++){
        if(grL[*it]<0) continue;
        if(--grL[*it] == 1 && us[*it]==false) {Q.push(*it);us[*it]=true;}
    }
    grR[node] = -1;
}

long who(long node){
    if(node<=n){ //! baietel
        for(auto it=listL[node].begin();it!=listL[node].end();it++)
            if(grR[*it]==0) nope();
            else if(grR[*it]>0) return *it;
    } else { //! fetita
        node -= n;
        for(auto it=listR[node].begin();it!=listR[node].end();it++)
            if(grL[*it]==0) nope();
            else if(grL[*it]>0) return *it;
    }
    return 0;
}

int main()
{
    Buffer fin("bal.in",1<<20);
    freopen("bal.out","w",stdout);

    //H = Hash();

    fin >> n >> m;
    for(;m--;){
        fin >> x >> y;
        long long vv = x*(1LL<<30)+y;
        //if(H.alrdn(vv)) continue;
        //H << vv;

        listL[x].push_back(y);
        listR[y].push_back(x);
        grL[x]++; grR[y]++;
    }

    for(i=1;i<=n;i++){
        if(grL[i]==0 || grR[i]==0) nope();
        if(grL[i]==1) Q.push(i);
        if(grR[i]==1) Q.push(i+n);
    }

    l.resize(n+11);
    while(!Q.empty()){
        long node = Q.front(); Q.pop();

        if(node<=n){ //! baietel dragutel
            if(grL[node]<0) continue;
            if(grL[node]==0) nope();

            long girl = who(node);
            rmvGirl(girl);
            rmvBoy(node);

            l[node] = girl;
        } else {  //! fetita cu fundita
            if(grR[node-n]<0) continue;
            if(grR[node-n]==0) nope();

            long boy = who(node);
            rmvBoy(boy);
            rmvGirl(node-n);

            l[boy]=node-n;
        }
    }

    for(i=1;i<=n;i++)
        if(!l[i]) nope();

    dap(l,n);

    return 0;
}

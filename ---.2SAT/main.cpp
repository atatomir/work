 #include <iostream>
#include <cstdio>
#include <stack>
#include <vector>

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
            while(!isDigit(Buff[pos]) && Buff[pos]!='-'){
                pos++;
                if(pos == maxBuf) reFill();
            }
            dest = 0; long sign = 1;
            if(Buff[pos] == '-'){
                sign = -1;
                if(++pos == maxBuf) reFill();
            }
            while(isDigit(Buff[pos])){
                dest = dest*10 + Buff[pos++] - '0';
                if(pos == maxBuf) reFill();
            }
            dest *= sign;
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

#define maxN 100011

long n,m,i,x,y,nn;
vector<long> list[maxN<<1],rev[maxN<<1];

bool vis[maxN<<1];
long ctc[maxN<<1],cnt;
vector<long> Comp[maxN<<1];
vector<long> tmp;

stack<long> S;
long col[maxN<<1];

inline void addDir(long a,long b){
    list[a+n].push_back(b+n);
    rev[b+n].push_back(a+n);
}

void dfsF(long nod){
    vis[nod] = true;
    for(long i=0;i<list[nod].size();i++){
        long newNod = list[nod][i];
        if(vis[newNod]) continue;
        dfsF(newNod);
    }
    S.push(nod);
}

void dfsB(long nod){
    ctc[nod] = cnt; tmp.push_back(nod);
    for(long i=0;i<rev[nod].size();i++){
        long newNod = rev[nod][i];
        if(ctc[newNod]) continue;
        dfsB(newNod);
    }
}

long searchCol(long act){
    long ans = 0;
    for(long i=0;i<Comp[act].size();i++){
        long nod = Comp[act][i];

        if(col[nod]){
            if(ans){
                if(ans != col[nod]) return -1;
            } else {
                ans = col[nod];
            }
        }
    }
    return ans;
}

bool tryCol(long act,long mCol){
    long inv;
    if(mCol == 1) inv = 2; else inv = 1;

    for(long i=0;i<Comp[act].size();i++){
        long nod = Comp[act][i];
        if(nod == nn) return true;

        col[nod] = mCol;
        long mNod = -(nod-nn)+nn;
        if(col[mNod] && col[mNod] == mCol) return false;
        col[mNod] = inv;

        if(mCol == 2){
            for(long j=0;j<list[nod].size();j++){
                long newNod = list[nod][j];
                if(col[newNod] == 1) return false;
                col[newNod] = 2;
            }
        }
    }
    return true;
}

int main()
{
    Buffer cin("2sat.in",1024*1024);
    freopen("2sat.out","w",stdout);

    cin >> n >> m;
    for(i=1;i<=m;i++){
        cin >> x >> y;
        addDir(-x,y);
        addDir(-y,x);
    } nn = n; n<<=1;

    for(i=1;i<=n;i++)
        if(!vis[i]) dfsF(i);

    cnt = 0;
    while(!S.empty()){
        long nod = S.top(); S.pop();
        if(ctc[nod]) continue;
        tmp.clear(); cnt++;
        dfsB(nod);
        Comp[cnt] = tmp;
    }

    for(i=1;i<=cnt;i++){
        long must = searchCol(i);
        if(must==-1){
            printf("-1");
            return 0;
        }
        if(must == 0) must = 1;

        if(!tryCol(i,must)){
            printf("-1");
            return 0;
        }
    }

    for(i=nn+1;i<=n;i++) printf("%ld ",col[i]-1);

    return 0;
}

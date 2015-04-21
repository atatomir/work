#include <iostream>
#include <cstdio>
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

#define maxN 100011
#define maxLog 22
#define myIteration(node) auto it=list[(node)].begin();it!=list[(node)].end();it++
#define cin fin

long n,m,i,x,l,r;
vector<long> list[maxN];
long wh[maxN];
vector<long> def,defH;
vector<long> rmq[maxLog],rmqH[maxLog];


void dfs(long node,long lvl){
    def.push_back(lvl); defH.push_back(node);  wh[node] = def.size()-1;
    for( myIteration(node) ){
        dfs(*it,lvl+1);
        def.push_back(lvl); defH.push_back(node);
    }
}

void make_rmq(){
    long i,j,actLog;
    long how=def.size();

    for(actLog=0;1<<(actLog+1) <= how;actLog++);

    for(i=0;i<=actLog;i++) rmq[i]  = vector<long>(how+10,0);
    for(i=0;i<=actLog;i++) rmqH[i] = vector<long>(how+10,0);
    for(i=1;i<=how;i++) {rmq[0][i] = def[i-1]; rmqH[0][i] = defH[i-1];}

    for(i=1;i<=actLog;i++){
        long h = 1<<(i-1);
        for(j=1;j+(h<<1) <= how+1 ;j++){
            if(rmq[i-1][j] < rmq[i-1][j+h])
                rmqH[i][j] = rmqH[i-1][j];
            else
                rmqH[i][j] = rmqH[i-1][j+h];
            rmq[i][j] = min(rmq[i-1][j],rmq[i-1][j+h]);
        }
    }
}

long getMax(long l,long r){
    if(l>r) swap(l,r); l++; r++;

    long how = r-l+1,actLog;
    for(actLog=0;1<<(actLog+1) <= how;actLog++);

    if(rmq[actLog][l] < rmq[actLog][r-(1<<actLog)+1])
        return rmqH[actLog][l];
    else
        return rmqH[actLog][r-(1<<actLog)+1];
}

int main()
{
    Buffer cin("lca.in",1024*1024);
    freopen("lca.out","w",stdout);

    cin >> n >> m;
    for(i=2;i<=n;i++){
        cin >> x;
        list[x].push_back(i);
    }

    dfs(1,1);
    make_rmq();

    for(;m--;){
        cin >> l >> r;
        printf("%ld\n",getMax(wh[l],wh[r]));
    }

    return 0;
}

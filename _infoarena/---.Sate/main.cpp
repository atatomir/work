#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

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

#define maxN 30011
#define dir first
#define cost second

long n,m,x,y,t,i,s,d,c;
vector<pair<long,long> > list[maxN];
long dp[maxN];
queue<long> Q;

int main()
{
    Buffer fin("sate.in",100000);
    freopen("sate.out","w",stdout);

    fin >> n >> m >> x >> y;
    for(i=1;i<=m;i++){
        fin >> s >> d >> c;
        list[s].push_back(make_pair(d,c));
        list[d].push_back(make_pair(s,-c));
    }

    if(x > y){t=x; x=y; y=t;}

    dp[x] = 1;
    Q.push(x);

    while(!Q.empty()){
        long node = Q.front(); Q.pop();

        if(node == y){
            printf("%ld",dp[y]-1);
            return 0;
        }

        for(long i=0;i<list[node].size();i++){
            long newNode = list[node][i].dir;
            if(!dp[newNode]) {
                dp[newNode] = dp[node] + list[node][i].cost;
                Q.push(newNode);
            }
        }
    }

    return 0;
}

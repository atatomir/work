#include <iostream>
#include <cstdio>
#include <vector>
#include <cstdio>
#include <algorithm>

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

#define x first
#define y second
#define maxN 100011
#define LIM 1000

typedef pair<long,long> Point;

long n,i,j;
vector<Point> G;
vector<Point> D[1011];

long par[maxN];
long ram[maxN];
long act;
long long cost;

long Find(long nod){
    long R = nod;
    while(par[R] != R) R = par[R];
    while(nod != R){
        long next = par[nod];
        par[nod] = R;
        nod = next;
    }
    return R;
}
void Merge(long R1,long R2){
    if(ram[R1] > ram[R2]){
        ram[R1]++;
        par[R2] = par[R1];
    } else {
        ram[R2]++;
        par[R1] = par[R2];
    }
}

long long abss(long x){
    if(x<0) return -x;
    return x;
}

int main()
{
    Buffer cin("rrmst.in",1000000);
    freopen("rrmst.out","w",stdout);

    cin >> n;
    G.resize(n);
    for(i=0;i<n;i++) {
        cin>>G[i].x;cin>>G[i].y;
        par[i] = i;
    }
    sort(G.begin(),G.end());

    act = n-1;
    for(i=1;i<G.size();i++){
        for(j=1;i-j>=0 && j<=LIM ;j++){
            long d = j + abss(G[i].y-G[i-j].y);
            if(d<=LIM) D[d].push_back(make_pair(i,i-j));
        }
    }

    for(i=2;i<=LIM;i++){
    for(j=0;j<D[i].size();j++){
        long R1 = D[i][j].x; R1 = Find(R1);
        long R2 = D[i][j].y; R2 = Find(R2);

        if(R1 != R2){
            Merge(R1,R2);
            cost = cost + abss(G[D[i][j].x].x-G[D[i][j].y].x) + abss(G[D[i][j].x].y-G[D[i][j].y].y);
            if(--act == 0) {
                printf("%lld",cost);
                return 0;
            }
        }
    }}

    return 0;
}

#include <iostream>
#include <cstdio>
#include <bitset>
#include <vector>
#include <unordered_set>

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


#define cntRead 276997
#define mod 82663
#define mod1 66013
#define mod2 10003
#define mod3 82663
#define mod4 79593
#define cin fin

long i,cnt;
long long x,n;
bitset<mod+11> B;
unordered_set<long long> uS;

inline long long h1(long long x){
    return x%mod1;
}
inline long long h2(long long x){
    return (x+13)%mod2;
}
inline long long h3(long long x){
    return (x+2)%mod3;
}
inline long long h4(long long x){
    return (x+17)%mod4;
}

int main()
{
    Buffer cin("dtcsu.in",1024*32);
    freopen("dtcsu.out","w",stdout);

    B.reset();
    for(i=1;i<=cntRead;i++){
        cin >> x;
        if(x&1) {B[h1(x)]=1;B[h2(x)]=1;B[h3(x)]=1;B[h4(x)]=1;uS.insert(x);}
    }

    cin >> n;
    for(i=1;i<=n;i++){
        cin >> x;
        if(x==0) continue;
        x /= (x^(x-1))&x;
        if(B[h1(x)]==1 && B[h2(x)]==1 && B[h3(x)]==1)
            if(B[h4(x)]) {
                if(uS.count(x)) cnt++;
            }
    }
    printf("%ld",cnt);

    return 0;
}

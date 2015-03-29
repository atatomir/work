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

#define k 2
#define Prime 1
#define notPrime 0

long t,ans,x;
const long kDef[k]={3,2};

long myPow(long long base,long poww,long long mod){
    long long ans=1;
    while(poww){
        if(poww&1) ans = (ans*base)%mod;
        base = (base*base)%mod;
        poww >>= 1;
    }
    return ans;
}

long isPrime(long n){
    long d,s,r,def,pas;
    bool goNext=false;

    def = n-1; r=0;
    while(def%(1<<(r+1))==0)r++;
    d = def/(1<<r);

    for(pas=k;pas;pas--){
        long long a = kDef[pas-1];

        a = myPow(a,d,n);
        if(a==1 || a==def) continue; //! first condition not to be prime

        for(s=1;s<r;s++){
            a = (a*a)%n;
            if(a==1) return notPrime; //! sure not prime
            if(a==def) {goNext=true;break;} //! may be prime
        }

        if(goNext){goNext=false;continue;}
        return notPrime;
    }
    return Prime;
}

int main()
{
    Buffer cin("dk.in",1024*1024*4);
    freopen("dk.out","w",stdout);

    cin >> t;
    for(;t;t--){
        cin >> x;
        if(x==1 || x==4 || x==6 ) continue;
        if(x==2 || x==3 || x==5 ) {ans++;continue;}
        ans += isPrime(x);
    }

    printf("%ld",ans);

    return 0;
}

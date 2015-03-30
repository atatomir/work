#include <iostream>
#include <cstdio>
#include <cstring>
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

#define maxN 100012
#define maxV 67

struct Triple{
    long a,b,c;

};

long n,i;
Triple Tr[maxN];
long how[maxV][maxV][maxV],def[maxV*2];
long long Ans;

long getCnt(long val){
    long ans=0;
    for(long i=2;i*i<=val;i++){
        if(val%i!=0) continue;
        val /= i;
        if(val%i==0) return -1;
        ans++;
    }
    if(val!=1) ans++;
    return ans;
}

int main()
{
    Buffer cin("puteri.in",1024*1024);
    freopen("puteri.out","w",stdout);

    cin >> n;
    for(i=1;i<=n;i++) cin >> Tr[i].a >> Tr[i].b >> Tr[i].c;

    for(long pas = 2;pas<maxV*2;pas++){
        long long sg = getCnt(pas);
        if(sg==-1) continue;
        if(sg%2==0) sg=-1; else sg=1;

        for(i=1;i<maxV*2;i++) def[i] = i%pas;

        memset(how,0,sizeof(how));
        for(i=1;i<=n;i++){
            Triple tmp = Tr[i];
            tmp.a=def[tmp.a]; tmp.b=def[tmp.b] ; tmp.c=def[tmp.c];
            tmp.a=def[pas - tmp.a]; tmp.b=def[pas - tmp.b] ; tmp.c=def[pas - tmp.c];

            if(tmp.a < maxV && tmp.b < maxV && tmp.c < maxV) Ans += sg*how[tmp.a][tmp.b][tmp.c];
            tmp = Tr[i]; tmp.a=def[tmp.a]; tmp.b=def[tmp.b] ; tmp.c=def[tmp.c];
            how[tmp.a][tmp.b][tmp.c]++;
        }
    }

    printf("%lld",Ans);

    return 0;
}

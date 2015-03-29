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

#define hMod 100000

class Hash{
    public:
        Hash(){
            for(long i=0;i<hMod;i++) C[i].clear();
        }
        void operator<<(long x){
            C[x%hMod].push_back(x);
        }
        bool check(long x){
            long dir = x%hMod;
            for(long i=0;i<C[dir].size();i++)
                if(C[dir][i]==x) return true;
            return false;
        }

    private:
        vector<long> C[hMod];
};

long n,m,i,cod,x,d;
long v[15],tr[15];

bool ok;

int main()
{

    Buffer cin("mcript.in",1024*1024);
    freopen("mcript.out","w",stdout);

    cin >> n >> cod;
    while(cod){
        v[++v[0]] = cod%10;
        cod/=10;
    }

    Hash H;

    for(i=1;v[0];v[0]--,i++) tr[v[v[0]]] = i;
    cin >> m;
    for(i=1;i<=m;i++){
        cin >> x; d = 0;
        while(x){ d = d*10 + tr[x%10]; x/=10; }
        while(d){ x = x*10 + d%10; d/=10;}
        H<<x;
    }

    cin >> m;
    for(;m;m--){
        cin >> n; ok = true;
        for(i=1;i<=n;i++){
            cin >> x;
            if(!H.check(x)){
                ok = false;
                break;
            }
        }
        if(ok) printf("1\n"); else printf("0\n");
    }

    return 0;
}

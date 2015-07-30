#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

class Buffer{
    private:
        vector<char> C;
        long maxBuf,pos;

        void reLoad(){
            fread(&C[0],1,maxBuf,stdin);
            pos=0;
        }
        inline bool isDigit(char c){
            return (c>='0')&&(c<='9');
        }

    public:
        Buffer(char name[],long dim){
            freopen(name,"r",stdin);
            C.resize(dim); maxBuf=dim;
            reLoad();
        }
        Buffer& operator>>(long long& ans){
            while( !isDigit(C[pos]) ){
                if(++pos == maxBuf) reLoad();
            }
            ans=0;
            while( isDigit(C[pos]) ){
                ans = ans*10 + C[pos] - '0';
                if(++pos == maxBuf) reLoad();
            }
            return *this;
        }
        Buffer& operator>>(long & ans){
            while( !isDigit(C[pos]) ){
                if(++pos == maxBuf) reLoad();
            }
            ans=0;
            while( isDigit(C[pos]) ){
                ans = ans*10 + C[pos] - '0';
                if(++pos == maxBuf) reLoad();
            }
            return *this;
        }

};

#define maxN (1<<20)

long n,i,s,d,u,h,aId;
long v[2][maxN];  //! vectorii cu val actuale
long t[2][maxN];  //! vector ajutator pt calc puterea
long ans[2][maxN]; //! vectorul cu raspunsul la ridicare
long inv[maxN]; //! vectorul invers
long rez[maxN];
long long x1,x2;

void reLoad(){
    long aDest = aId^1;

    for(long i=1;i<=n;i++) ans[aDest][i] = ans[aId][ t[u][i] ];

    aId^=1;
}

void Multiply(){
    long dest = u^1;
    for(long i=1;i<=n;i++) t[dest][i] = t[u][ t[u][i] ];
}

void genVect(long long how){
    long i; aId=0;
    for(i=1;i<=n;i++) ans[0][i] = i;
    for(i=1;i<=n;i++) t[u][i] = v[d][i];

    while(how){
        if(how&1) reLoad();
        how >>= 1;
        Multiply();
        u ^= 1;
    }
}

int main()
{
    Buffer fin("hideandseek.in",1<<20);
    freopen("hideandseek.out","w",stdout);

    fin >> n >> x1 >> x2;
    s=0;d=1;
    for(i=1;i<=n;i++) {
        fin >> h;
        v[s][h] = i;
    }

    for(i=1;i<=n;i++) {
        fin >> h;
        v[d][h] = i;
    }

    if(x1 < x2){swap(x1,x2);swap(s,d);}

    while(x2!=1){
        long long how = x1 / x2;
        genVect(how);

        //! am vectorul in ans[aId]
        for(i=1;i<=n;i++) inv[ ans[aId][i] ] = i;
        for(i=1;i<=n;i++) v[s][i] = inv[ v[s][i] ];

        s^=1;d^=1;
        x1 %= x2; swap(x1,x2);
    }

    for(i=1;i<=n;i++) rez[ v[d][i] ] = i;
    for(i=1;i<=n;i++) printf("%ld ",rez[i]);

    return 0;
}

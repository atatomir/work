#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

long tmp[12];

class State{
    public:
        long C[12];
        long dim,i,j,mask;

        void setBit(long x,long y) {C[x]^=1<<y;}
        bool getBit(long x,long y) {return C[x]&(1<<y);}
        State(long ddim){
            dim = ddim; mask=0;
            for(i=0;i<=dim+1;i++) C[i]=0;
            for(i=1;i<=dim;i++) mask^=1<<i;
        }
        bool operator==(State& cmp){
            for(i=1;i<=dim;i++)
                if(C[i]!=cmp.C[i]) return false;
            return true;
        }
        void nextSt(){
            for(i=0;i<=dim+1;i++) tmp[i] = C[i];
            for(i=1;i<=dim;i++){
                C[i] = tmp[i-1]^tmp[i+1]^(tmp[i]<<1)^(tmp[i]>>1);
                C[i] &= mask;
            }
        }
        void operator=(State& tmp){
            dim = tmp.dim; mask = tmp.mask;
            for(i=0;i<=dim+1;i++) C[i] = tmp.C[i];
        }

        void write(){
            for(i=1;i<=dim;i++){
                for(j=1;j<=dim;j++) {
                    if(getBit(i,j)==0)
                        printf("0 ");
                    else
                        printf("1 ");
                }
                printf("\n");
            }
        }
};

///////////////////////////////////
    #define mod 173955

    vector<pair<State,long> > H[mod];
    void addH(State& tmp,long T){
        long id = 0;
        for(long i=1;i<=tmp.dim;i++) id ^= (tmp.C[i]<<2)^(tmp.C[i]>>1);
        id %= mod;
        H[id].push_back(make_pair(tmp,T));
    }
    long getTime(State& tmp){
        long id = 0;
        for(long i=1;i<=tmp.dim;i++) id ^= (tmp.C[i]<<2)^(tmp.C[i]>>1);
        id %= mod;

        for(long i=0;i<H[id].size();i++)
            if(H[id][i].first==tmp) return H[id][i].second;
        return 0;
    }

///////////////////////////////////

long n,t,i,j,b;
long cicl,que;

int main()
{
    freopen("virus.in","r",stdin);
    freopen("virus.out","w",stdout);

    scanf("%ld %ld",&n,&t); t++;
    State ini(n);
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            scanf("%ld",&b);
            if(b) ini.setBit(i,j);
        }
    }

    State it(0);
    it = ini;

    addH(ini,1);

    cicl=1;
    while(1){
        cicl++;
        it.nextSt();

        long T = getTime(it);
        if(T){
            que = T-1;
            cicl = cicl-T;
            break;
        }
        addH(it,cicl);

        if(cicl==t){
            it.write();
            return 0;
        }
    }

    /*
    long tt = t-1; it2 = ini;
    while(tt) {it2.nextSt();tt--;}
    it2.write(); printf("\n");
    */

    if(t<=que){
        t--;
        while(t) {t--;ini.nextSt();}
    } else {
        t -= que; t--; t%=cicl;
        ini = it;

        while(t) {t--;ini.nextSt();}
    }

    ini.write();

    /*cerr << que << ' ' << cicl<<'\n';
    cerr << (ini==it2?"Good":"Bad");*/


    return 0;
}

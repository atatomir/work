#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 311
#define maxLog 11
#define mod 66013

class Buffer {
    public:
        int maxBuf,pos;
        vector<char> Buff;

        Buffer(char fileName[],int buffSize){
            freopen(fileName,"r",stdin);
            maxBuf = buffSize; Buff.resize(maxBuf);
            reFill();
        }

        Buffer& operator>>(int &dest){
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

struct Rar {
    int prov_x,prov_y;
    int v1,v2,v3,v4;

    Rar(){}
    Rar(int _prov_x,int _prov_y){
        prov_x = _prov_x;
        prov_y = _prov_y;

        v1 = v2 = v3 = v4 = -1;
    }

    bool operator<(const Rar& who)const {
        if( v1 != who.v1 ) return v1 < who.v1;
        if( v2 != who.v2 ) return v2 < who.v2;
        if( v3 != who.v3 ) return v3 < who.v3;
        return v4 < who.v4;
    }
    bool operator==(const Rar& who)const {
        if( v1 != who.v1 ) return false;
        if( v2 != who.v2 ) return false;
        if( v3 != who.v3 ) return false;
        return (v4 == who.v4);
    }
};

struct Hash {
    size_t operator()(const Rar& who)const{
        return (who.v1*3+who.v2*2+who.v4*5+who.v3)%mod;
    }
};

int prefix[maxLog][maxN][maxN];
class SuffixArray {
    public:
        void init(int _n,int _m){
            int i,j;
            vector< Rar > aux;

            n = _n; m = _m;
            for (logg = 1; (1<<logg) < n && (1<<logg) < m ; logg++);


            for (int actLog = 1; actLog <= logg; actLog++) {
                aux.clear();
                int def = (1<<(actLog-1));

                int lim_1 = n - (def<<1) + 1;
                int lim_2 = m - (def<<1) + 1;
                for (i = 1; i <= lim_1; i++) {
                    for (j = 1; j <= lim_2; j++) {
                        Rar act(i,j);
                        act.v4 = prefix[actLog-1][i][j];
                        if (i + def <= n) act.v2 = prefix[actLog-1][i+def][j];
                        if (j + def <= m) act.v3 = prefix[actLog-1][i][j+def];
                        if (i + def <= n && j + def <= m) act.v1 = prefix[actLog-1][i+def][j+def];

                        aux.pb(act);
                    }
                }

                sort(aux.begin(),aux.end());
                prefix[actLog][ aux[0].prov_x ][ aux[0].prov_y ] = 1;
                for (i = 1; i < aux.size(); i++) {
                    //! Atentie la sintaxa
                    if ( aux[i-1]==aux[i] ) {
                        prefix[actLog][ aux[i].prov_x ][ aux[i].prov_y ] =
                          prefix[actLog][ aux[i-1].prov_x ][ aux[i-1].prov_y ];
                    } else {
                        prefix[actLog][ aux[i].prov_x ][ aux[i].prov_y ] =
                          prefix[actLog][ aux[i-1].prov_x ][ aux[i-1].prov_y ] + 1;
                    }
                }
            }

        }

    private:
        int n,m;
        int logg;
};

int t,n,m,i,j,k,limit;
SuffixArray SA;

unordered_map< Rar, int, Hash > M;

bool Try( int dim ) {
    int i,j;
    int actLog = 0;
    vector<Rar> aux;
    aux.clear();

    if (dim > limit) return false;

    while ( (1<<(actLog+1) ) <= dim ) actLog++;
    int def = 1<<actLog;

    M.clear();

    for (i = n - dim + 1; i > 0; i--){
        for (j = m - dim + 1; j > 0; j--) {
            Rar act(i,j);
            act.v4 = prefix[actLog][i][j];
            act.v2 = prefix[actLog][i+dim-def][j];
            act.v3 = prefix[actLog][i][j+dim-def];
            act.v1 = prefix[actLog][i+dim-def][j+dim-def];

            if( ++M[act] == k ) return true;
            //aux.pb(act);
        }
    }
    //sort(aux.begin(),aux.end());

    int _limit = aux.size()-k+1;
    for (i = 0; i < _limit; i++){
        if( aux[i] == aux[i+k-1] ) return true;
    }

    return false;
}

int binarySearch() {
    int ans = 0;
    int step;

    for ( step = 1; step <=  limit; step <<= 1 ) ;
    for ( ; step ; step >>= 1 )
        if (Try(ans+step)) ans += step;

    return ans;
}

int main()
{
    Buffer fin("poze.in",1<<20);
    freopen("poze.out","w",stdout);

    for (fin >> t; t; t--) {
        fin >> n >> m >> k;
        limit = min(n,m);

        for (i = 1; i <= n; i++)
            for (j = 1; j <= m; j++)
                fin >> prefix[0][i][j];

        SA.init(n,m);

        printf("%d\n", binarySearch() );
    }


    return 0;
}

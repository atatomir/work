#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

#define maxN 20011
#define mp make_pair
#define xx first
#define yy second
#define abs abss

class Buffer{
    private:
        long pos,dim;
        vector<char> Buff;

        bool isDigit(char c){
            if(c=='-') return true;
            return '0'<=c && c<='9';
        }
        void reFill(){
            pos = 0;
            fread(&Buff[0],1,dim,stdin);
        }

    public:
        Buffer(long dim){
            pos = 0; Buff.resize(dim);
            reFill();
        }
        Buffer& operator>>(long& ans){
            while(!isDigit(Buff[pos]))
                if(++pos==dim) reFill();
            ans = 0; bool sgn = true;
            if(Buff[pos]=='-'){
                sgn = false;
                if(++pos==dim) reFill();
            }
            while(isDigit(Buff[pos])){
                ans = ans*10 + Buff[pos]-'0';
                if(++pos==dim) reFill();
            }

            if(!sgn) ans=-ans;
            return *this;
        }
};

long n,i,s,d,j;
pair<long,long> p[maxN];
long dpA[2][maxN],dpB[2][maxN]; //! A-x,B-y

inline long abs(long x){
    if(x>0) return x;
    return -x;
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("test.in","r",stdin);
    #endif // ONLINE_JUDGE
    Buffer fin(1<<20);

    fin >> n;
    for(i=1;i<=n;i++) fin >> p[i].xx >> p[i].yy;

    s=0;d=1;

    dpA[s][0] = abs(p[1].xx);
    dpB[s][0] = abs(p[1].yy);

    for(i=2;i<=n;i++){
        //! pentru A
        for(j=0;j<i-1;j++) dpA[d][j] = dpA[s][j]+abs( p[i].xx-p[i-1].xx );
        dpA[d][i-1] = 1<<29;
        for(j=0;j<i-1;j++) dpA[d][i-1] = min( dpA[d][i-1] , dpB[s][j]+abs( p[i].xx-p[j].xx ) );
        //! pentru B
        for(j=0;j<i-1;j++) dpB[d][j] = dpB[s][j]+abs( p[i].yy-p[i-1].yy );
        dpB[d][i-1] = 1<<29;
        for(j=0;j<i-1;j++) dpB[d][i-1] = min( dpB[d][i-1] , dpA[s][j]+abs( p[i].yy-p[j].yy ) );

        swap(s,d);
    }

    long ans = 1<<29;
    for(i=0;i<n;i++) ans = min(ans, dpA[s][i] );
    for(i=0;i<n;i++) ans = min(ans, dpB[s][i] );
    printf("%ld",ans);

    return 0;
}

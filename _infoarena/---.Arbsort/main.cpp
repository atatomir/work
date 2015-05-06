#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

char s[100000];

class bigNumber{
    private:
        vector<long> C;
        long dim;

        void check(){
            long sz = C.size();
            if(sz-dim < 10) C.resize(dim+20,0);
        }

    public:
        bigNumber(){
            C.clear();
            dim = 1; check();
            C[1] = 0;
        }
        bigNumber(long v){
            C.clear();
            dim = 1; check();
            C[1] = v;
        }

        void getNumber(){
            C.clear();

            scanf("%s",s+1);
            dim = strlen(s+1); check();

            long pos;
            for(long i=dim,pos=1;i;i--,pos++) C[pos] = s[i]-'0';
        }

        bigNumber& operator+(bigNumber &who){
            dim = max(dim,who.dim); check();

            for(long i=1;i<=dim;i++) C[i] += who.C[i];
            for(long i=1;i<=dim;i++) {
                if(C[i] < 10) continue;
                C[i+1] += C[i]/10;
                C[i] %= 10;
            }

            if(C[dim+1]) dim++; check();

            return *this;
        }

        bigNumber& operator-(bigNumber &who){
            for(long i=1;i<=dim;i++) C[i] -= who.C[i];
            for(long i=1;i<=dim;i++){
                if(C[i]>=0) continue;
                C[i] += 10;
                C[i+1]--;
            }

            while(dim>1 && C[dim]==0) dim--;
            return *this;
        }

        bool isSmaller(bigNumber& who){
            if(dim < who.dim) return true;
            if(dim > who.dim) return false;

            for(long i=dim;i;i--)
                if(C[i]>who.C[i]) return false;
                else if(C[i]<who.C[i]) return true;

            return true;
        }
};

#define maxN 205

long n,i,j,L,C;
bigNumber dp[maxN][maxN];

int main()
{
    freopen("arbsort.in","r",stdin);
    freopen("arbsort.out","w",stdout);

    scanf("%ld\n",&n);

    bigNumber p;
    p.getNumber();

    for(i=1;i<n;i++) dp[n][i] = bigNumber(1);
    for(i=n-1;i>0;i--){
        dp[i][i-1] = bigNumber();
        dp[i][i-1] + dp[i+1][i-1] ;
        dp[i][i-1] + dp[i+1][i];

        for(j=i-2;j>0;j--){
            dp[i][j] = bigNumber();
            dp[i][j] + dp[i][j+1];
            dp[i][j] + dp[i+1][j];
        }
    }

    printf("0 ");
    for(L=2,C=1;L<=n;){
        bool good = p.isSmaller(dp[L][C]);
        if(good) { printf("%ld ",C); L++; }
        else     { p - dp[L][C]; C++; }
    }


    return 0;
}

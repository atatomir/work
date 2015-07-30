#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define maxC 20000

class bNumber{
    public:
        int C[maxC];
        long cnt;

        bNumber(long init){
            memset(C,0,sizeof(C));
            cnt=0;
            while(init){
                C[++cnt] = init%10;
                init/=10;
            }
        }
        bNumber(long tPow,long init){
            memset(C,0,sizeof(C));
            cnt = tPow+1; C[cnt] = init;
            while(C[cnt]>9){
                C[cnt+1] = C[cnt]/10;
                C[cnt] %= 10;
                cnt++;
            }
        }

        void operator+(bNumber& tmp){
            cnt = max(cnt,tmp.cnt);
            for(long i=1;i<=cnt;i++) C[i] += tmp.C[i];

            for(long i=1;i<=cnt;i++) {
                C[i+1] += C[i]/10;
                C[i] %= 10;
            }
            while(C[cnt+1]!=0){
                C[cnt+1] = C[cnt]/10;
                C[cnt] %= 10;
                cnt++;
            }
        }
        void operator-(bNumber& tmp){
            cnt = max(cnt,tmp.cnt);
            for(long i=1;i<=cnt;i++) C[i] -= tmp.C[i];

            for(long i=1;i<=cnt;i++){
                while(C[i]<0){
                    C[i] += 10;
                    C[i+1]--;
                }
            }

            while(C[cnt]==0) cnt--;
        }
        void operator/(long def){
            // only in this case
            for(long i=1;i<=cnt;i++) C[i] /= def;
        }
        void operator=(bNumber& tmp){
            cnt = tmp.cnt;
            for(long i=1;i<=cnt;i++) C[i] = tmp.C[i];
        }

        void write(){
            for(long i=cnt;i;i--) printf("%ld",C[i]);
        }
};

long n,c;

int main()
{
    freopen("nrcifre.in","r",stdin);
    freopen("nrcifre.out","w",stdout);

    scanf("%ld %ld",&n,&c);

    bNumber TenNm1oN(n-1,n); // 10^(n-1) * n
    bNumber TenNm1oNm1(n-1,n-1); // 10^(n-1) *(n-1)
    bNumber N(n);
    bNumber Nm1(n-1);
    bNumber Ten(10);
    bNumber One(1);
    bNumber TenNoN(n,n);  // 10^n * n
    bNumber TenN(n,1); // 10^n
    bNumber TenNm1(n-1,1); // 10*(n-1)

    if(c>0){
        TenNm1oN.write();
    } else {
        if(n==1)
            printf("1");
        else {
            bNumber tmp(0),tmp2(0);
            tmp = TenNm1oNm1;
            tmp2 = TenNm1; tmp2-Ten;tmp2/9;
            tmp-tmp2;

            tmp.write();

        }
    }

    printf("\n");

    bNumber tmp(0);
    tmp = One;
    tmp+TenNoN;

    bNumber tmp2(0);
    tmp2 = TenN; tmp2-One; tmp2/9;

    tmp-tmp2;
    tmp.write();


    return 0;
}

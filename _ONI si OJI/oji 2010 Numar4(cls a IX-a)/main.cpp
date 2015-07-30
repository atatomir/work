#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define maxN 2011
class bNumber{
    public:
        long l;
        long C[maxN];

        bNumber(long lung){
            memset(C,0,sizeof(C));
            l = lung;
        }
        bool div2(){
            return C[1]%2==0;
        }
        bool div5(){
            return C[1]%5==0;
        }
        void operator/=(long d){
            for(long i=l;i;i--){
                C[i-1] = (C[i]%d)*10 + C[i-1];
                C[i] /= d;
            }
            while(C[l]==0) l--;
        }
        void write(){
            printf("%ld\n",l);
            for(long i=l;i;i--) printf("%ld",C[i]);
            printf("\n");
        }
};

long n,m,i;

int main()
{
    freopen("numar4.in","r",stdin);
    freopen("numar4.out","w",stdout);

    scanf("%ld %ld",&n,&m);
    bNumber a(n+m),b(m+1);

    b.C[m+1] = 1;
    for(i=1;i<=n+m;i++) scanf("%ld",&a.C[n+m-i+1]);
    a/=1;

    while(a.div2()&&b.div2()) {
        a/=2;
        b/=2;
    }
    while(a.div5()&&b.div5()) {
        a/=5;
        b/=5;
    }

    a.write();
    b.write();

    return 0;
}

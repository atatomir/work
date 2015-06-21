#include <cstdio>

using namespace std;

#define maxN (1000011)
#define ll long long

long n,i,_n;
long qA[maxN],qB[maxN],qC[maxN];
long a,b,c;
long col[maxN];
long wh [maxN];

long _fin;

long getNext(long x){
    if(!wh[x]) return x;
    wh[x] = getNext(wh[x]);
    return wh[x];
}

int main()
{
    freopen("curcubeu.in","r",stdin);
    freopen("curcubeu.out","w",stdout);

    scanf("%ld %ld %ld %ld",&n,&qA[1],&qB[1],&qC[1]);
    _n = n;

    for(i=2;i<n;i++){
        qA[i] = ((ll)i*qA[i-1])%n;
        qB[i] = ((ll)i*qB[i-1])%n;
        qC[i] = ((ll)i*qC[i-1])%n;
    }

    for(;--n>0;){
        a = qA[n];
        b = qB[n];
        c = qC[n];
        if(a>b) {long t=a;a=b;b=t;}

        //! solve...
        long s = a,d=b,what=c;
        _fin=d+1;

        s = getNext(s);
        while(s<=d){
            col[s] = what;
            wh[s] = _fin;
            s = getNext(s+1);
        }
    }

    n = _n; i=1;
    for(   ;i+4<n;i+=5) printf("%ld\n%ld\n%ld\n%ld\n%ld\n",col[i],col[i+1],col[i+2],col[i+3],col[i+4]);
    for(   ;i<n;i++) printf("%ld\n",col[i]);

    return 0;
}


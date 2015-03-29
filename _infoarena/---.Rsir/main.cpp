#include <iostream>
#include <cstdio>

using namespace std;

long a,b,x,y,z,mod;
long def0[7011],def1[7011];
long long n;


struct State{
    long t0,t1;

    inline State getNext(){
        State ans;
        ans.t0 = t1;
        ans.t1 = def0[t0] + def1[t1] ;
        if(ans.t1 >= mod) ans.t1 -= mod;
        return ans;
    }
    inline State getNextNext(){
        State ans = getNext();
        return ans.getNext();
    }
    bool operator!=(State tmp){
        return (tmp.t0 != t0)||(tmp.t1 != t1);
    }
};

State p1,p2,beg;
long lC,lCic;

int main()
{
    freopen("rsir.in","r",stdin);
    freopen("rsir.out","w",stdout);

    scanf("%ld %ld %ld %ld %ld %ld %ld %ld %lld",&p1.t0,&p1.t1,&a,&b,&x,&y,&z,&mod,&n);
    p1.t1 %= mod; p1.t0 %= mod; beg = p1;
    a %= mod; b %= mod; x %= mod; y %= mod; z %= mod;

    for(long i=0;i<mod;i++) {
        def0[i] = (1LL*i*i*a + i*x + z)% mod;
        def1[i] = (1LL*i*i*b + i*y)% mod;
    }

    p2 = p1.getNext(); lCic = 1;
    while(p1 != p2){
        p1 = p1.getNext();
        p2 = p2.getNextNext();
        lCic++;
    }

    p1 = beg; lC = 0; p2 = p2.getNext();
    while(p1 != p2) {
        p1 = p1.getNext();
        p2 = p2.getNext();
        lC++;
    }

    if(n == 0) {
        printf("%ld",beg.t0);
        return 0;
    }
    if(n <= lC){
        for(long i = 2;i<=n;i++) beg = beg.getNext();
        printf("%ld",beg.t1);
    } else {
        n -= lC; n%=lCic; if(!n) n = lCic;
        for(long i = 2;i<=n;i++)
            p1 = p1.getNext();
        printf("%ld",p1.t1);
    }

    return 0;
}

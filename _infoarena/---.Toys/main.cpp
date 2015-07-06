#include <iostream>
#include <algorithm>

using namespace std;

#define maxN 2000011

long long n,l,m,s,x,y,z,v,i;
long tt[maxN];

long a,b;
long long ans;

long getTime(long pos , long toy){
    if(toy) return pos;
    else    return l+(l-pos);
}

int main()
{
    freopen("toys.in","r",stdin);
    freopen("toys.out","w",stdout);

    scanf("%lld %lld %lld",&n,&l,&m);
    scanf("%lld %lld %lld %lld %lld",&s,&x,&y,&z,&v);

    a = s; b = 1; tt[ ++tt[0] ] = getTime(a,b); m++;
    for(i=2;i<=n;i++){
        long _a = a;
        a = ( x * _a + y * ( i - 1 ) ) % ( l - 1 ) + 1;
        b = ( z * _a + v * ( i - 1 ) ) % 2;
        tt[ ++tt[0] ] = getTime(a,b);

        if(b) m++;
    }

    ans = 2LL*l*(m/n);
    m %= n; if(m==0) {m=n; ans-=2LL*l;}

    nth_element( tt+1,tt+m,tt+n+1 );
    ans += (long long)tt[m];
    printf("%lld",ans);

    return 0;
}

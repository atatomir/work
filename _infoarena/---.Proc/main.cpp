#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define defStep (1LL<<35)

long long n,i,k1,k2;
long long _k1,_k2,_low,_high;

bool Try( long long lim ) {
    _low = 1; _high = 2;
    _k1 = k1; _k2 = k2;
    for (int i = 1; i <= n; i++) {
        long long act = lim;

        long long how = min( _k2 , act/_high );
        _k2 -= how;
        act -= _high*how;

        how = min( _k1 , act/_low );
        _k1 -= how;
        act -= _low*how;

        _low++; _high += 2;

        if( _k1 == _k2 && _k1 == 0 ) return true;
    }
    return false;
}

int main()
{
    freopen("proc.in","r",stdin);
    freopen("proc.out","w",stdout);

    scanf("%lld%lld%lld",&k2,&k1,&n);
    k2 -= k1;

    long long ans = 0;
    for (long long step = defStep; step > 0; step >>= 1) {
        if ( !Try(ans+step) ) ans += step;
    }

    if( k1 == k2 && k1 == 0 ) ans = -1;
    printf("%lld",ans+1);

    return 0;
}

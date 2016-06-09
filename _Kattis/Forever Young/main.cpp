#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>


using namespace std;


#define mp make_pair
#define pb push_back
#define ll long long

#define base_limit 100000
#define number_limit 10000

ll nr, limit;
ll base, x;
ll ans = 10;

ll to_base(ll base, ll nr) {
    ll ans = 0;
    ll poww = 1;
    
    while (nr) {
        if (nr % base >= 10) return -1;
        ans += (nr % base) * poww;
        nr /= base; poww *= 10;
    }
    
    return ans;
}

ll to_dec(ll base, ll x) {
    ll aux = 1;
    ll ans = 0;
    
    while (x) {
        if (nr - aux * (x % 10) < 0) return (1LL << 60); // adding more then we need
        
        ans += aux * (x % 10);
        x /= 10; 
        
        if (nr / aux < base && x != 0) return (1LL << 60); //! aux is too big  
        aux *= base;
    }
    
    return ans;
}

ll cb(ll x, ll nr) {
    ll ans = 0;
    
    for (ll step = (1LL << 60); step; step >>= 1)
        if ( to_dec(ans + step, x) <= nr)
            ans += step;
    
    return ans;
}

int main() {
    
   scanf("%lld%lld", &nr, &limit);
   
   for (base = 11; base <= base_limit; base++) 
       if (to_base(base, nr) >= limit) 
            ans = max(ans, base); 
      
    for (x = limit; x <= number_limit; x++) {
        base = cb(x, nr);
        if (base == 0) continue;
        
        if (to_dec(base, x) == nr)
            ans = max(ans, base);
    }
   
    printf("%lld", ans);
    
    return 0;
}

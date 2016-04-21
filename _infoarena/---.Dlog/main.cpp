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
#define ll long long

#define maxBit 22
#define lim 9


int t, ti, i;
ll mod, G, Y, act, plim;
unordered_map<int, int> H;
ll Bits[maxBit];


ll poww(ll a, int b) {
    ll ans = 1;

    while (b) {
        if (b & 1) ans = (ans * a) % mod;
        b >>= 1;
        a = (a * a) % mod;
    }
    return ans;
}

ll invmod(ll a) {
    return poww(a, mod - 2);
}



int main()
{
    freopen("dlog.in","r",stdin);
    freopen("dlog.out","w",stdout);

    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++) {
        scanf("%lld%lld%lld", &mod, &G, &Y);
        H.clear();

        //! first half
        Bits[0] = G;
        for (i = 1; i < maxBit; i++) Bits[i] = (Bits[i - 1] * Bits[i - 1]) % mod;
        plim = min(mod, 1LL << lim);

        for (int state = 0, act = 1; state < plim; state++, act = (act * Bits[0]) % mod)
            H[act] = state + 1;

        //! second half
        Bits[0] = invmod(G);
        for (i = 1; i < maxBit; i++) Bits[i] = (Bits[i - 1] * Bits[i - 1]) % mod;
        plim = 1LL << lim;


        for (int state = 0, act = Y; state < mod; state += plim, act = (act * Bits[lim]) % mod) {
            int _pair = H[act];

            if (_pair == 0) continue;

            int ans = _pair - 1 + state;
            if (ans == mod - 1) ans = 0;

            printf("%d\n", ans);
            break;
        }
    }


    return 0;
}

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

struct Miller_Rabin {
    vector<ll> list_a = {2, 3, 666013, 1000000007, 15485863}; // primes
    ll mod;

    Miller_Rabin() { }

    Miller_Rabin(int limit) {
        list_a.resize(limit);
    }

    ll poww(ll a, ll b) {
        ll ans = 1;

        while (b) {
            if (b & 1) ans = (ans * a) % mod;
            b >>= 1;
            a = (a * a) % mod;
        }

        return ans;
    }

    bool check(ll a) {
        // if this function returns false then number is composed
        // otherwise we dont really know if it is prime :)

        ll nr;
        ll base = mod - 1;

        while ( (base & 1) == 0 ) base >>= 1;
        nr = poww(a, base);

        if (nr == 1) return true;
        for (; base <= mod - 1; base <<= 1, nr = (nr * nr) % mod) {
            if (nr == mod - 1) return true;
            if (nr == 1) return false;
        }

        return false;
    }

    bool is_prime(ll x) {

        if (x == 2) return true;
        for (auto e : list_a)
            if (x == e)
                return true;

        mod = x;
        for (auto e : list_a)
            if (!check(e))
                return false;

        return true;
    }
};

int n, i, x, cnt;
Miller_Rabin test(2);

int main()
{
    srand(time(NULL));

    freopen("dk.in","r",stdin);
    freopen("dk.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d", &x);
        if (test.is_prime(x))
            cnt++;
    }

    printf("%d", cnt);
    cerr << cnt;


    return 0;
}

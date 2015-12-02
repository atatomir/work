#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

#define mp make_pair
#define pb push_back

#define mod 9999991
#define ll long long

#define maxN 2000011

ll n, i, lim, pos;
vector<int> need;
map<ll, ll> M;
ll fact;

ll myPow(ll a, ll b) {
    ll ans = 1;
    while (b) {
        if (b & 1) ans = (ans * a) % mod;
        b >>= 1;
        a = (a * a) % mod;
    }

    return ans;
}

ll invMod(ll a) {
    return myPow(a, mod - 2);
}

int main()
{
    freopen("dirichlet.in","r",stdin);
    freopen("dirichlet.out","w",stdout);

    scanf("%lld", &n);

    if (n == 1) {
        printf("1");
        return 0;
    }
    if (n == 2) {
        printf("3");
        return 0;
    }

    need.pb(2 * n);
    need.pb(n);
    need.pb(n - 1);
    need.pb(n + 1);

    sort(need.begin(), need.end());

    lim = n * 2;

    fact = 1;
    for (i = 1; i <= lim; i++) {
        fact = (fact * i) % mod;
        if (need[pos] == i) {
            M[i] = fact;
            pos++;
        }
    }

    //cerr << M[2 * n] / M[n] / M[n] << '\n';
    //cerr << M[2 * n] / M[n - 1] / M[n + 1];

    ll ans = (((M[2 * n] * invMod(M[n]) ) % mod) * invMod(M[2 * n - n])) % mod -
             (((M[2 * n] * invMod(M[n - 1]) ) % mod) * invMod(M[2 * n - n + 1])) % mod +
             mod;
    printf("%lld", ans % mod);


    return 0;
}

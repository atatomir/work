#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define mod 666013

int n, i;
ll ans;

ll poww(ll a, ll b) {
    ll ans = 1;

    while (b > 0) {
        if (b & 1) ans = (ans * a) % mod;
        b >>= 1;
        a = (a * a) % mod;
    }

    return ans;
}

int solve(int node) {
    if (node > n) return 0;

    int sol = solve(2 * node) + solve(2 * node + 1) + 1;
    ans *= poww(sol, mod - 2);
    ans %= mod;

    return sol;
}

int main()
{
    freopen("permheap.in","r",stdin);
    freopen("permheap.out","w",stdout);

    scanf("%d", &n);
    ans = 1;

    for (i = 1; i <= n; i++) {
        ans *= i;
        ans %= mod;
    }

    solve(1);
    printf("%lld", ans);


    return 0;
}

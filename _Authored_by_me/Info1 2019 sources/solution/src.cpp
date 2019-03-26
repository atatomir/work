#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <assert.h>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

bool solve_recursive(vector<ll> vals, ll k) {
    while (true) {
        ll sum = 0;

        for (auto e : vals) sum += e;
        if (sum & 1) return true;
        if (k == 1) return false;

        k >>= 1;
        for (auto& e: vals) e >>= 1;
    }
}

bool solve_formula(vector<ll> vals, ll k) {
    ll ans = 0;

    for (auto e : vals) ans ^= e;
    if (ans == 0) return false;

    while ((ans & 1) == 0) {
        k >>= 1;
        ans >>= 1;
    }

    if (k >= 1) return true;
    return false;
}

void solve_input() {
    ll n, k, i, t, ti, inside;
    vector<ll> aux = {};
    ll sum = 0;

    assert(scanf("%lld", &t) == 1);
        for (ti = 1; ti <= t; ti++) {
        assert(scanf("%lld%lld", &n, &k) == 2);
        assert(0 <= n && n <= 1000000);
        assert(1 <= k && k <= 1000000000000000000LL);
        sum += n;
        inside = 0;
        
        aux.resize(n);
        for (auto& e: aux) {
            assert(scanf("%lld", &e) == 1);
            assert(0 <= e && e <= 1000000000000000000LL);
            inside += e;
       }


        bool answer = solve_formula(aux, k);
        if (answer == true)
            printf("Naka\n");
        else
            printf("Jima\n");
    }

    assert(sum <= 1000000);
}

int main()
{
    //freopen("test.in", "r", stdin);
    solve_input();


    return 0;
}

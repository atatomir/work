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

//#define debug(x) ;
#define debug(x) cerr << #x << " = " << x << "\n";

ostream& operator<<(ostream& cerr, vector<ll> aux) {
    cerr << "[";
    for (auto e : aux) cerr << e << ' ';
    cerr << "]";
    return cerr;
}

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
    ll n, k, i, t, ti;
    vector<ll> aux = {};

    assert(scanf("%lld", &t) == 1);
        for (ti = 1; ti <= t; ti++) {
        assert(scanf("%lld%lld", &n, &k) == 2);
        assert(0 <= n && n <= 1000000);
        assert(1 <= k && k <= 1000000000000000000LL);

        aux.resize(n);
        for (auto& e: aux) {
            assert(scanf("%lld", &e) == 1);
            assert(e <= 1000000000000000000LL);
            assert(e >= 0);
        }

        bool answer = solve_recursive(aux, k);
        if (answer == true)
            printf("Naka\n");
        else
            printf("Jima\n");
    }
}

ll randi() {
    const ll limit = 1LL << 30;
    ll v1 = rand() % limit;
    ll v2 = rand() % limit;
    ll ans = (v1 << 30) | v2;
    assert(ans >= 0);
    return ans;
}

pair<vector<ll>, ll> generate_test(ll n, ll k, ll xoro, ll limit) {
    ll i, act_xor = 0;
    vector<ll> ans = {};

    for (i = 0; i < n; i++) {
        ans.pb(randi() % limit);
        act_xor ^= ans.back();
    }

    ans[0] ^= act_xor^xoro;
    random_shuffle(ans.begin(), ans.end());
    return mp(ans, k);
}

vector<ll> normalize(vector<ll> v, ll need) {
    ll sum = 0;
    for (auto e : v) sum += e;
    for (auto& e: v) e = (e * need) / sum;

    sum = 0;
    for (auto e : v) sum += e;
    
    v[0] += need - sum;
    return v;
}

void print_test(int t) {
    ofstream fin("test.in");
    ofstream fout("test.out");

    fin << t << '\n';
    for (int ti = 1; ti <= t; ti++) {
        // ---------------------- n     k  xor  limit
        ll n = 2 + (randi() % 19);
        ll k = 1 + (randi() % 23);
        ll xoro = 15;

        /*ll p = 3 + (randi() % 50);
        k = randi() % (1LL << p);
        k |= 1LL << p;

        ll shift = p + (ti % 5) - 2;
        ll dif = 57 - shift;
        xoro = (randi() % (1LL << dif)) << shift;
        */

        if (ti % 137 == 13) xoro = 0;
        
        auto test = generate_test(n, k, xoro, randi() % (1LL << 55));
        test.first = normalize(test.first, 6 + (randi() % 15));

        bool ans1 = solve_recursive(test.first, test.second);
        bool ans2 = solve_formula(test.first, test.second);

        assert(ans1 == ans2);
        fin << test.first.size() << ' ' << test.second << '\n';
        for (auto e : test.first) fin << e << ' ';
        fin << '\n';

        if (ans1)
           fout << "Naka\n";
        else
           fout << "Jima\n";

    }

    fin.close();
    fout.close();
}

int main()
{
    srand(time(0));
    

    //freopen("test.in", "r", stdin);
    solve_input();


    return 0;
}

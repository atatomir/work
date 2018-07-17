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
#define ll long long

ll poww(ll a, ll b, ll mod) {
    ll ans = 1;
    while (b > 0) {
        if (b & 1) ans = (ans * a) % mod;
        b >>= 1;
        a = (a * a) % mod;
    }
    return ans;
}

const int maxN = 250011;

const ll mod = 1000000007;
const ll base = 500167;
const ll inv_base = poww(base, mod - 2, mod);

const ll mod2 = 1000000009;
const ll base2 = 503803; 
const ll inv_base2 = poww(base2, mod2 - 2, mod2);

struct hash_key {
    ll v1, v2;

    hash_key() {v1 = v2 = 0;}
    hash_key(ll _v1, ll _v2) {v1 = _v1 % mod; v2 = _v2 % mod2;}
    hash_key(ll x) { v1 = (mod + x) % mod, v2 = (mod2 + x) % mod2; }

    bool operator<(const hash_key &who) const {
        return mp(v1, v2) < mp(who.v1, who.v2);
    }
    
    bool operator==(const hash_key &who) const {
        return mp(v1, v2) == mp(who.v1, who.v2);
    }

    void operator*=(const hash_key who) {
        v1 = (v1 * who.v1) % mod;
        v2 = (v2 * who.v2) % mod2;
    }

    void operator+=(const hash_key who) {
        v1 = (v1 + who.v1) % mod;
        v2 = (v2 + who.v2) % mod2;
    }

    void operator-=(const hash_key who) {
        v1 = (v1 + mod - who.v1) % mod;
        v2 = (v2 + + mod2 - who.v2) % mod2;
    }

    hash_key get_inv()const {
        return {poww(v1, mod - 2, mod), poww(v2, mod2 - 2, mod2)};
    }
};

struct smart_map {
    map<hash_key, ll> M;
    hash_key bonus;

    smart_map() {
        M.clear();
        bonus = {1, 1};
    }

    void operator*=(hash_key who) {
        bonus *= who;
    }

    void add(hash_key x) {
        x *= bonus.get_inv();
        M[x]++;
    }

    ll query(hash_key x) {
        x *= bonus.get_inv();
        return M[x];
    }
};

ll n, i;
char s[maxN];
smart_map data;
ll ans;

hash_key act, full;
const hash_key to_left = {base, base2};
const hash_key to_right = {inv_base, inv_base2};

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d\n%s", &n, s + 1);

    data.add(hash_key(0));
    act = hash_key(0);

    for (i = n; i >= 1; i--) {
        if (s[i] == '+') act += 1;    
        if (s[i] == '-') act += -1;
        if (s[i] == '<') act *= to_left;
        if (s[i] == '>') act *= to_right;
    }

    full = act;
    act = hash_key(0);

    for (i = n; i >= 1; i--) {
        if (s[i] == '+') act += 1;    
        if (s[i] == '-') act += -1;
        if (s[i] == '<') act *= to_left, data *= to_left;
        if (s[i] == '>') act *= to_right, data *= to_right;
    
        hash_key src = act;
        src -= full;
        ans += data.query(src);

        data.add(act);
    }

    printf("%lld", ans);

    return 0;
}

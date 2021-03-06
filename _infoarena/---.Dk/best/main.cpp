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

#define lim 100000

class Buffer {
    public:
        Buffer(string name, int _dim) {
            if (name != "")
                freopen(name.c_str(), "r", stdin);
            dim = _dim;
            data.resize(dim + 11);
            refill();
        }

        template<typename T>
        Buffer& operator>>(T &dest) {
            T sign = +1;
            dest = 0;

            while (!is_digit(data[pos]) && data[pos] != '-')
                if (++pos == dim)
                    refill();

            if (data[pos] == '-') {
                sign = -1;
                if (++pos == dim)
                    refill();
            }

            while (is_digit(data[pos])) {
                dest = dest * 10 + data[pos] - '0';
                if (++pos == dim)
                    refill();
            }

            dest *= sign;
            return *this;
        }


    private:
        int pos, dim;
        vector<char> data;

        bool is_digit(char c) {
            return '0' <= c && c <= '9';
        }

        void refill() {
            memset(&data[0], 0, dim);
            fread(&data[0], 1, dim, stdin);
            pos = 0;
        }
};

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

bool ciur[lim + 11];

void pre() {
    ll i, j;

    ciur[1] = true;
    for (i = 2; i <= lim; i++) {
        if (ciur[i]) continue;

        for (j = i * i; j <= lim; j += i)
            ciur[j] = true;
    }
}

int main()
{
    Buffer fin("dk.in", 1 << 22);
    freopen("dk.out","w",stdout);

    pre();

    fin >> n;
    for (i = 1; i <= n; i++) {
        fin >> x;

        if (x > lim)
            cnt += test.is_prime(x);
        else
            cnt += (ciur[x] == false);
    }

    printf("%d", cnt);
    cerr << cnt;


    return 0;
}

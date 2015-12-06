#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define mod 1000000007LL
#define maxVal 500
#define ll long long
#define maxN 200011
#define maxDQ 35

class Buffer {
    public:
        Buffer(string name, int _dim) {
            freopen(name.c_str(), "r", stdin);
            dim = _dim;
            data.resize(dim);

            reFill();
        }

        template<class T>
        Buffer& operator>>(T &who) {
            bool sign = false;

            while (!isDigit(data[pos]) && data[pos] != '-')
                if (++pos == dim) reFill();

            if (data[pos] == '-') {
                sign = true;
                if (++pos == dim) reFill();
            }

            who = 0;
            while (isDigit(data[pos])) {
                who = who * 10 + data[pos] - '0';
                if (++pos == dim) reFill();
            }

            if (sign) who *= -1;
            return *this;
        }

    private:
        int dim, pos;
        vector<char> data;

        bool isDigit(char c) {
            return ('0' <= c && c <= '9');
        }

        void reFill() {
            pos = 0;
            memset(&data[0], 0, dim);
            fread(&data[0], 1, dim, stdin);
        }
};

Buffer fin("produse.in", 1 << 20);

ll n, i, d, x, lim;
ll how[maxVal];
vector<ll> more;
ll ans;

ll dp[maxN];

ll fact[maxN];
ll invfact[maxN];

ll max_how;

ll myPow(ll a, ll b) {
    ll ans = 1;
    while (b > 0) {
        if (b & 1) ans = (ans * a) % mod;
        b >>= 1;
        a = (a * a) % mod;
    }
    return ans;
}

ll Comb(ll n, ll k) {
    if (n == k)
        return 1;
    return (fact[n] * ((invfact[k] * invfact[n - k]) % mod)) % mod;
}

void solve_dp() {
    int i, j, k;

    fact[1] = 1; invfact[1] = 1;
    for (i = 2; i <= max_how; i++) fact[i] = (fact[i - 1] * i) % mod;
    for (i = 2; i <= max_how; i++) invfact[i] = myPow(fact[i], mod - 2);

    dp[1] = 1;

    for (i = 2; i <= lim; i++) {
        if (how[i] == 0)
            continue;

        for (j = (d / i) * i; j >= i; j -= i) {
            int pos = j;
            for (k = how[i]; k > 0; k--) {
                if (pos % i != 0) break;
                pos /= i;

                if(dp[pos] > 0) dp[j] = (dp[j] + dp[pos] * Comb(how[i], how[i] - k + 1)) % mod;
            }
        }
    }

    ll ind = more.size() - 1;
    sort(more.begin(), more.end());
    for (i = 1; i <= d; i++) {
        while (ind >= 0 && more[ind] * i > d) ind--;
        ans += dp[i] * (ind + 2);
        ans %= mod;
    }
}

int main()
{
    //freopen("produse.in","r",stdin);
    freopen("produse.out","w",stdout);

    fin >> n >> d;

    lim = (int)sqrt(d) + 1;
    for (i = 1; i <= n; i++) {
        fin >> x;
        if (x > lim) {
            more.pb(x);
        } else {
            how[x]++;
            max_how = max(max_how, how[x]);
        }
    }

    n -= how[1];
    solve_dp();

    ans = (ans * myPow(2, how[1])) % mod;
    ans--;

    if (ans < 0) ans += mod;
    printf("%lld", ans);


    return 0;
}

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stack>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 200011

class Buffer {
    public:
        Buffer(string name, int _dim) {
            freopen(name.c_str(), "r", stdin);
            dim = _dim;
            data.resize(dim + 10);
            refill();
        }

        template<typename T>
        Buffer& operator>>(T &dest) {
            while (!is_digit(data[pos]))
                if (++pos == dim)
                    refill();

            dest = 0;

            while (is_digit(data[pos])) {
                dest = dest * 10 + data[pos] - '0';
                if (++pos == dim)
                    refill();
            }

            return *this;
        }

    private:
        int dim, pos;
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


int n, k, i;
ll pr[maxN], dist[maxN];

ll ans = (1LL << 60);


ll solve(int conf) {
    int i, j;
    vector<int> bits;
    ll ans = 0;

    bits.clear();
    for (i = 0; i < n; i++)
        if ( (conf >> i) & 1 )
            bits.pb(i + 1);

    for (i = 1; i < bits.size(); i++) {
        int bg = bits[i - 1];
        int en = bits[i];

        ll aux = pr[bg];
        for (j = bg; j < en; j++) aux += dist[j];

        ans = max(ans, aux);
    }

    int bg = bits.back();
    int en = bits[0];

    ll aux = pr[bg];
    for (i = bg; i <= n; i++) aux += dist[i];
    for (i = 1; i < en; i++) aux += dist[i];

    ans = max(ans, aux);


    return ans;
}

int main()
{
    Buffer fin("oneouts.in", 1 << 20);
    freopen("oneouts.ok","w",stdout);

    fin >> n >> k;
    for (i = 1; i <= n; i++)
        fin >> dist[i];

    for (i = 1; i <= n; i++)
        fin >> pr[i];


    for (int state = (1 << n) - 1; state > 0; state--) {
        int aux = state;
        int bits = 0;

        while (aux) {
            bits++;
            aux &= aux - 1;
        }

        if (bits > k) continue;
        ans = min(ans, solve(state));

        if (solve(state) == 25) {
            cerr << "da";
        }
    }

    printf("%lld", ans);

    return 0;
}

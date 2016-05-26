#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

#define ll long long
#define mp make_pair
#define pb push_back

#define maxN 1024
#define maxQ 1000011

class Buffer {
    public:
        Buffer(string name, int _dim) {
            freopen(name.c_str(), "r", stdin);
            dim = _dim;
            data.resize(dim + 17);
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
            pos = 0;
            memset(&data[0], 0, dim);
            fread(&data[0], 1, dim, stdin);
        }
};

int n, q, i;
ll y, t, s;
ll x[maxN], sum[maxN];

vector< pair<ll, int> > off;
ll ans[maxQ];

void solve() {
    int i, pos;
    ll where, when;
    ll val;

    val = 0;
    where = 0; when = 0;
    for (pos = 0; pos < off.size();) {
        if (val >= x[where]) val -= x[where];
        if (where == 0) val += y;
        if(++where == n + 1) where = 0;
        when++;

        while (pos < off.size()) {
            if (off[pos].first > when) break;
            ans[off[pos++].second] = val;
        }
    }
}

int main()
{
    Buffer fin("expozitie.in", 1 << 20);
    //freopen("expozitie.in", "r", stdin);
    freopen("expozitie.out", "w", stdout);

    fin >> n >> q >> y;
    for (i = 1; i <= n; i++) fin >> x[i], sum[i] = x[i] + sum[i - 1];

    for (i = 1; i <= q; i++) {
       fin >> t >> s;

        ll where = t % (n + 1);
        ll new_t;

        if (s <= where)
            new_t = t - (where - s);
        else
            new_t = t - (where + n + 1 - s);

        if (new_t > 0) off.pb(mp(new_t, i));
    }

    sort(off.begin(), off.end());
    solve();

    for (i = 1; i <= q; i++) printf("%lld\n", ans[i]);

    return 0;
}

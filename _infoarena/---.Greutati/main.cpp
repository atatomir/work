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

const ll mod = 1000000007;

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

struct elem {
    ll pp, cnt;

    bool operator<(const elem& who) const {
        return pp < who.pp;
    }
};

ll n, p, i, x, y;
vector<elem> bts;
ll ans;

void upd(ll &a, ll b) {
    a += b;
    if (a >= mod) a -= mod;
}

ll poww(ll a, ll b) {
    ll ans = 1;

    while (b > 0) {
        if (b & 1) ans = (ans * a) % mod;
        b >>= 1;
        a = (a * a) % mod;
    }

    return ans;
}

void maturica() {
    vector<elem> data;
    elem aux;
    int i;

    sort(bts.begin(), bts.end());

    data = bts;
    bts.clear();
    aux = {0, 0};

    for (i = 0; i < data.size(); i++) {
        auto e = data[i];

        if (aux.cnt > 0) {
            if (aux.pp == e.pp) {
                e.cnt += aux.cnt;
            } else {
                e = aux; i--;
            }
        }

        aux = {e.pp + 1, 0};
        if (e.cnt % 2 == 1) {
            aux.cnt = e.cnt / 2;
            e.cnt = 1;
        } else {
            aux.cnt = (e.cnt / 2) - 1;
            e.cnt = 2;
        }

        bts.pb(e);

        if (i == data.size() - 1 && aux.cnt > 0) {
            data.pb({aux.pp, 0});
        }
    }

    cerr << "Am terminat cu maturica.\n";
}

void solve() {
    int i, j;
    bool all_equal = true;

    for (i = bts.size() - 1; i >= 0; i--) {

        if (bts[i].cnt == 2) {
            if (all_equal) {
                //! continua
            } else {
                //! adauga-le pe ambele la cel mai mic
                upd(ans, mod - poww(2, bts[i].pp + 1));
            }
        }

        if (bts[i].cnt == 1) {
            if (all_equal) {
                //! aici treaba este grea

                for (j = i; j >= 0; j--) {
                    if (i - j != bts[i].pp - bts[j].pp) break;
                    if (bts[j].cnt == 2) break;
                }

                if (j >= 0) {
                    if (i - j == bts[i].pp - bts[j].pp) {
                        if (bts[j].cnt == 2) {
                            //! putem sa facem acesti biti egali
                            i = j;
                            continue;
                        }
                    }
                }

                all_equal = false;
                upd(ans, poww(2, bts[i].pp));

            } else {
                //! adauga-l la cel mai mic
                upd(ans, mod - poww(2, bts[i].pp));
            }
        }

    }

    cerr << "Am terminat de rezolvat.\n";
}

int main()
{
    Buffer fin("greutati.in", 1 << 20);
    freopen("greutati.out","w",stdout);

    fin >> n >> p;
    bts.reserve(n);
    for (i = 1; i <= n; i++) {
        fin >> x >> y;
        bts.pb({x, y});
    }

    maturica();
    solve();

    ans %= mod;
    printf("%lld", ans);

    cerr << "Rezulat final : " << ans << '\n';

    return 0;
}

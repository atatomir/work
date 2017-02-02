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

#define maxN 150011

class Buffer {
    public:
        Buffer(string name, int _dim) {
            freopen(name.c_str(), "r", stdin);
            dim = _dim;
            data.resize(dim + 11);
            refill();
        }

        template<typename T>
        Buffer& operator>>(T &dest) {
            while (!is_digit(data[pos]))
                if(++pos == dim)
                    refill();

            dest = 0;
            while (is_digit(data[pos])) {
                dest = dest * 10 + data[pos] - '0';
                if(++pos == dim)
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

struct aib {
    int n;
    vector<ll> data;

    void init(int _n) {
        n = _n;
        data = vector<ll>(n + 11, 0);
    }

    int zrs(int x) {
        return (x ^ (x - 1)) & x;
    }

    void add(int pos, ll v) {
        while (pos <= n) {
            data[pos] += v;
            pos += zrs(pos);
        }
    }

    ll sum(int pos) {
        ll ans = 0;

        while (pos > 0) {
            ans += data[pos];
            pos -= zrs(pos);
        }

        return ans;
    }

    int cb(ll x) {
        ll ans = 0;

        for (ll step = 1 << 18; step > 0; step >>= 1)
            if (ans + step <= n)
                if (data[ans + step] < x)
                    ans += step, x -= data[ans];

        return ans;
    }
};

struct query {
    int op;
    ll x, y;
};

int q, n, i;
query Q[maxN];
vector< pair<ll, ll> > down, up;

aib down_x, down_y;
aib up_x, up_y;

map< pair<ll, ll>, int > Mdown, Mup;


bool query(ll x, ll y) {
    int id;
    ll y0, dx, xx, yy;

    id = down_x.cb(x) + 1;
    if (id > n) return 0;

    y0 = down_y.sum(id - 1);
    xx = down[id - 1].first;
    yy = down[id - 1].second;
    dx = x - down_x.sum(id - 1);

    if (y * xx < y0 * xx + yy * dx)
        return false;

    // now up

    id = up_x.cb(x) + 1;
    y0 = up_y.sum(id - 1);
    xx = up[id - 1].first;
    yy = up[id - 1].second;
    dx = x - up_x.sum(id - 1);

    if (y * xx > y0 * xx + yy * dx)
        return false;

    return true;
}

int main()
{
    Buffer fin("combl.in", 1 << 20);
    //freopen("combl.in","r",stdin);
    freopen("combl.out","w",stdout);

    fin >> q;
    for (i = 1; i <= q; i++) {
        fin >> Q[i].op >> Q[i].x >> Q[i].y;
        if (Q[i].op == 1)
            down.pb({Q[i].x, Q[i].y});
    }

    up = down;
    sort(down.begin(), down.end(), [](const pair<ll, ll>& a, const pair<ll, ll>& b)->bool const {
        return a.first * b.second > a.second * b.first;
    });

    sort(up.begin(), up.end(), [](const pair<ll, ll>& a, const pair<ll, ll>& b)->bool const {
        return a.first * b.second < a.second * b.first;
    });

    n = down.size();
    down_x.init(n);
    down_y.init(n);
    up_x.init(n);
    up_y.init(n);

    for (i = 0; i < n; i++) {
        Mdown[down[i]] = i + 1;
        Mup[up[i]] = i + 1;
    }

    for (i = 1; i <= q; i++) {
        if (Q[i].op == 1) {
            int pd = Mdown[{Q[i].x, Q[i].y}];
            int pu = Mup[{Q[i].x, Q[i].y}];

            down_x.add(pd, Q[i].x);
            down_y.add(pd, Q[i].y);

            up_x.add(pu, Q[i].x);
            up_y.add(pu, Q[i].y);
        }

        if (Q[i].op == 2) {
            int pd = Mdown[{Q[i].x, Q[i].y}];
            int pu = Mup[{Q[i].x, Q[i].y}];

            down_x.add(pd, -Q[i].x);
            down_y.add(pd, -Q[i].y);

            up_x.add(pu, -Q[i].x);
            up_y.add(pu, -Q[i].y);
        }

        if (Q[i].op == 3) {
            if (query(Q[i].x, Q[i].y))
                printf("DA\n");
            else
                printf("NU\n");
        }
    }


    return 0;
}

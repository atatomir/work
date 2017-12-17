#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <functional>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define lSon (node << 1)
#define rSon (lSon | 1)

const int maxN = 50011;
const int limit = 100;
const int maxVal = limit + 11;

struct Buffer {
    public:
        Buffer(int _dim) {
            dim = _dim;
            data.resize(dim + 11);
            refill();
        }

        Buffer& operator>>(int& a) {
            while (!is_digit(data[pos]))
                if (++pos == dim)
                    refill();

            a = 0;
            while (is_digit(data[pos])) {
                a = a * 10 + data[pos] - '0';
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

struct aint {
    int data[maxN * 4 + 11], op[maxN * 4 + 11];

    void init() {
        memset(data, 0, sizeof(data));
        for (int i = 0; i < maxN * 4 + 3; i++)
            op[i] = -1;
    }

    void upd(int node, int l, int r, int qL, int qR, int val) {
        if (qL <= l && r <= qR) {
            op[node] = val;
            data[node] = op[node] * (r - l + 1);
            return;
        }

        int mid = (l + r) >> 1;
        if (op[node] != -1) {
            op[lSon] = op[node];
            data[lSon] = op[node] * (mid - l + 1);
            op[rSon] = op[node];
            data[rSon] = op[node] * (r - mid);
            op[node] = -1;
        }

        if (qL <= mid) upd(lSon, l, mid, qL, qR, val);
        if (qR > mid) upd(rSon, mid + 1, r, qL, qR, val);
        data[node] = data[lSon] + data[rSon];
    }

    int que(int node, int l, int r, int qL, int qR) {
        if (qL <= l && r <= qR)
            return data[node];

        int mid = (l + r) >> 1;
        if (op[node] != -1) {
            op[lSon] = op[node];
            data[lSon] = op[node] * (mid - l + 1);
            op[rSon] = op[node];
            data[rSon] = op[node] * (r - mid);
            op[node] = -1;
        }

        int ans = 0;
        if (qL <= mid) ans += que(lSon, l, mid, qL, qR);
        if (qR > mid) ans += que(rSon, mid + 1, r, qL, qR);
        return ans;
    }
};

int n, q, i, tp, a, b, c, d, m, x, c1, c2;
bool ciur[maxVal];
vector<int> divs;
vector<int> pp[maxVal];
int v[maxN];

aint work[30];
ll ans;

ll poww(ll a, ll b) {
    ll ans = 1;

    while (b > 0) {
        if (b & 1) ans = (ans * a) % m;
        b >>= 1;
        a = (a * a) % m;
    }

    return ans;
}

void pre() {
    int i, j;

    for (i = 2; i <= limit; i++) {
        if (ciur[i]) continue;
        divs.pb(i);
        for (j = i * i; j <= limit; j += i)
            ciur[j] = true;
    }

    for (i = 0; i < divs.size(); i++) work[i].init();

    for (i = 1; i <= limit; i++) {
        int aux = i;

        for (int d = 0; d < divs.size(); d++) {
            int cnt = 0;

            while (aux % divs[d] == 0)
                aux /= divs[d], cnt++;

            pp[i].pb(cnt);
        }
    }
}

void fact_and_execute(int nr, function<void(int, int)> callback) {
    int cnt, i;

    for (i = 0; i < pp[nr].size(); i++)
        callback(i, pp[nr][i]);
}

int main()
{
    freopen("test.in","r",stdin);
    Buffer fin(1 << 20);

    pre();
    cerr << divs.size() << '\n';

    fin >> n;
    for (i = 1; i <= n; i++) {
        fin >> v[i];
        fact_and_execute(v[i], [](int where, int cnt)->void {
            work[where].upd(1, 1, n, i, i, cnt);
        });
    }

    fin >> q;
    for (i = 1; i <= q; i++) {
        fin >> tp;
        if (tp == 1) {
            fin >> a >> b >> x;
            fact_and_execute(x, [](int where, int cnt)->void {
                work[where].upd(1, 1, n, a, b, cnt);
            });
        } else {
            fin >> a >> b >> c >> d >> m;

            ans = 1;
            for (int dv = 0; dv < divs.size(); dv++) {
                c1 = work[dv].que(1, 1, n, a, b);
                c2 = work[dv].que(1, 1, n, c, d);

                if (c1 < c2) {
                    ans = -1;
                    break;
                }

                if (c1 > c2)
                    ans = (ans * poww(divs[dv], c1 - c2)) % m;
            }

            printf("%lld\n", ans);
        }
    }


    return 0;
}

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

#define maxN 100011
#define TP pair<int, int>

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
vector<int> list[maxN];
ll ans, step;

vector<int> act;
bool us[maxN];
bool good;

int ql, qr;
pair<int, ll> Q[maxN]; //! pos, limit

ll bul;
ll gl_lim;




void dfs(int node) {
    static int bg;

    if (good) return;
    act.pb(node);
    us[node] = true;


    if (act.size() <= k)
        bg = act[0];
    else
        bg = act[act.size() - 1 - k + 1];

    if (dist[bg - 1] + dist[n] - dist[node - 1] + pr[node] <= gl_lim) {
        good = true;
        return ;
    }

    for (auto to : list[node])
        dfs(to);

    act.pop_back();
}

bool check(ll lim) {
    int i, pos, need;
    ll aux;

    memset(us, 0, sizeof(us));
    for (i = 1; i <= n; i++) list[i].clear();
    gl_lim = lim;

    //! compute edges
    ql = 1; qr = 0;
    for (i = 1; i <= n; i++) {
        ll act = lim + dist[i - 1] - pr[i];

        if (ql > qr || Q[qr].second < act)
            Q[++qr] = mp(i, act);

        while (ql <= qr && Q[ql].second < dist[i - 1]) ql++;

        if (ql <= qr && Q[ql].first != i)
            list[Q[ql].first].pb(i);
    }

    act.clear();
    good = false;
    for (i = 1; i <= n && !good; i++)
        if (!us[i])
            dfs(i);



    return good;
}



int main()
{
    Buffer fin("oneouts.in", 1 << 20);
    freopen("oneouts.out","w",stdout);

    fin >> n >> k;
    for (i = 1; i <= n; i++)
        fin >> dist[i];

    for (i = 1; i <= n; i++) {
        fin >> pr[i];
        bul = max(bul, pr[i]);
    }

    for (i = 2; i <= n; i++) dist[i] += dist[i - 1];
    bul += dist[n];


    ans = 0;
    for (step = (1LL << 48); step > 0; step >>= 1)
        if (ans + step <= bul)
            if (!check(ans + step))
                ans += step;

    printf("%lld", ans + 1);
    cerr << ans + 1;

    return 0;
}

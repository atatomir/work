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
#define TP pair<int, int>
#define maxLog 19

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
ll ans, step;
int go[maxN];

vector<int> list[maxN];
bool us[maxN];

vector<int> act;
bool good;

vector<int> valid;




void dfs(int node) {
    static int need, pos;

    us[node] = true;
    if (good) return;
    act.pb(go[node]);

    need = node + n;
    if (act[0] >= need) {
        if (act.size() <= k) {
            good = true;
            return;
        }

        if (act[act.size() - k] >= need) {
            good = true;
            return;
        }
    }

    for (auto to : list[node])
        dfs(to);

    act.pop_back();
}


void pre() {
    int i, last;

    valid.clear();
    for (i = 1; i <= 2 * n; i++) {
        if (go[i] <= last) {
            go[i] = i;
            continue;
        }

        last = go[i];
        valid.pb(i);
    }
}

int query(int pos) {
    auto it = upper_bound(valid.begin(), valid.end(), pos);
    it--;

    return *it;
}

bool check(ll lim) {
    int i, pos, need;
    ll aux;


    for (i = 2 * n; i >= 1; i--) {
        aux = lim - pr[i];

        if (dist[i - 1] + aux < dist[i]) {
            go[i] = i;
            continue;
        }

        go[i] = upper_bound(dist + i, dist + 2 * n + 1, dist[i - 1] + aux) - dist;
    }

    memset(us, 0, sizeof(us));
    for (i = 1; i <= 2 * n; i++) list[i].clear();

    pre();
    for (i = 2 * n; i >= 1; i--) {
        if (go[i] == i) continue;

        int to = query(go[i]);
        if (to != i) list[to].pb(i);
    }

    act.clear();
    good = false;
    for (i = 2 * n; i >= 1 && !good; i--)
        if (!us[i])
            dfs(i);



    return good;
}




int main()
{
    Buffer fin("oneouts.in", 1 << 20);
    freopen("oneouts.out","w",stdout);

    fin >> n >> k;
    for (i = 1; i <= n; i++) {
        fin >> dist[i];
        dist[i + n] = dist[i];
    }

    for (i = 1; i <= n; i++) {
        fin >> pr[i];
        pr[i + n] = pr[i];
    }

    for (i = 2; i <= 2 * n; i++) dist[i] += dist[i - 1];


    ans = 0;
    for (step = (1LL << 50); step > 0; step >>= 1)
        if (!check(ans + step))
            ans += step;

    printf("%lld", ans + 1);
    cerr << ans + 1;

    return 0;
}

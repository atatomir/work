#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 300011
#define maxM 400011

class Buffer {
    public:
        Buffer(string name, int _dim) {
            freopen(name.c_str(), "r", stdin);
            dim = _dim;
            data.resize(dim + 11);
            refill();
        }

        Buffer& operator>>(int &dest) {
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

const int inf = 1 << 30;

int n, m, k, q, i, x, y, l;
vector<int> start;
vector< pair<int, int> > list[maxN];

priority_queue< pair<int, int>, vector< pair<int, int> >, greater< pair<int, int> > > H;
int dist[maxN], T;

vector< pair<int, int> > ord;
bool on[maxN];
int dad[maxN];
vector<int> Q[maxN];

pair<int, int> data[maxM];
int ans[maxM], refe[maxM];


int Find(int x) {
    if (dad[x] == x) return x;
    dad[x] = Find(dad[x]);
    return dad[x];
}

bool Merge(int x, int y, int time) {
    int e;

    x = Find(x);
    y = Find(y);

    if (x == y) return false;
    if (Q[x].size() > Q[y].size()) swap(x, y);
    dad[x] = y;

    Q[y].reserve(Q[x].size() + Q[y].size());

    while (!Q[x].empty()) {
        e = Q[x].back();
        Q[x].pop_back();

        if (ans[e] != 0) continue;

        if (Find(data[e].first) == Find(data[e].second))
            ans[e] = max(ans[e], time);
        else
            Q[y].pb(e);
    }
    Q[x].clear();

    return true;
}

int main()
{
    Buffer fin("termite.in", 1 << 20);
    freopen("termite.out","w",stdout);

    fin >> n >> m >> k >> q;
    for (i = 1; i <= k; i++) {
        fin >> x;
        start.pb(x);
    }

    for (i = 1; i <= m; i++) {
        fin >> x >> y >> l;
        list[x].pb(mp(y, l));
        list[y].pb(mp(x, l));
    }

    for (i = 1; i <= q; i++) {
        fin >> x >> y >> T;
        refe[i] = T; ans[i] = 0;
        data[i] = mp(x, y);
        Q[x].pb(i);
        Q[y].pb(i);
    }

    for (i = 1; i <= n; i++) dist[i] = inf;
    for (auto e : start) {
        dist[e] = 0;
        H.push(mp(0, e));
    }

    while (!H.empty()) {
        int node = H.top().second;
        int dd = H.top().first;
        H.pop();

        if (dist[node] != dd) continue;
        ord.pb(mp(dist[node], node));

        for (auto to : list[node]) {
            if (dd + to.second < dist[to.first]) {
                dist[to.first] = dd + to.second;
                H.push(mp(dist[to.first], to.first));
            }
        }
    }

    for (i = 1; i <= n; i++) {
        dad[i] = i;
        on[i] = false;

        for (auto e : Q[i]) {
            if (data[e].first == data[e].second) {
                ans[e] = dist[data[e].first];
            }
        }
    }

    sort(ord.begin(), ord.end());
    reverse(ord.begin(), ord.end());

    for (auto act : ord) {
        on[act.second] = true;

        for (auto to : list[act.second]) {
            if (!on[to.first]) continue;
            Merge(act.second, to.first, act.first);
        }
    }

    for (i = 1; i <= q; i++)
        printf("%d\n", max(0, ans[i] - refe[i]));




    return 0;
}

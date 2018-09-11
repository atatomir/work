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

const int maxN = 200011;

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

struct edge {
    int x, y;
    int cost;
};

int n, k, i, j, cnt;
edge E[maxN];
vector< pair<int, int> > list[maxN];

int gr[maxN]; //! grupa din care face parte
bool active[maxN]; //! daca muchia e activa
int sz[maxN]; //! dimensiunea grupei
int dad[maxN]; //! pentru pre_smecherie
vector<int> cand; //! candidatii
int ans;
vector<int> aux;

int root[maxN];
queue<int> Q;

int Find(int x) {
    if (dad[x] == x) return x;
    dad[x] = Find(dad[x]);
    return dad[x];
}

void pre() {
    int i;

    for (i = 1; i <= n; i++) {
        dad[i] = i;
        sz[i] = 1;
    }

    for (i = n - 1; i >= 1; i--) {
        int x = E[i].x;
        int y = E[i].y;

        int xx = Find(x);
        int yy = Find(y);

        if (sz[xx] < sz[yy]) {
            swap(E[i].x, E[i].y);
            swap(x, y);
            swap(xx, yy);
        }

        dad[yy] = xx;
        sz[xx] += sz[yy];
    }
}

bool check() {
    while (!cand.empty()) {
        if (sz[cand.back()] >= k) break;
        cand.pop_back();
    }
    return cand.empty() == false;
}

void bfs(int node) {
    int p, i;

    root[node] = 0;
    Q.push(node);

    while (!Q.empty()) {
        node = Q.front();
        Q.pop();
        aux.pb(node);

        //! sterge muchiile inactive
        p = 0;
        for (i = 0; i < list[node].size(); i++)
            if (active[list[node][i].second])
                list[node][p++] = list[node][i];

        list[node].resize(p);

        for (auto e : list[node]) {
            if (e.first == root[node]) continue;
            root[e.first] = node;
            Q.push(e.first);
        }
    }
}

void add_edge(int id) {
    int x = E[id].x;
    int y = E[id].y;

    if (sz[gr[x]] < sz[gr[y]]) swap(x, y);

    aux.clear();
    bfs(y);

    for (auto e : aux) {
        sz[gr[e]]--;
        gr[e] = gr[x];
        if (++sz[gr[e]] == k) cand.pb(gr[e]);
    }

    active[id] = true;
    list[x].pb(mp(y, id));
    list[y].pb(mp(x, id));
}

void rm_edge(int id) {
    int x = E[id].x;
    int y = E[id].y;

    active[id] = false;
    aux.clear();
    bfs(y);

    cnt++;
    for (auto e : aux) {
        sz[gr[e]]--;
        gr[e] = cnt;
        if (++sz[gr[e]] == k) cand.pb(gr[e]);
    }

}

int main()
{
    Buffer fin("nespus.in", 1 << 20);
    freopen("nespus.out","w",stdout);

    fin >> n >> k;
    for (i = 1; i < n; i++)
        fin >> E[i].x >> E[i].y >> E[i].cost;

    pre();

    for (i = 1; i <= n; i++) gr[i] = i, sz[i] = 1;
    ans = E[n - 1].cost - E[1].cost;
    cnt = n;

    j = 0;
    for (i = 1; i <= n; i++) {
        while (!check()) {
            if (++j > n) {
                printf("%d", ans);
                return 0;
            }

            add_edge(j);
        }

        ans = min(ans, E[j].cost - E[i].cost);
        rm_edge(i);
    }

    printf("%d", ans);

    return 0;
}

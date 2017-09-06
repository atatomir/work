#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <map>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 100011

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

int n, m, k, i, x, y;
int col[maxN];
vector<int> list[maxN];
vector<int> who[maxN];
vector< pair<int, int> > E;

int last[maxN], idd;
vector<int> colors[maxN];
vector<int> edges[maxN];
unordered_map<ll, bool> M;

void compute_color(int id) {
    for (auto n1 : who[id]) {
        if (last[n1] != id) {
            last[n1] = id;
            colors[n1].pb(id);
        }

        for (auto n2 : list[n1]) {
            if (last[n2] != id) {
                last[n2] = id;
                colors[n2].pb(id);
            }
        }
    }
}

void compute_edges(int n1, int n2, int id) {
    if (colors[n1].size() > colors[n2].size()) swap(n1, n2);
    ll hp = (1LL * n2) << 20;

    for (auto c : colors[n1]) {
        if (M[hp | c]) {
            edges[c].pb(id);
        }
    }
}

void dfs(int node) {
    last[node] = idd;

    for (auto to : list[node])
        if (last[to] != idd)
            dfs(to);
}

int count_tribe(int id) {
    int ans = 0;

    for (auto e : edges[id]) {
        list[E[e].first].clear();
        list[E[e].second].clear();
    }

    for (auto e : edges[id]) {
        list[E[e].first].pb(E[e].second);
        list[E[e].second].pb(E[e].first);
    }

    idd = id;
    for (auto e : edges[id]) {
        if (last[E[e].first] != idd) {
            ans++;
            dfs(E[e].first);
        }
    }

    return ans;
}

void dfs2(int node) {
    last[node] = idd;
    for (auto to : list[node]) {
        if (last[to] == idd) continue;
        if (M[ ((1LL * to) << 20) | idd] == false) continue;
        dfs2(to);
    }
}

int count_brute(int id) {
    int ans = 0;
    int i;

    idd = id;
    for (i = 1; i <= n; i++) {
        if (last[i] == id) continue;
        if (M[ ((1LL * i) << 20) | id] == false) continue;
        dfs2(i);
        ans++;
    }

    return ans;
}

int main()
{
    Buffer fin("tribes.in", 1 << 20);
    //freopen("tribes.in","r",stdin);
    freopen("tribes.out","w",stdout);


    fin >> n >> m >> k;
    for (i = 1; i <= n; i++) fin >> col[i], who[col[i]].pb(i);
    for (i = 1; i <= m; i++) {
        fin >> x >> y;
        list[x].pb(y);
        list[y].pb(x);
        E.pb(mp(x, y));
    }

    for (i = 1; i <= k; i++)
        compute_color(i);

    for (i = 1; i <= n; i++)
        for (auto c : colors[i])
            M[ ((1LL * i) << 20) | c ] = true;


    if (n <= 1000) {
        memset(last, 0, sizeof(last));
        for (i = 1; i <= k; i++)
            printf("%d\n", count_brute(i));
        return 0;
    }



    for (i = 0; i < m; i++)
        compute_edges(E[i].first, E[i].second, i);

    for (i = 1; i <= n; i++) list[i].clear();

    memset(last, 0, sizeof(last));
    for (i = 1; i <= k; i++) {
        printf("%d\n", count_tribe(i));
    }

    return 0;
}

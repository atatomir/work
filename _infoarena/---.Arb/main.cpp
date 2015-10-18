#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

#define pb push_back
#define mp make_pair

#define maxN 250011
#define maxM 500011
#define ll int

class Buffer {
    public:
        Buffer(string name, int _dim) {
            freopen(name.c_str(), "r", stdin);
            dim = _dim;
            data.resize(dim);
            reFill();
        }

        Buffer& operator>>(int &dest) {
            while (!isDigit(data[pos])) {
                if (++pos == dim) reFill();
            }
            dest = 0;
            while(isDigit(data[pos])) {
                dest = dest * 10 + data[pos] - '0';
                if (++pos == dim) reFill();
            }
            return *this;
        }

    private:
        int dim, pos;
        vector<char> data;

        void reFill() {
            pos = 0;
            memset(&data[0], 0, dim);
            fread(&data[0], 1, dim, stdin);
        }
        bool isDigit(char c) {
            return ('0' <= c) && (c <= '9');
        }
};
Buffer fin("arb.in", 1 << 20);

class aib {
    public:
        void init(int _n, ll *_data) {
            n = _n;
            data = _data;
        }

        void add(int pos, ll val) {
            while (pos <= n) {
                data[pos] += val;
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

    private:
        int n;
        ll *data;

        int zrs(int x) {
            return (x & (x - 1)) ^ x;
        }
};

int n, i, x, q, y;
int cost[maxN];
vector<int> list[maxN];
int lvl[maxN];
int _left[maxN], _right[maxN], dim;

vector< pair<int, int> > queries;
int q_node[maxM];
ll ans[maxM];
aib work;
ll aib_data[maxN];
vector<int> nodes[maxN];


void dfs(int node) {
    nodes[lvl[node]].pb(node);
    _left[node] = ++ dim;

    for (int i = 0; i < list[node].size(); i++) {
        lvl[list[node][i]] = lvl[node] + 1;
        dfs(list[node][i]);
    }

    _right[node] = dim;
}

int main()
{
    //freopen("arb.in", "r", stdin);
    freopen("arb.out", "w", stdout);

    fin >> n;
    for (i = 1; i <= n; i++) fin >> cost[i];
    for (i = 2; i <= n; i++) {
        fin >> x;
        list[x].pb(i);
    }

    lvl[1] = 1;
    dfs(1);

    fin >> q;
    for (i = 1; i <= q; i++) {
        fin >> x >> y;
        y = lvl[x] + y;

        q_node[i] = x;
        queries.pb(mp(y, i));
    }

    sort(queries.begin(), queries.end());
    work.init(n, aib_data);

    int it = 1;
    for (i = 0; i < queries.size(); i++) {
        pair<int, int> Q = queries[i];

        while (it <= n && it <= Q.first) {

            for (int j = 0; j < nodes[it].size(); j++) {
                int who = nodes[it][j];
                work.add(_left[who], cost[who]);
            }

            it++;
        }

        int node = q_node[Q.second];
        ans[Q.second] = work.sum(_right[node]) - work.sum(_left[node] - 1);
    }

    for (i = 1; i <= q; i++) printf("%d\n", ans[i]);

    return 0;
}

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

#define maxN 400011
#define inf 1000000000

class Buffer {
    public:
        Buffer(int _dim) {
            freopen("sushi2.in", "r", stdin);
            dim = _dim;
            data.resize(dim + 11);
            refill();
        }

        Buffer& operator>>(int &dest) {
            while (!is_digit(data[pos]) && data[pos] != '-')
                if (++pos == dim)
                    refill();

            dest = 0;
            int sgn = 1;

            if (data[pos] == '-') {
                sgn = -1;
                if (++pos == dim)
                    refill();
            }

            while (is_digit(data[pos])) {
                dest = dest * 10 + data[pos] - '0';
                if (++pos == dim)
                    refill();
            }

            dest *= sgn;

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

int bucket = 600;

int n, m, i, k, j, x, y, t, dim;
vector<int> list[maxN], pos[maxN];
vector<int> nodes, upds[maxN];

int ans[maxN];
int last[maxN], nxt[maxN];

int act_id, id[maxN];
vector<int> manu;
int best;


void dfs(int node, int root) {
    nodes.pb(node);

    for (auto to : list[node]) {
        if (to == root) {
            pos[node] = {0};
            continue;
        }
        pos[node].pb(nodes.size() - 1);
        dfs(to, node);
        nodes.pb(node);
    }

    if(node != 1) pos[node][0] = nodes.size() - 1;
}

int main()
{
    Buffer fin(1 << 20);
    freopen("sushi2.out","w",stdout);

    fin >> n >> m;
    for (i = 1; i <= n; i++) {
        fin >> k;
        for (j = 1; j <= k; j++) {
            fin >> x;
            list[i].pb(x);
        }
    }

    dfs(1, 0);

    dim = nodes.size();
    for (i = 1; i < dim; i++) nodes.pb(nodes[i]);

    for (i = 1; i <= m; i++) {
        fin >> x >> y >> t;
        int node = pos[x][y - 1];
        upds[node].pb(t);
    }

    for (i = nodes.size() - 1; i >= 0; i--) {
        nxt[i] = last[ nodes[i] ];
        last[ nodes[i] ] = i;
    }

    bucket = min(bucket, dim);
    for (i = 0; i < dim; i += bucket) {
        manu.clear();

        act_id++;
        for (j = i; j < i + bucket; j++) {
            if (id[ nodes[j] ] != act_id) {
                id[ nodes[j] ] = act_id;
                manu.pb(nodes[j]);
            }
        }

        best = -inf;
        for (j = i; j < i + bucket; j++) {
            for (auto e : upds[j]) {
                best = max(best, e + (i + bucket - j));

                for (auto who : manu)
                    ans[who] = max(ans[who], e + last[who] - j);
            }

            last[ nodes[j] ] = nxt[j];
        }

        for (int v = 1; v <= n; v++)
            if (id[v] != act_id)
                ans[v] = max(ans[v], best + last[v] - (i + bucket));
    }

    for (i = 1; i <= n; i++)
        printf("%d ", ans[i]);



    return 0;
}

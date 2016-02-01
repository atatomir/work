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

#define maxN 11022
#define maxM maxN * 10
#define maxBit 9
#define inf 1000000000
#define pii pair<int, int>

class Buffer {
    public:
        Buffer(string name, int _dim) {
            freopen(name.c_str(), "r", stdin);
            data.resize(_dim + 3);
            dim = _dim;
            refill();
        }

        template<typename T>
        Buffer& operator>>(T &ans) {
            while (!is_digit(data[pos])) {
                pos++;
                if (pos == dim) refill();
            }

            ans = 0;
            while (is_digit(data[pos])) {
                ans = ans * 10 + data[pos++] - '0';
                if (pos == dim) refill();
            }

            return *this;
        }

    private:
        int dim, pos;
        vector<char> data;

        void refill() {
            memset(&data[0], 0, dim);
            pos = 0;
            fread(&data[0], 1, dim, stdin);
        }

        bool is_digit(char c) {
            return '0' <= c && c <= '9';
        }
};

//! ---------------

int n, m, i, x, y;
int pay[maxM];

vector<int> who[maxN];

int lvl[maxN], dad[maxN];
bool us[maxN];

int dp[maxN][1 << maxBit];
vector<int> list[maxN];

int common[maxN][maxBit];
vector<int> bits[1 << maxBit];

void dfs(int node) {
    us[node] = true;

    for (int i = 0; i < list[node].size(); i++) {
        int to = list[node][i];

        if (us[to]) {
            list[node][i] = list[node][ list[node].size() - 1 ];
            list[node].pop_back();
            i--;
            continue;
        }

        dad[to] = node;
        lvl[to] = lvl[node] + 1;
        dfs(to);
    }
}

void mark(int x, int y, int id) {
    if (lvl[x] > lvl[y]) swap(x, y);

    while (lvl[y] != lvl[x]) {
        who[y].pb(id);
        y = dad[y];
    }

    while (x != y) {
        who[x].pb(id);
        who[y].pb(id);
        x = dad[x];
        y = dad[y];
    }

    who[x].pb(id);
}

void solve(int node) {
    int i, state;
    int cnt = who[node].size();
    int lim = (1 << cnt) - 1;

    dp[node][0] = inf;

    //! get common bits
    for (auto son : list[node]) {
        int pos1, pos2;

        pos2 = 0;
        if (who[son].empty() == false )
        for (pos1 = 0; pos1 < cnt ; pos1++) {
            while (pos2 + 1 < who[son].size()) {
                int next_val = who[son][pos2 + 1];
                if (next_val > who[node][pos1]) break;
                pos2++;
            }

            if (who[node][pos1] == who[son][pos2]) {
                common[son][pos1] = pos2 + 1;
            }
        }

        solve(son);
    }

    //! compute act state
    for (state = 1; state <= lim; state++) {
        dp[node][state] = 0;

        for (auto bit : bits[state])
            dp[node][state] += pay[ who[node][bit] ];
    }


    for (auto son : list[node]) {
        for (state = 1; state <= lim; state++) {
            int son_mask = 0;

            for (auto bit : bits[state]) {
                if (common[son][bit]) {
                    son_mask |= 1 << (common[son][bit] - 1);
                    dp[node][state] -= pay[ who[node][bit] ];
                }
            }

            dp[node][state] += dp[son][son_mask];
        }
    }

    //! compress states
    for (state = lim; state > 0; state--)
        for (auto bit : bits[state])
            dp[node][ state ^ (1 << bit) ] = min(dp[node][ state ^ (1 << bit) ], dp[node][state]);
}

int main()
{
    Buffer fin("mesaj3.in", 1 << 20); //!atentie
    //freopen("mesaj3.in","r",stdin);
    freopen("mesaj3.out","w",stdout);

    fin >> n;

    for (i = 1; i < n; i++) {
        fin >> x >> y;
        list[x].pb(y);
        list[y].pb(x);
    }

    dfs(1);

    fin >> m;
    for (i = 1; i <= m; i++) {
        fin >> x >> y >> pay[i];
        mark(x, y, i);
    }

    int lim = 1 << maxBit;
    for (int state = 1; state < lim; state++)
        for (i = 0; i < maxBit; i++)
            if (state & (1 << i))
                bits[state].pb(i);

    solve(1);

    printf("%d", dp[1][0]);
    cerr << dp[1][0];

    return 0;
}

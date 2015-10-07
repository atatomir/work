#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 100011
#define maxLog 5

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

Buffer fin("maimute.in", 1 << 17);

int n, i, x, y, t;
vector<int> list[maxN];
int lvl[maxN];

int dp[maxLog][maxN];

void dfs(int node) {
    for (auto to : list[node]) {
        if (lvl[to] != 0) continue;

        lvl[to] = lvl[node] + 1;
        dp[0][to] = node;
        dfs(to);
    }
}

int goUp(int x, int how) {
    int actLog = 0;

    while (how > 0) {
        int work = how % 10;
        for (int i = 1; i <= work; i++) x = dp[actLog][ x ];

        how /= 10;
        actLog++;
    }

    return x;
}

int main()
{
    //freopen("maimute.in","r",stdin);
    freopen("maimute.out","w",stdout);

    fin >> n;
    for (i = 1; i < n; i++) {
        fin >> x >> y;
        list[x].pb(y);
        list[y].pb(x);
    }

    lvl[1] = 1;
    dfs(1);

    for (int actLog = 1; actLog < maxLog; actLog++) {
        for (i = 1; i <= n; i++) {
            dp[actLog][i] = dp[actLog - 1][i];
            for (int j = 1; j < 10; j++) dp[actLog][i] = dp[actLog - 1][ dp[actLog][i] ];
        }
    }

    fin >> t;
    for (i = 1; i <= t; i++) {
        fin >> x >> y;

        if (lvl[y] < lvl[x]) swap(x, y);

        int how = lvl[y] - lvl[x];
        y = goUp(y, how);
        if (x == y)
            printf("DA\n");
        else
            printf("NU\n");
    }


    return 0;
}

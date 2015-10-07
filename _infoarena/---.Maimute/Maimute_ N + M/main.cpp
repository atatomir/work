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

int n, i, x, y;
vector<int> list[maxN];

bool us[maxN];
int dim;
int l_pos[maxN], r_pos[maxN];

void dfs(int node) {
    us[node] = true;

    l_pos[node] = ++dim;

    for (auto who : list[node]) {
        if (us[who]) continue;
        dfs(who);
    }

    r_pos[node] = dim;
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

    dfs(1);

    int m;
    fin >> m;
    for (i = 1; i <= m; i++) {
        fin >> x >> y;

        if (l_pos[y] < l_pos[x]) swap(x, y);

        if (l_pos[x] <= l_pos[y] && l_pos[y] <= r_pos[x])
            printf("DA\n");
        else
            printf("NU\n");
    }


    return 0;
}

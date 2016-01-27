#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 250011
#define maxK 1024
#define piii pair< int, pair<int, int> >

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

int n, m, x, y, i, s, d, c;
vector< piii > aux;
bool us[maxN];
vector<int> list[maxN];

void dfs(int node) {
    us[node] = true;
    for (auto to : list[node])
        if (!us[to])
            dfs(to);
}

int main()
{
    Buffer fin("pscnv.in", 1 << 20);
    freopen("pscnv.out","w",stdout);

    fin >> n >> m >> s >> d;
    for (i = 1; i <= m; i++) {
        fin >> x >> y >> c;
        aux.pb(mp(c, mp(x, y)));
    }

    sort(aux.begin(), aux.end());
    us[s] = true;

    for (auto now : aux) {
        bool active = false;

        list[now.second.first].pb(now.second.second);
        list[now.second.second].pb(now.second.first);

        if (us[now.second.first] || us[now.second.second])
            dfs(now.second.first);

        if (us[d]) {
            printf("%d", now.first);
            return 0;
        }
    }


    return 0;
}

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
vector< pair<int, int> > list[maxN];
bool unlocked[maxN];
vector<int> work[maxK];
int best[maxN];
int pos[maxK];

int main()
{
    Buffer fin("pscnv.in", 1 << 20);
    freopen("pscnv.out","w",stdout);

    fin >> n >> m >> s >> d;
    for (i = 1; i <= m; i++) {
        fin >> x >> y >> c;
        list[x].pb(mp(y, c));
        list[y].pb(mp(x, c));
    }

    for (i = 1; i <= n; i++)
        best[i] = 1001;

    work[0] = {s};
    for (i = 0; unlocked[d] == false; ) {
        while (pos[i] == work[i].size()) i++;

        int node = work[i][pos[i]++];

        if (node == d) {
            printf("%d", i);
            return 0;
        }

        if (unlocked[node]) continue;
        unlocked[node] = true;
        for (auto to : list[node])
            if (!unlocked[to.first] && best[to.first] > max(i, to.second))
                work[ max(i, to.second) ].pb(to.first);
    }


    return 0;
}

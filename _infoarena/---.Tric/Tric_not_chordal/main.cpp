#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <unordered_map>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 100011
#define def 100001LL

class Buffer {
    public:
        Buffer(string name, int _dim) {
            freopen(name.c_str(), "r", stdin);
            dim = _dim;
            data.resize(dim + 17);
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

int n, m, i, j, x, y;
vector<int> list[maxN];
int gr[maxN];
unordered_map<ll, bool> H;
bool dead[maxN];
int ans;

int limit;
bool added[maxN];
queue<int> Heap; //! limited at sqrt


void rm_trash(int node) {
    int i;
    int pos = 0;

    for (i = 0; i < list[node].size(); i++)
        if (!dead[list[node][i]])
            list[node][pos++] = list[node][i];

    list[node].resize(pos);
}


int main()
{
    Buffer fin("tric.in", 1 << 20);
    freopen("tric.out","w",stdout);

    fin >> n >> m;
    for (i = 1; i <= m; i++) {
        fin >> x >> y;
        x++; y++;

        list[x].pb(y); gr[x]++;
        list[y].pb(x); gr[y]++;
        H[ def * x  + y ] = H[ y * def + x ] = true;
    }

    limit = sqrt(m) + 1;
    for (i = 1; i <= n; i++)
        if (gr[i] <= limit)
            Heap.push(i), added[i] = true;

    while (!Heap.empty()) {
        int node = Heap.front(); Heap.pop();
        dead[node] = true;
        rm_trash(node);

        for (i = 0; i < list[node].size(); i++)
            for(j = i + 1; j < list[node].size(); j++)
                if (H[def * list[node][i] + list[node][j]])
                    ans++;

        for (int to : list[node])
            if (--gr[to] <= limit && added[to] == false)
                Heap.push(to), added[to] = true;
    }

    printf("%d\n", ans);


    return 0;
}

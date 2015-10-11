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
Buffer fin("arbciclu.in", 1 << 20);

struct hash_func {
    size_t operator()(const pair<int, int> who)const {
        return (who.first * 17 + who.second) % 666013;
    }
};

int n, i, m, x, y, t;
vector<int> list[maxN];
int gr[maxN];
queue<int> Q;
unordered_map<pair<int, int>, bool, hash_func> Hash;

bool us[maxN];
bool Added[maxN];
bool isGood;

void init() {
    for (int i = 1; i <= n; i++) list[i].clear();
    memset(gr, 0, sizeof(gr));
    memset(us, 0, sizeof(us));
    memset(Added, 0, sizeof(Added));
    while (!Q.empty()) Q.pop();
    Hash.clear();
}

int main()
{
    //freopen("arbciclu.in","r",stdin);
    freopen("arbciclu.out","w",stdout);

    for (fin >> t; t > 0; t--) {
        fin >> n >> m;
        isGood = true;
        init();

        for (i = 1; i <= m; i++) {
            fin >> x >> y;
            list[x].pb(y);
            list[y].pb(x);

            gr[x]++;
            gr[y]++;
            Hash[mp(x, y)] = true;
            Hash[mp(y, x)] = true;
        }

        for (i = 1; i <= n; i++) {
            if (gr[i] <= 1)
                isGood = false;
            if (gr[i] == 2) {
                Q.push(i);
                Added[i] = true;
            }
        }

        while (!Q.empty()) {
            int node = Q.front(); Q.pop();
            us[node] = true;

            for (int i = 0; i < list[node].size(); i++) {
                if (us[list[node][i]] == false) continue;
                list[node][i] = list[node][ list[node].size() -1 ];
                list[node].pop_back();
                i--;
                continue;
            }

            if (list[node].size() <= 1) continue;

            int n1 = list[node][0];
            int n2 = list[node][1];

            if (Hash[mp(n1, n2)] == false) {
                gr[n1]++;
                gr[n2]++;
                Hash[mp(n1, n2)] = true;
                Hash[mp(n2, n1)] = true;
                list[n1].pb(n2);
                list[n2].pb(n1);
            }

            gr[n1]--;
            gr[n2]--;
            gr[node] = 0;

            if (gr[n1] == 2 && !Added[n1]) {
                Added[n1] = true;
                Q.push(n1);
            }
            if (gr[n2] == 2 && !Added[n2]) {
                Added[n2] = true;
                Q.push(n2);
            }
        }

        for (i = 1; i <= n; i++)
            if (gr[i] >= 2)
                isGood = false;

        int aux = 0;
        for (i = 1; i <= n; i++)
            if (gr[i] == 1)
                aux++;
        if (aux > 2) isGood = false;

        if (isGood)
            printf("YES\n");
        else
            printf("NO\n");
    }


    return 0;
}

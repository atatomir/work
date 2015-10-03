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
#define inf 1000000000000LL

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


struct Edge {
    int to, d, c;

    Edge() {}
    Edge(int _to, int _d, int _c) {
        to = _to;
        d = _d;
        c = _c;
    }
};

int n, i, x, y, cost, dist;
vector< Edge > list[maxN];

bool us[maxN];
long long dp_time[maxN];
long long dp_pay[maxN];
long long pay_inc[maxN];

void dfs(int node) {
    us[node] = true;
    pay_inc[node] = inf;

    for (int i = 0; i < list[node].size(); i++) {
        int goTo = list[node][i].to;

        if (us[ goTo ]) {
            list[node][i] = list[node][ list[node].size() - 1 ];
            list[node].pop_back();
            i--;
            continue;
        }

        dfs(goTo);
        dp_time[goTo] += list[node][i].d;
        dp_time[node] = max(dp_time[node], dp_time[goTo]);
        dp_pay[node] += dp_pay[goTo];

        pay_inc[node] += min(pay_inc[goTo], 1LL * list[node][i].c);
    }

    if(list[node].size() > 0) pay_inc[node] -= inf;

    for (auto who : list[node])
        dp_pay[node] += 1LL * min(1LL * who.c, pay_inc[who.to]) * (dp_time[node] - dp_time[who.to]);
}

int main()
{
    Buffer fin("arb2.in", 1 << 20);
    freopen("arb2.out","w",stdout);

    fin >> n;
    for (i = 1; i < n; i++) {
        fin >> x >> y >> dist >> cost;
        list[x].pb(Edge(y, dist, cost));
        list[y].pb(Edge(x, dist, cost));
    }

    dfs(1);
    printf("%lld", dp_pay[1]);

    cerr << dp_pay[1] << ' ' << dp_time[1];

    return 0;
}

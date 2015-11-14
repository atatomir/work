#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 500011
#define inf 1000000

class Buffer {
    public:
        Buffer(string name, int _dim) {
            freopen(name.c_str(), "r", stdin);
            dim = _dim;
            data.resize(dim);

            reFill();
        }

        Buffer& operator>>(int &who) {
            while (!isDigit(data[pos]))
                if (++pos == dim) reFill();
            who = 0;
            while (isDigit(data[pos])) {
                who = who * 10 + data[pos] - '0';
                if (++pos == dim) reFill();
            }
            return *this;
        }

    private:
        int dim, pos;
        vector<char> data;

        bool isDigit(char c) {
            return ('0' <= c && c <= '9');
        }

        void reFill() {
            pos = 0;
            memset(&data[0], 0, dim);
            fread(&data[0], 1, dim, stdin);
        }
};

Buffer fin("mate.in", 1 << 20);

//!-----------------------------------

int n, i, x;
vector< pair<int, int> > st[maxN]; //! pos, val

int cnt[maxN];
int aux[maxN];
int from[maxN];
int ll[maxN];
int rr[maxN];

int last[maxN];
int ans;

void addStack(int pos, int x, int v) {
    if (st[x].empty()) {
        st[x].pb( mp(pos, v) );
        return;
    }

    if (st[x][ st[x].size() - 1 ].second > v)
        st[x].pb( mp(pos, v) );
}

int binary(int id, int v) {
    int ans = -1;

    for (int step = 1 << 19; step > 0; step >>= 1)
        if (ans + step < st[id].size() - 1)
            if (st[id][ ans + step ].second > v)
                ans += step;
    return st[id][ ans + 1 ].first + 1;
}

int main()
{
    //freopen("mate.in","r",stdin);
    freopen("mate.out","w",stdout);

    ans = 1;

    fin >> n;
    for (i = 1; i <= n; i++) {
        fin >> x;

        cnt[x]++;

        int how = cnt[x];
        aux[i] = 2 * how - i;
        addStack(i - 1, x, aux[i] - 1);

        from[i] = binary(x, aux[i]);

        ll[i] = last[ x ];
        last[x] = i;
        rr[ ll[i] ] = i;
    }

    for (i = 1; i <= n; i++)
        if (rr[i] == 0)
            rr[i] = n + 1;

    for (int p2 = 1; p2 <= n; p2++) {
        int p1 = from[p2];

        int delta = aux[p2] - aux[p1] + 1;
        int rez = (rr[p2] - p2 - 1) + (p1 - ll[p1] - 1);

        ans = max(ans, (p2 - p1 + 1) + min(delta, rez) );
    }

    printf("%d", ans);

    return 0;
}

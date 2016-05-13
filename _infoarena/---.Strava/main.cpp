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

#define maxN 100011
#define base 10000LL

class Buffer {
    public:
        Buffer(string name, int _dim) {
            freopen(name.c_str(), "r", stdin);
            dim = _dim;
            data.resize(dim + 17);
            refill();
        }

        template<typename T>
        Buffer& operator>>(T& dest) {
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

Buffer fin("strava.in", 1 << 20);

struct segm {
    ll x1, y1, x2, y2;
    ll id;

    pair<ll, ll> read_lf() {
        static ll a, b;

        fin >> a >> b; a++;
        return mp(a * base + b, a);
    }

    void read() {
        auto aux = read_lf();
        x1 = aux.first;

        aux = read_lf();
        y1 = aux.first;

        aux = read_lf();
        x2 = aux.first;

        aux = read_lf();
        y2 = aux.first;
    }

    ll dist(ll x1, ll y1, ll x2, ll y2) {
        return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
    }

    bool same(const segm& who) {
        if (dist(x1, y1, who.x1, who.y1) > base * base) return false;
        if (dist(x2, y2, who.x2, who.y2) > base * base) return false;
        return true;
    }

};

int t, ti;
int n, i, j;
segm work[maxN];
int ord[maxN];
int ans;


bool cmp(int a, int b) {
    return work[a].x1 < work[b].x1;
}




int main()
{
    //freopen("strava.in","r",stdin);
    freopen("strava.out","w",stdout);

    fin >> t;
    for (ti = 1; ti <= t; ti++) {
        fin >> n;
        for (i = 1; i <= n; i++) {
            work[i].read();
            ord[i] = i;
        }

        ans = 0;

        sort(ord + 1, ord + n + 1, cmp);
        for (i = 1; i <= n; i++)
            for (j = i + 1; work[ord[j]].x1 - work[ord[i]].x1 <= base && j <= n; j++)
                if (work[ord[j]].same(work[ord[i]]))
                    ans++;



        cerr << ans;
        printf("%d\n", ans);
    }


    return 0;
}

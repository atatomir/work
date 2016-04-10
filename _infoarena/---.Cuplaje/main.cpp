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

#define maxN 200011


class Buffer {
    public:
        Buffer(string name, int _dim) {
            freopen(name.c_str(), "r", stdin);
            dim = _dim;
            data.resize(dim + 5);
            refill();
        }

        template<typename T>
        Buffer& operator>>(T &dest) {
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

Buffer fin("cuplaje.in", 1 << 22);


int n, m, i, j, x;
int boy[maxN];
vector< pair<int, int> > girl;
int ans;


int aib[maxN];

int zrs(int x) {
    return (x ^ (x - 1)) & x;
}

void add(int pos, int val) {
    while (pos <= m) {
        aib[pos] += val;
        pos += zrs(pos);
    }
}

int sum(int pos) {
    int ans = 0;
    while (pos) {
        ans += aib[pos];
        pos -= zrs(pos);
    }
    return ans;
}

int lower(int val) {
    int ans = 0;
    val--;

    for (int step = (1 << 18); step; step >>= 1) {
        if (ans + step <= m)
            if (aib[ans + step] <= val)
                ans += step, val -= aib[ans];
    }

    return ans + 1;
}



int main()
{
    //freopen("cuplaje.in","r",stdin);
    freopen("cuplaje.out","w",stdout);

    fin >> n >> m;
    for (i = 1; i <= n; i++) fin >> boy[i];
    for (j = 1; j <= m; j++) {
        fin >> x;
        girl.pb(mp(x, j));
    }

    sort(girl.begin(), girl.end());
    for (i = n; i > 0; i--) {
        while (!girl.empty()) {
            if (girl.back().first < i) break;
            add(girl.back().second, + 1);
            girl.pop_back();
        }

        int sumi = sum(boy[i]);
        if (sumi == 0) continue;
        ans++;

        int pos = lower(sumi);
        add(pos, -1);

        //cerr << i << ' ' << pos << '\n';
    }

    printf("%d", ans);

    return 0;
}

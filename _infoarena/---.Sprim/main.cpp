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
#define maxValue 1000000LL

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
                if(++pos == dim) reFill();
            }
            dest = 0;
            while (isDigit(data[pos])) {
                dest = dest * 10 + data[pos] - '0';
                if(++pos == dim) reFill();
            }
            return *this;
        }

    private:
        int dim, pos;
        vector<char> data;

        void reFill() {
            pos = 0;
            memset(&data[0], 0, sizeof(data));
            fread(&data[0], 1, dim, stdin);
        }

        bool isDigit(char c) {
            return ('0' <= c) && (c <= '9');
        }
};

int n, i, j;
int vv[maxN];
vector<int> divs[maxN];
int last[maxValue + 11];
bool ciur[maxValue + 11];
vector<int> ciur_aux;

long long ans;
int dp[maxN];

void make_ciur() {
    ciur[1] = true;

    for (long long i = 2; i <= maxValue; i++) {
        if (ciur[i]) continue;
        ciur_aux.pb(i);

        for (long long j = i * i; j <= maxValue; j += i) ciur[j] = true;
    }
}

void make_divs(int v, int id) {
    int vv = v;
    for (auto who : ciur_aux) {
        if ( who * who > v) break;
        if (v % who == 0) {
            divs[id].pb(who);
            divs[id].pb(vv/who);
            while (v % who == 0) v /= who;
        }
    }
    if (v != 1) divs[id].pb(v);
}

int main()
{
    Buffer fin("sprim.in", 1 << 20);
    freopen("sprim.out","w",stdout);

    make_ciur();

    fin >> n;
    for (i = 1; i <= n; i++) {
        fin >> vv[i];
        make_divs(vv[i], i);
    }

    for (i = 1; i <= n; i++) {
        int pos = dp[i - 1];

        for (auto who : divs[i]) pos = max(pos, last[who]);
        for (auto who : divs[i]) last[who] = i;

        dp[i] = pos;
        ans += 0LL + i - pos;
    }

    printf("%lld", ans - n);

    return 0;
}

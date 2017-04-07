#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stack>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN (1 << 19) + 3

class Buffer {
    public:
        Buffer(string name, int _dim) {
            if (name != "")
                freopen(name.c_str(), "r", stdin);
            dim = _dim;
            data.resize(dim + 11);
            refill();
        }

        template<typename T>
        Buffer& operator>>(T &dest) {
            T sign = +1;
            dest = 0;

            while (!is_digit(data[pos]) && data[pos] != '-')
                if (++pos == dim)
                    refill();

            if (data[pos] == '-') {
                sign = -1;
                if (++pos == dim)
                    refill();
            }

            while (is_digit(data[pos])) {
                dest = dest * 10 + data[pos] - '0';
                if (++pos == dim)
                    refill();
            }

            dest *= sign;
            return *this;
        }


    private:
        int pos, dim;
        vector<char> data;

        bool is_digit(char c) {
            return '0' <= c && c <= '9';
        }

        void refill() {
            memset(&data[0], 0, dim);
            fread(&data[0], 1, dim, stdin);
            pos = 0;
        }
};

int n, c, m, i, op, p, l, cl, cr;
int len[maxN];
unsigned char col[maxN], last[maxN];

int main()
{
    Buffer fin("culori2.in", 1 << 19);
    freopen("culori2.out","w",stdout);

    fin >> n >> c >> m;
    len[0] = n; col[0] = c;


    for (i = 1; i <= m; i++) {
        fin >> op >> p;

        if (op == 0) {
            cout << (int)col[p] << '\n';
        }

        if (op == 1) {
            col[p] = last[ p + len[p] ];
            len[p] += len[p + len[p]];
        }

        if (op == 2) {
            fin >> l >> cl >> cr;
            last[p + l] = col[p];
            col[p] = cl; col[p + l] = cr;
            len[p + l] = len[p] - l;
            len[p] = l;
        }
    }

    return 0;
}

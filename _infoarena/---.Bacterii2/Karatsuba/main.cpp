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

#define def 32768
#define maxDim (2 * def + 22)

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


int t, ti;
int n, m, i, x, step;
int act_dim;

int pos;
int a[maxDim];
int b[maxDim];
int r[maxDim * 6];
int mem[maxDim * 10];



int* alloc(int dim) {
    int *rez = &mem[pos];
    pos += dim;
    return rez;
}

void dealloc(int dim) {
    pos -= dim;
}

void print(int *pos, int d) {
    for (int i = 0; i < d; i++) cerr << pos[i] << ", ";
    cerr << '\n';
}



/* Karatsuba algorithm */
void solve(int *a, int *b, int *r, int d) {
    int i;

    if (d == 2) {
        r[0] = a[0] * b[0];
        r[1] = a[0] * b[1] + a[1] * b[0];
        r[2] = a[1] * b[1];
        r[3] = 0;
        return;
    }

    int *a0 = &a[0], *a1 = &a[d / 2];
    int *b0 = &b[0], *b1 = &b[d / 2];
    int *z0 = &r[0], *z1 = &r[2 * d], *z2 = &r[d];
    int *asum = alloc(d / 2);
    int *bsum = alloc(d / 2);

    for (i = 0; i < d / 2; i++) {
        asum[i] = a0[i] + a1[i];
        bsum[i] = b0[i] + b1[i];
    }

    solve(a0, b0, z0, d / 2);
    solve(a1, b1, z2, d / 2);
    solve(asum, bsum, z1, d / 2);
    dealloc(d);


    for (i = 0; i < d; i++) z1[i] -= z0[i] + z2[i];
    for (i = 0; i < d; i++) z0[i + d / 2] += z1[i];
}



int main()
{
    Buffer fin("bacterii2.in", 1 << 20);
    freopen("bacterii2.out","w",stdout);

    fin >> t;
    for (ti = 1; ti <= t; ti++) {

        memset(a, 0, sizeof(a));
        memset(b, 0, sizeof(b));
        memset(r, 0, sizeof(r));
        act_dim = 2;

        fin >> n;
        for (i = 1; i <= n; i++) {
            fin >> x;
            a[x - 1]++;

            act_dim = max(act_dim, x);
        }

        fin >> m;
        for (i = 1; i <= m; i++) {
            fin >> x;
            b[x - 1]++;

            act_dim = max(act_dim, x);
        }

        for (step = 2; step < act_dim; step <<= 1);

        solve(a, b, r, step);
        for (i = 0; i < 2 * step; i++)
            if (r[i])
                printf("%d %d\n", i + 2, r[i]);

        printf("\n");
    }


    return 0;
}

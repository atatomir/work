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

#define maxDim (1 << 20 + 1)

class Buffer {
    public:
        Buffer(string name, int _dim) {
            freopen(name.c_str(), "w", stdout);
            dim = _dim;
            pos = 0;
            data.resize(dim + 5);
        }

        Buffer& operator<<(char c) {
            data[pos++] = c;
            if (pos == dim) push_it();

            return *this;
        };

        void push_it() {
            fwrite(&data[0], 1, pos, stdout);
            pos = 0;
        }

    private:
        int dim, pos;
        vector<char> data;


};

Buffer fout("bile3.out", 1 << 13);

int n, k, i, cnt;
int vals[maxDim];
int poww[33];

//int last_val;

void print_bin(int v) {
    for (int i = 0; i < n; i++) {
        if (v & (1 << i)) {
            if (i == 20 - 1)
                fout << '2' << '0';
            else
            if (i >= 10 - 1)
                fout << '1' << '0' + (i + 1) % 10;
            else
                fout << '0' + (i + 1) % 10;

            fout << ' ';
        }
    }

    fout << '\n';
}

bool good(int a, int b) {
    if (a == 0) return true;

    int diff = 0;
    for (int i = 0; i < n; i++)
        if ( (a & (1 << i)) != (b & (1 << i)) )
            diff++;

    return diff == 2;
}

int main()
{
    freopen("bile3.in","r",stdin);
    //freopen("bile3.out","w",stdout);

    scanf("%d%d", &n, &k);

    cnt = 1;
    vals[1] = 1;

    for (i = 0; i <= 20; i++) poww[i] = 1 << i;

    for (cnt = 2; cnt <= n; cnt++) {
        int last = (1 << (cnt - 1));
        int bit = 1 << (cnt - 1);

        for (i = 1; i <= last; i++)
            vals[last + (last - i + 1)] = vals[i] ^ bit;
    }

    cnt = 1 << n;
    for (i = 1; i <= cnt; i++) {
        int aux = vals[i];

        int bits = 0;
        while (aux) {
            bits++;
            aux &= (aux - 1);
        }

        if (bits == k) {
            print_bin(vals[i]);
        }
    }

    fout.push_it();

    return 0;
}

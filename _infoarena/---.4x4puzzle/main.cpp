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

#define maxN 55

class Buffer {
    public:
        Buffer(string name, int _dim) {
            freopen(name.c_str(), "r", stdin);
            dim = _dim;
            data.resize(dim + 11);
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
            memset(&data[0], 0, dim);
            fread(&data[0], 1, dim, stdin);
            pos = 0;
        }
};

int q, qq, i, j, cnt;
int v[maxN];

int abss(int x) {
    if (x < 0) return -x;
    return x;
}

int main()
{
    Buffer fin("4x4puzzle.in", 1 << 20);
    //freopen("4x4puzzle.in","r",stdin);
    freopen("4x4puzzle.out","w",stdout);

    fin >> q;
    for (qq = 1; qq <= q; qq++) {
        for (i = 1; i <= 16; i++) fin >> v[i];
        reverse(v + 5, v + 9);
        reverse(v + 13, v + 17);

        for (i = 1; v[i] != 0; i++);
        for (j = i; j < 16; j++) v[j] = v[j + 1];

        cnt = 0;
        for (i = 1; i <= 14; i++)
            for (j = i + 1; j <= 15; j++)
                if (v[i] > v[j])
                    cnt++;

        if (cnt % 2 == 1)
            printf("DA\n");
        else
            printf("NU\n");
    }


    return 0;
}

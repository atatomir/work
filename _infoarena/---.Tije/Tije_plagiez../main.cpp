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

#define maxN 111
//#define DEBUG

class Buffer {
    public:
        void flush() {
            fwrite(&data[0], 1, pos, stdout);
            pos = 0;
        }

        Buffer(string name, int _dim) {
            freopen(name.c_str(), "w", stdout);
            dim = _dim;
            data.resize(dim + 17);
            pos = 0;
            flush();
        }

        Buffer& operator<<(char c) {
            data[pos++] = c;
            if (pos >= dim) flush();

            return *this;
        }

        Buffer& operator<<(int a) {
            aux.clear();
            while (a) {
                aux.pb('0' + a % 10);
                a /= 10;
            }

            reverse(aux.begin(), aux.end());
            for (char e : aux) data[pos++] = e;
            if (pos >= dim) flush();

            return *this;
        }

    private:
        int dim, pos;
        vector<char> data;
        vector<char> aux;
};

Buffer fout("tije.out", 1 << 20);



int n, m, i, j, step;



int main()
{
    freopen("tije.in","r",stdin);

    scanf("%d", &n);
    if (n == 1) return 0;

    for (step = n - 1; step >= 0; step--) {
        for (i = 1; i <= step + 1; i++)
            fout << 1 << ' ' << n + 1 << '\n';

        for (i = 2; i <= n + 1; i++)
            for (j = 1; j <= step; j++)
                fout << i << ' ' << i - 1 << '\n';
    }

    for (i = 1; i <= n; i++) fout << n + 1 << ' ' << 1 << '\n';

    fout.flush();

    return 0;
}

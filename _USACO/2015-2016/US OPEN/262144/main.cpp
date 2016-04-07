#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 263000
#define maxK 62

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

Buffer fin("262144.in", 1 << 22);

int n, i, j, pos;
int v[maxN];
int ans;

//unordered_map<int, int> H;
int H[maxN][maxK];


int compress(int pos, int how) {
    return (pos << 10) | how;
}

int main()
{
    freopen("262144.out","w",stdout);

    fin >> n;
    for (i = 1; i <= n; i++) fin >> v[i];

    for (i = 1; i <= n; i++) {
        H[i][v[i]] = i;
        j = v[i];

        pos = i - 1;
        while (pos > 0) {
            if (H[pos][j] == 0) break;
            pos = H[pos][j] - 1;
            H[i][j + 1] = pos + 1;

            j++;
            ans = max(ans, j);
        }

        ans = max(ans, v[i]);
    }

    printf("%d", ans);


    return 0;
}

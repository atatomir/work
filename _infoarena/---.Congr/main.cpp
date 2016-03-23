#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxN 300011

class Buffer {
    public:
        Buffer(string name, int _dim) {
            freopen(name.c_str(), "r", stdin);
            dim = _dim;
            data.resize(dim + 5);
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

Buffer fin("congr.in", 1 << 22);

int n, i, x, y;
vector<int> v;
vector<int> A, B;

ll sum;
int cnt;


int main()
{
    srand(time(NULL));

    //freopen("congr.in","r",stdin);
    freopen("congr.out","w",stdout);

    fin >> n;
    for (i = 1; i <= n; i++) {
        fin >> x;
        v.pb(x);
        A.pb(v.size() - 1);

        sum += 1LL * x;
    }

    for (i = 1; i < n; i++) {
        fin >> x;
        v.pb(x);
        B.pb(v.size() - 1);
    }

    while (sum % n != 0) {
        x = rand() % n;
        y = rand() % (n - 1);

        sum -= 1LL * v[A[x]];
        sum += 1LL * v[B[y]];

        swap(A[x], B[y]);

        cnt++;
    }


    sort(A.begin(), A.end());
    for (int e : A)
        printf("%d ", e + 1);

    cerr << "done : " << cnt;

    return 0;
}

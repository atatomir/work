#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <assert.h>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 53

#define big_dim 11
#define base 10000
int aux[big_dim];
class big_integer {
    public:
        int dim;
        int data[big_dim];

        big_integer() {
            reset();
        }

        void set(int init) {
            data[1] = init;
        }

        void operator=(const big_integer& who) {
            dim = who.dim;
            memcpy(data, who.data, sizeof(data));
        }

        void operator+=(const big_integer& who) {
            dim = max(dim, who.dim);
            for (int i = 1; i <= dim; i++) {
                data[i] += who.data[i];
                if (data[i] >= base) {
                    data[i + 1]++;
                    data[i] -= base;
                }
            }
            if (data[dim + 1] != 0) dim++;

            assert(data[dim] != 0 || dim == 1);
            assert(dim < big_dim);
        }

        void operator *=(const big_integer& who) {
            memcpy(aux, data, sizeof(data));
            memset(data, 0, sizeof(data));

            for (int i = 1; i <= dim; i++)
                for (int j = 1; j <= who.dim; j++)
                    data[i + j - 1] += aux[i] * who.data[j];

            dim = dim + who.dim - 1;
            for (int i = 1; i <= dim; i++) {
                data[i+1] += data[i] / base;
                data[i] %= base;

                if (data[dim + 1] != 0) dim++;
            }

            while (dim > 1 && data[dim] == 0) dim--;
            //! daca inmultesti cu 0-uri

            assert(data[dim] != 0 || dim == 1);
            assert(dim < big_dim);
        }

        void print() {
            printf("%d", data[dim]);
            for (int i = dim - 1; i > 0; i--) print_number(data[i]);
            printf("\n");
        }

        void reset() {
            dim = 1;
            memset(data, 0, sizeof(data));
        }

    private:
        void print_number(int nr) {
            int tmp = base / 10;
            while (tmp > nr) {
                printf("0");
                tmp /= 10;
            }
            if (tmp != 0) printf("%d",nr);
        }
};

int n, k, i, j;
big_integer dp[maxN][maxN];
big_integer use;

int main()
{
    freopen("gard3.in","r",stdin);
    freopen("gard3.out","w",stdout);

    scanf("%d%d", &n, &k);

    dp[3][0].set(1);
    for (int nn = 4; nn <= n; nn++) {
        dp[nn][0].set(1);

        for (int kk = 1; kk <= nn - 3; kk++) {
            dp[nn][kk] += dp[nn - 1][kk];
            dp[nn][kk] += dp[nn - 1][kk - 1];

            //! for i == 3
            dp[nn][kk] += dp[nn - 1][kk - 1];

            //! for i == nn - 1
            if(nn - 1 != 3) {
                dp[nn][kk] += dp[nn - 2][kk - 1];
                if (kk > 1)
                    dp[nn][kk] += dp[nn - 2][kk - 2];
            }

            for (i = 4; i <= nn - 2; i++) {
                for (j = 0; j <= kk - 1; j++) {
                    use  = dp[i - 1][j];
                    if (j != 0) use += dp[i - 1][j - 1];
                    use *= dp[nn - i + 2][kk - j - 1];

                    dp[nn][kk] += use;
                }
            }
        }
    }

    dp[n][k - 1].print();


    return 0;
}

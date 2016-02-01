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

#define max_dim 2300
#define base 100000
class big_number {
    public:
        int dim;
        int data[max_dim];

        void init(int x) {
            dim = 1;
            memset(data, 0, sizeof(data));
            data[1] = x;
            flat();
        }

        void flat() {
            while (data[dim] >= base) {
                data[dim + 1] = data[dim] / base;
                data[dim] %= base;
                dim++;
            }
        }

        void operator+=(big_number &who) {
            dim = max(dim, who.dim);
            for (int i = 1; i <= dim; i++) {
                data[i] += who.data[i];
                if (data[i] >= base) {
                    data[i] -= base;
                    data[i + 1]++;
                }
            }

            if (data[dim + 1]) dim++;
        }

        void operator*=(int x) {
            int i;

            for (i = 1; i <= dim; i++)
                data[i] *= x;

            for (i = 1; i <= dim; i++) {
                data[i + 1] += data[i] / base;
                data[i] %= base;
                if (data[dim + 1]) dim++;
            }
        }

        void print() {
            printf("%d", data[dim]);

            for (int i = dim - 1; i > 0; i--) {
                int val = base / 10;
                while (data[i] < val) {
                    printf("0");
                    val /= 10;
                }

                if (val == 0) continue;
                printf("%d", data[i]);
            }
            printf("\n");
        }
};

int n, i;
big_number sum; //! a[1] + a[2] + ..
big_number aux; //! a[1] * (i - 1) * a[2] * (i - 2) + ..

big_number now;
big_number ans;

int main()
{
    freopen("bombar.in","r",stdin);
    freopen("bombar.out","w",stdout);

    scanf("%d", &n);

    sum.init(1);
    aux.init(1);
    ans.init(n);

    for (i = 2; i <= n; i++) {
        now = aux;
        now *= 2;

        sum += now;
        aux += sum;

        now *= (n - i + 1);
        ans += now;
    }

    ans.print();
    cerr << ans.dim;

    return 0;
}

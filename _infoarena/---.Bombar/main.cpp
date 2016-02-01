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

#define max_dim 7000
#define base 1000

int data_rez[max_dim];

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

        void operator*=(big_number &who) {
            int i, j;

            memcpy(data_rez, data, sizeof(data));
            memset(data, 0, sizeof(data));

            for (i = 1; i <= dim; i++)
                for (j = 1; j <= who.dim; j++)
                    data[i + j - 1] += data_rez[i] * who.data[j];

            dim += who.dim - 1;
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

big_number rez[2][2];
big_number rez2[2][2];
big_number rez_aux;

struct Matrix {
    int n = 2;
    int i, j, k;
    big_number data[2][2];

    void operator*=(Matrix& who) {
        memcpy(rez, data, sizeof(data));
        memcpy(rez2, who.data, sizeof(data));

        data[0][0].init(0);
        data[0][1].init(0);
        data[1][0].init(0);
        data[1][1].init(0);

        for (k = 0; k < 2; k++)
            for (i = 0; i < 2; i++)
                for (j = 0; j < 2; j++) {
                    rez_aux = rez[i][k];
                    rez_aux *= rez2[k][j];

                    data[i][j] += rez_aux;
                }


    }
};

int n, i;
Matrix aux, ans;
big_number now;

void powww() {
    ans = aux;
    n--;

    while (n) {
        if (n & 1) ans *= aux;
        n >>= 1;
        aux *= aux;
    }
}

int main()
{
    freopen("bombar.in","r",stdin);
    freopen("bombar.out","w",stdout);

    scanf("%d", &n);

    aux.data[0][0].init(1);
    aux.data[0][1].init(1);
    aux.data[1][0].init(2);
    aux.data[1][1].init(3);

    if (n == 1) {
        printf("1");
        return 0;
    }

    n--;
    powww();

    now = ans.data[0][1];
    now += ans.data[1][1];

    cerr << now.dim;
    now.print();

    return 0;
}

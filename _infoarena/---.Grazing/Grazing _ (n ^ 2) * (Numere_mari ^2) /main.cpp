#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

#define pb push_back
#define mp make_pair

#define big_dim 73
#define base 1000000000LL
#define ll long long

ll aux[big_dim];
int dimi;

class big_number {
    public:
        int dim, i, j;
        ll data[big_dim];

        void init(int v) {
            memset(data, 0, sizeof(data));
            dim = 1;
            data[1] = v;
        }

        void operator+=(const big_number& who) {
            dim = max(dim, who.dim);
            for (i = 1; i <= dim; i++)
                data[i] += who.data[i];

            for (i = 1; i <= dim; i++) {
                data[i + 1] += data[i] / base;
                data[i] %= base;
            }
            if (data[dim + 1]) dim++;
        }

        void operator*=(const big_number& who) {
            memcpy(aux, data, sizeof(data));
            dimi = dim;
            init(0);

            for (i = 1; i <= dimi; i++)
                for (j = 1; j <= who.dim; j++)
                    data[i + j - 1] += aux[i] * who.data[j];


            dim = dimi + who.dim - 1;
            for (i = 1; i <= dim; i++) {
                data[i + 1] += data[i] / base;
                data[i] %= base;

                if (data[dim + 1]) dim++;
            }
        }

        void operator*=(int v) {
            for (i = 1; i <= dim; i++)
                data[i] *= v;

            for (i = 1; i <= dim; i++) {
                data[i + 1] += data[i] / base;
                data[i] %= base;

                if (data[dim + 1]) dim++;
            }

            while(dim > 1 && data[dim] == 0) dim--;
        }

        void operator=(big_number& who) {
            dim = who.dim;
            memcpy(data, who.data, sizeof(data));
        }

        void print() {
            printf("%lld", data[dim]);

            for (i = dim - 1; i > 0; i--) {
                for (int step = base / 10; step > data[i]; step /= 10)
                    printf("0");

                if(data[i]) printf("%lld", data[i]);
            }
        }
};

#define maxN 311

big_number comb[maxN][maxN];
big_number fact[maxN];

int n, i, l;
big_number dp[maxN];
big_number aux_big;

void preproc() {
    int i, j;

    comb[1][1].init(1); comb[1][0].init(1);
    comb[1][2].init(0);
    for (i = 2; i <= n; i++) {
        comb[i][0].init(1);
        comb[i][i + 1].init(0);
        for (j = 1; j <= i; j++) {
            comb[i][j] = comb[i - 1][j];
            comb[i][j] += comb[i - 1][j - 1];
        }
    }

    //! fact without 2..
    fact[1].init(1);
    fact[2].init(1);
    for (i = 3; i <= n; i++) {
        fact[i] = fact[i - 1];
        fact[i] *= i;
    }

}

int main()
{
    freopen("grazing.in", "r", stdin);
    freopen("grazing.out", "w", stdout);

    scanf("%d", &n);
    preproc();

    dp[0].init(1);
    dp[1].init(1); dp[2].init(2);

    for (i = 3; i <= n; i++) {
        dp[i] = dp[i - 1]; //! separated node..

        for (l = 3; l <= i; l++) {
            aux_big = comb[i - 1][l - 1];
            aux_big *= fact[l - 1];
            aux_big *= dp[i - l];

            if (l % 3 == 0)
                aux_big *= l;
            else
                aux_big *= l + 1;

            dp[i] += aux_big;
        }

        l = 2;
        aux_big = comb[i - 1][l - 1];
        aux_big *= fact[l];
        aux_big *= dp[i - l];

        dp[i] += aux_big;
    }

    dp[n].print();

    return 0;
}

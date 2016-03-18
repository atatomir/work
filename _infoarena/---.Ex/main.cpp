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
#define maxDim 150
#define base 10

struct big_num {
    int dim;
    int data[maxDim];

    void init(int v) {
        dim = 1;
        memset(data, 0, sizeof(data));
        data[1] = v;
    }

    void operator*=(int v) {
        if (v == 0) {
            init(0);
            return;
        }

        for (int i = 1; i <= dim; i++) data[i] *= v;
        for (int i = 1; i <= dim; i++) {
            data[i + 1] += data[i] / base;
            data[i] %= base;

            if (data[dim + 1]) dim++;
        }
    }

    void operator+=(big_num& who) {
        dim = max(dim, who.dim);
        for (int i = 1; i <= dim; i++) {
            data[i] += who.data[i];

            data[i + 1] += data[i] / base;
            data[i] %= base;
        }
        if (data[dim + 1]) dim++;
    }

    void print() {
        for (int i = dim; i > 0; i--)
            printf("%d", data[i]);
    }
};

int n, k, p, i, j;
big_num dp[maxN][maxN]; //! dp[i][j] - count of states with i people and j excursions


int main()
{
    freopen("ex.in","r",stdin);
    freopen("ex.out","w",stdout);

    scanf("%d%d%d", &n, &k, &p);

    for (i = 0; i <= p; i++) dp[k][i].init(0);
    dp[k][k].init(1);

    for (i = k + 1; i <= n; i++) {
        dp[i][0].init(0);

        for (j = 1; j <= p; j++) {
            dp[i][j] = dp[i - 1][j];
            dp[i][j] *= j;
            dp[i][j] += dp[i - 1][j - 1];
        }
    }


    dp[n][p].print();


    return 0;
}

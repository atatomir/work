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

#define maxN 1024
#define maxData 60
#define base 1000000000

struct large {
    int dim;
    ll data[maxData];

    large() {
        dim = 1;
        memset(data, 0, sizeof(data));
    }

    void operator*=(int x) {
        static int i;

        for (i = 1; i <= dim; i++) data[i] *= x;
        for (i = 1; i <= dim; i++) {
            if (data[i] >= base) {
                data[i + 1] += data[i] / base;
                data[i] %= base;
            }

            if (data[dim + 1] > 0) dim++;
        }

        if (data[dim] == 0)
            data[dim = 1] = 0;

    }

    void operator+=(const large who) {
        static int i;

        dim = max(dim, who.dim);
        for (i = 1; i <= who.dim; i++) data[i] += who.data[i];
        for (i = 1; i <= dim; i++) {
            if (data[i] >= base) {
                data[i + 1] += data[i] / base;
                data[i] %= base;
            }
        }

        if (data[dim + 1] > 0) dim++;
    }

    void operator+=(int x) {
        static int i;

        data[1] += x;
        for (i = 1; i <= dim; i++) {
            if (data[i] >= base) {
                data[i + 1] += data[i] / base;
                data[i] %= base;
            }
        }

        if (data[dim + 1] > 0) dim++;
    }

    void print() {
        printf("%d", data[dim]);
        for (int i = dim - 1; i > 0; i--) {
            for (int aux = base / 10; aux > 0; aux /= 10)
                if (data[i] < aux)
                    printf("0");

            if (data[i])
                printf("%d", data[i]);
        }

        printf("\n");
    }
};

int n, i, j;
large sum[maxN], par_sum[maxN];
large stair[maxN], par_stair[maxN], super_stair[maxN];
large aux;


int main()
{
    freopen("poli.in","r",stdin);
    freopen("poli.out","w",stdout);

    scanf("%d", &n);

    sum[1].data[1] = par_sum[1].data[1] = stair[1].data[1] = par_stair[1].data[1] = 1;
    super_stair[1].data[1] = 1;

    for (i = 2; i <= n; i++) {
        // compute sum
        sum[i] = sum[i - 1];
        sum[i] += par_sum[i - 2];
        sum[i] += stair[i - 1];

        par_sum[i] = par_sum[i - 1];
        par_sum[i] += sum[i];

        // compute super_stair (needed in stair)
        super_stair[i] = super_stair[i - 1];
        super_stair[i] += par_sum[i];

        // compute stair (needed in sum)
        stair[i] = stair[i - 1];
        stair[i] += par_stair[i - 1];

        aux = super_stair[i - 2];
        aux *= 2;
        stair[i] += aux;
        stair[i] += 1;

        par_stair[i] = par_stair[i - 1];
        par_stair[i] += stair[i];
    }


    sum[n].print();

    cerr << stair[n].dim << ' ';
    cerr << super_stair[n].dim;


    /*for (i = 1; i <= min(n, 100); i++) {
        sum[i].print();
        stair[i].print();
        printf("////\n");
    }*/


    return 0;
}

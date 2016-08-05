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

#define maxN 32
#define digits 35
#define base 1000

struct Large {
    int dim;
    int data[digits];

    Large();
    Large operator+(Large who);
    Large operator*(int v);

    int operator%(int v);

    void from(int v);
    void print();
};

Large::Large() {
    dim = 1;
    memset(data, 0, sizeof(data));
}

void Large::from(int v) {
    memset(data, 0, sizeof(data));

    dim = 0;
    while (v) {
        data[++dim] = v % base;
        v /= base;
    }

    dim = max(dim, 1);
}

Large Large::operator+(Large who) {
    static Large ans;
    static int i;

    ans.dim = max(dim, who.dim);
    memset(ans.data, 0, sizeof(ans.data));

    for (i = 1; i <= ans.dim; i++)
        ans.data[i] = data[i] + who.data[i];
    for (i = 1; i <= ans.dim; i++) {
        ans.data[i + 1] += ans.data[i] / base;
        ans.data[i] %= base;
    }

    ans.dim += (ans.data[ans.dim + 1] != 0);
    return ans;
}

int Large::operator%(int v) {
    int ans = 0;
    int i;

    for (i = dim; i > 0; i--) {
        ans = ans * base + data[i];
        ans %= v;
    }

    return ans;
}

Large Large::operator*(int v) {
    static Large ans;
    int i;

    ans = *this;
    for (i = 1; i <= ans.dim; i++) ans.data[i] *= v;
    for (i = 1; i <= ans.dim; i++) {
        ans.data[i + 1] += ans.data[i] / base;
        ans.data[i] %= base;

        if (ans.data[ans.dim + 1] != 0)
            ans.dim++;
    }

    return ans;
}

void Large::print() {
    if (dim == 1 && data[1] == 0) {
        printf("0\n");
        return;
    }

    printf("%d", data[dim]);
    for (int i = dim - 1; i > 0; i--) {
        for (int aux = base / 10; aux > data[i]; aux /= 10, printf("0"));
        if(data[i]) printf("%d", data[i]);
    }

    printf("\n");
}


int t, ti;
int n, i;
int P, R;

Large rem;
Large period;


int main()
{
    freopen("resturi.in","r",stdin);
    freopen("resturi.out","w",stdout);

    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++) {
        scanf("%d", &n);

        scanf("%d%d", &P, &R);
        rem.from(R);
        period.from(P);

        for (i = 2; i <= n; i++) {
            scanf("%d%d", &P, &R);

            while (rem % P != R)
                rem = rem + period;

            period = period * P;
        }

        rem.print();
    }


    return 0;
}

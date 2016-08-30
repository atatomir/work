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
#define base 10
#define maxData 1024

struct Large {
    int dim;
    int data[maxData];

    Large() {
        dim = 1;
        memset(data, 0, sizeof(data));
    }

    void read() {
        static char s[1024];
        memset(s, 0, sizeof(s));
        scanf("%s", s + 1);
        dim = strlen(s + 1);
        for (int i = 1; i <= dim; i++) data[dim - i + 1] = s[i] - '0';
    }

    bool operator<(const Large& who) {
        if (dim < who.dim) return true;
        if (dim > who.dim) return false;

        for (int i = dim; i > 0; i--) {
            if (data[i] < who.data[i]) return true;
            if (data[i] > who.data[i]) return false;
        }

        return false;
    }

    void operator+=(const Large& who) {
        dim = max(dim, who.dim);
        for (int i = 1; i <= dim; i++) data[i] += who.data[i];
        for (int i = 1; i <= dim; i++) {
            data[i + 1] += data[i] / base;
            data[i] %= base;
        }
        dim += (data[dim + 1] > 0);
    }

    void operator-=(const Large& who) {
        dim = max(dim, who.dim);
        for (int i = 1; i <= dim; i++) data[i] -= who.data[i];
        for (int i = 1; i <= dim; i++) {
            if (data[i] < 0) {
                data[i] += base;
                data[i + 1]--;
            }
        }

        while (data[dim] == 0 && dim > 1) dim--;
    }
};

int k, i, last;
Large n;
Large Side[maxN], Center[maxN];
Large aux;

int ans[maxN];

int main()
{
    freopen("triti2.in","r",stdin);
    freopen("triti2.out","w",stdout);

    scanf("%d", &k);
    n.read();


    Side[1].data[1] = Center[1].data[1] = 1;
    for (i = 2; i <= k; i++) {
        Center[i] = Side[i - 1];
        Center[i] += Side[i - 1];

        Side[i] = Center[i - 1];
    }

    aux = Center[k];
    aux += Side[k];

    if (aux < n) {
        printf("-1");
        return 0;
    }

    if (Center[k] < n) {
        ans[1] = last = 2;
        n -= Center[k];
    } else {
        ans[1] = last = 1;
    }

    for (i = 2; i <= k; i++) {
        if (last == 0) {
            ans[i] = last = 1;
            continue;
        }

        if (last == 2) {
            ans[i] = last = 1;
            continue;
        }

        if (Side[k - i + 1] < n) {
            ans[i] = last = 2;
            n -= Side[k - i + 1];
        } else {
            ans[i] = last = 0;
        }
    }

    for (i = 1; i <= k; i++) printf("%d", ans[i]);


    return 0;
}

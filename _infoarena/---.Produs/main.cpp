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

#define dig 8
#define base 100000000
#define maxData 10000 + 44
#define eps  1e-5

char s[10011];

struct Large {
    int dim, i;
    ll data[maxData];

    void read() {
        scanf("%s", s + 1);
        dim = strlen(s + 1);

        memset(data, 0, sizeof(data));
        for (i = dim; i > 0; i--) data[dim - i + 1] = s[i] - '0';

        int now = 0;
        for (i = 1; i <= dim; i += dig) {
            ll aux = 0;
            for (int j = dig - 1; j >= 0; j--)
                aux = aux * 10 + data[i + j];
            data[++now] = aux;
        }

        dim = now;
    }

    bool divide(ll x) {
        ll rem = 0;

        for (i = dim; i > 0; i--) {
            rem = rem * base + data[i];
            if (rem >= x) rem %= x;
        }

        return rem == 0;
    }

    void operator/=(ll x) {
        for (int i = dim; i > 0; i--) {
            data[i - 1] += base * (data[i] % x);
            data[i] /= x;
        }

        while (data[dim] == 0) dim--;
    }
};

#define maxN 100011

int l = 1, r = 100000, i, last;
bool ciur[maxN];
double P, act;
Large nr;

void manu(ll v) {
    ll v2 = v * v;
    ll v4 = v2 * v2;
    ll v8 = v4 * v4;
    double l = log(v);
    double l2 = log(v2);
    double l4 = log(v4);
    double l8 = log(v8);

    while (nr.divide(v8)) {
        P += l8;
        nr /= v8;
    }

    while (nr.divide(v4)) {
        P += l4;
        nr /= v4;
    }

    while (nr.divide(v2)) {
        P += l2;
        nr /= v2;
    }

    while (nr.divide(v)) {
        P += l;
        nr /= v;
    }
}

int main()
{
    freopen("produs.in","r",stdin);
    freopen("produs.out","w",stdout);

    nr.read();

    manu(2);
    manu(3);
    manu(5);
    manu(7);

    for (i = 2; i <= r; i++) {
        if (ciur[i]) continue;
        for (ll j = 1LL * i * i; j <= r; j += i) ciur[j] = true;

        int cnt = 0;
        while (nr.divide(i)) {
            cnt++;
            nr /= i;
        }

        P += log(i) * cnt;
        if (cnt) last = i;
    }

    int p1 = last, p2 = last;
    act = log(p1);

    while (act < P && p1 > 1) act += log(--p1);

    while ( abs(act - P) > eps && p2 <= r) {
        if (act < P)
            act += log(++p2);
        else
            act -= log(p1++);
    }

    printf("%d %d", p1, p2);



    return 0;
}

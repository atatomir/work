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

#define maxN ((1 << 20) + 13)

void fast_to(int dim, ll *data) {
    int len, i, j;
    ll u, v;

    for (len = 1; 2 * len <= dim; len <<= 1) {
        for (i = 0; i < dim; i += 2 * len) {
            for (j = 0; j < len; j++) {
                u = data[i + j];
                v = data[i + len + j];

                data[i + j] = v;
                data[i + len + j] = u + v;
            }
        }
    }
}

void fast_from(int dim, ll *data) {
    int len, i, j;
    ll u, v;

    for (len = 1; 2 * len <= dim; len <<= 1) {
        for (i = 0; i < dim; i += 2 * len) {
            for (j = 0; j < len; j++) {
                u = data[i + j];
                v = data[i + len + j];

                data[i + j] = -u + v;
                data[i + len + j] = u;
            }
        }
    }
}

int n, i;
ll a[maxN], b[maxN];
ll ans[maxN], ans2[maxN];

void brute() {
    int i, j;

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            ans[i & j] += a[i] * b[j];
}

void fast_solve() {
    int i;

    fast_to(n, a);
    fast_to(n, b);

    for (i = 0; i < n; i++)
        ans2[i] = a[i] * b[i];

    fast_from(n, ans2);
}

int main()
{
    freopen("test.in", "r", stdin);

    /*
    scanf("%d", &n);
    for (i = 0; i < n; i++) scanf("%lld", &a[i]);
    for (i = 0; i < n; i++) scanf("%lld", &b[i]);
    */

    srand(time(NULL));
    n = 1 << 12;
    for (i = 0; i < n; i++) {
        a[i] = rand() % 100;
        b[i] = rand() % 100;

        a[i] -= 50;
        b[i] -= 50;

        if (rand() % 3 == 0) a[i] = 0;
        if (rand() % 3 == 0) b[i] = 0;
    }

    if (n & (n - 1)) {
        cerr << "n is invalid..";
        return 0;
    }

    brute();
    fast_solve();

    for (i = 0; i < n; i++) {
        cerr << ans[i] << ' ' << ans2[i] << '\n';
        if (ans[i] != ans2[i]) {
            cerr << "error\n";
            return 0;
        }
    }


    return 0;
}

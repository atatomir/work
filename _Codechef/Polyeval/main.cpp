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

#define mod 786433
#define def 20

int n, q, i, x;
int to[mod];

vector<int> A, ind, aux; // polynomial
int vars[mod * def]; // argument of function
int ans[mod * def]; // answer
int vA[mod], vB[mod];

int cnt;
int used[mod];


void FFT(int n, int *poly, int m, int *x, int *ans) {
    int i, even, odd, vv, nxt_vals;

    if (n == 1) {
        for (i = 0; i < m; i++)
            ans[i] = A[poly[0]] % mod;
        return;
    }

    even = odd = 0;
    for (i = 0; i < n; i++) aux[i] = poly[i];
    for (i = 0; i < n; i += 2, even++) poly[i / 2] = aux[i];
    for (i = 1; i < n; i += 2, odd++) poly[even + (i / 2)] = aux[i];

    cnt++; nxt_vals = 0;
    for (i = 0; i < m; i++) {
        vv = x[i];
        vv = min(vv, mod - vv);

        if (used[vv] == cnt) continue;
        x[m + nxt_vals] = to[vv];
        nxt_vals++;
        used[vv] = cnt;
    }

    FFT(even, poly, nxt_vals, x + m, ans);
    FFT(odd, poly + even, nxt_vals, x + m, ans + nxt_vals);

    for (i = 0; i < nxt_vals; i++)
        vA[ x[m + i] ] = ans[i];
    for (i = 0; i < nxt_vals; i++)
        vB[ x[m + i] ] = ans[i + nxt_vals];

    for (i = 0; i < m; i++) {
        vv = to[x[i]];

        ans[i] = (1LL * vA[vv] + 1LL * x[i] * vB[vv]) % mod;
    }
}

int main()
{
    //freopen("test.in","r",stdin);

    for (i = 0; i < mod; i++)
        to[i] = (1LL * i * i) % mod;

    scanf("%d", &n); n++;
    for (i = 1; i <= n; i++) {
        scanf("%d", &x);
        A.pb(x);

        ind.pb(i - 1);
    }

    aux.resize(ind.size());
    for (i = 0; i < mod; i++) vars[i] = i;

    FFT(n, &ind[0], mod, vars, ans);

    scanf("%d", &q);
    for (i = 1; i <= q; i++) {
        scanf("%d", &x);
        x %= mod;

        printf("%d\n", ans[x]);
    }

    return 0;
}

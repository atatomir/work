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

#define mod 1000000007

#define maxN 20

int n, i, limit;
ll A[1 << maxN], B[1 << maxN], C[1 << maxN];
ll ans;

void add(ll& a, ll b) {
    a += b;
    if (a >= mod) a -= mod;
}

void subsets() {
    int i, j;

    for (i = 0; i < n; i++) {
        for (j = 0; j < limit; j++) {
            if (j & (1 << i)) {
                add(A[j], A[j ^ (1 << i)]);
                add(B[j], B[j ^ (1 << i)]);
                add(C[j], C[j ^ (1 << i)]);
            }
        }
    }
}

void inv_subsets() {
    int i, j;

    for (i = 0; i < n; i++) {
        for (j = 0; j < limit; j++) {
            if (j & (1 << i)) {
                add(A[j], mod - A[j ^ (1 << i)]);
            }
        }
    }
}

void suprasets() {
    int i, j;

    for (i = 0; i < n; i++) {
        for (j = 0; j < limit; j++) {
            if ( (j & (1 << i)) == 0) {
                add(A[j], A[j ^ (1 << i)]);
            }
        }
    }
}

int main()
{
    //freopen("test.in","r",stdin);

    cin >> n; limit = 1 << n;
    for (i = 0; i < limit; i++) cin >> A[i];
    for (i = 0; i < limit; i++) cin >> B[i];
    for (i = 0; i < limit; i++) cin >> C[i];

    subsets();

    for (i = 0; i < limit; i++)
        A[i] = (((A[i] * B[i]) % mod) * C[i]) % mod;

    inv_subsets();

    suprasets();

    for (i = 0; i < limit; i++)
        add(ans, A[i]);

    cout << ans;

    return 0;
}

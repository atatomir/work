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

const int bts = 20;
const int limit = 1 << 20;

int n, i, j;
ll A[limit];

ll F[limit], G[limit];
ll dp_F[limit][bts + 1], dp_G[limit][bts + 1];

void add(ll& a, ll b) {
    a += b;
    if (a >= mod) a -= mod;
}

int main()
{
    //freopen("test.in","r",stdin);

    cin >> n;
    for (i = 0; i < n; i++) cin >> A[i];

    for (i = 0; i < n; i++) {
        //! compute dp_G partially
        for (j = bts - 1; j >= 0; j--) {
            dp_G[i][j] = dp_G[i][j + 1];
            if (i & (1 << j))
                add(dp_G[i][j], dp_G[i ^ (1 << j)][j + 1]);
        }

        //! compute F
        F[i] = (A[i] * A[i]) % mod;
        F[i] += (dp_G[i][0] * dp_G[i][0]) % mod;
        F[i] %= mod;

        //! compute dp_F
        dp_F[i][bts] = (F[i] * F[i]) % mod;
        for (j = bts - 1; j >= 0; j--) {
            dp_F[i][j] = dp_F[i][j + 1];
            if (i & (1 << j))
                add(dp_F[i][j], dp_F[i ^ (1 << j)][j + 1]);
        }

        //! compute G
        G[i] = dp_F[i][0];

        //! compute G partially
        dp_G[i][bts] = G[i];
        for (j = bts - 1; j >= 0; j--) {
            dp_G[i][j] = dp_G[i][j + 1];
            if (i & (1 << j))
                add(dp_G[i][j], dp_G[i ^ (1 << j)][j + 1]);
        }
    }

    ll ans = 0;
    for (i = 0; i < n; i++)
        add(ans, (((1LL * i * F[i]) % mod) * G[i]) % mod);

    cout << ans;

    return 0;
}

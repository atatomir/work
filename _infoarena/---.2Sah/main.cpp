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

#define mod 100003

ll aux[3][3];

struct matrix {
    int n = 3;
    ll data[3][3];

    void init() {
        memset(data, 0, sizeof(data));
    }

    void operator*=(matrix who) {
        memcpy(aux, data, sizeof(data));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                data[i][j] = 0;

                for (int k = 0; k < n; k++)
                    data[i][j] = (data[i][j] + aux[i][k] * who.data[k][j]) % mod;
            }
        }
    }
};

ll op, n, k;
ll ans, i;
matrix ini, mat;

ll poww(ll a, ll b) {
    ll ans = 1;

    while (b > 0) {
         if (b & 1) ans = (ans * a) % mod;
         b >>= 1;
         a = (a * a) % mod;
    }

    return ans;
}

matrix poww2(matrix a, int b) {
    matrix ans = a;
    b--;

    while (b > 0) {
        if (b & 1) ans *= a;
        b >>= 1;
        a *= a;
    }

    return ans;
}

int main()
{
    freopen("2sah.in","r",stdin);
    freopen("2sah.out","w",stdout);

    scanf("%lld%lld%lld", &op, &n, &k); n++;

    if (op == 1) {
        ans = poww(3, k - 1);
        printf("%lld", ans);
        return 0;
    }

    if (n == k) {
        printf("1");
        return 0;
    }

    ini.init();
    ini.data[0][1] = ini.data[1][2] = ini.data[2][0] = ini.data[2][1] = ini.data[2][2] = 1;
    mat = poww2(ini, n - k);

    printf("%lld", mat.data[2][2]);

    return 0;
}

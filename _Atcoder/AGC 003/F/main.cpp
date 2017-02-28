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
#define mod 1000000007

ll aux[2][2];

struct matrix {
    ll data[2][2];
    int i, j, k;

    void operator*=(matrix who) {
        memcpy(aux, data, sizeof(data));

        for (i = 0; i < 2; i++) {
            for (j = 0; j < 2; j++) {
                data[i][j] = 0;

                for (k = 0; k < 2; k++)
                    data[i][j] += (aux[i][k] * who.data[k][j]) % mod;
                data[i][j] %= mod;
            }
        }
    }
};

int n, m, i, j;
ll k, cnt;
char s[maxN][maxN];

int hor, ver, link_hor, link_ver;
ll a, b, c;

matrix ini;

ll poww(ll a, ll b) {
    ll ans = 1;

    while (b > 0) {
        if (b & 1) ans = (ans * a) % mod;
        b >>= 1;
        a = (a * a) % mod;
    }

    return ans;
}

matrix poww(matrix a, ll b) {
    matrix ans = a; b--;

    while (b > 0) {
        if (b & 1) ans *= a;
        b >>= 1;
        a *= a;
    }

    return ans;
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d%lld\n", &n, &m, &k);
    for (i = 1; i <= n; i++) scanf("%s", s[i] + 1);

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            if (s[i][j] != '#') continue;
            cnt++;

            if (s[i + 1][j] == '#') ver++;
            if (s[i][j + 1] == '#') hor++;
        }
    }

    for (i = 1; i <= n; i++)
        if (s[i][1] == s[i][m] && s[i][1] == '#')
            link_hor++;

    for (i = 1; i <= m; i++)
        if (s[1][i] == s[n][i] && s[1][i] == '#')
            link_ver++;

    if (k == 0) {
        printf("1");
    }

    if (link_hor > 0 && link_ver > 0) {
        printf("1");
        return 0;
    }

    if (link_hor == 0 && link_ver == 0) {
        printf("%lld", poww(cnt, k - 1));
        return 0;
    }

    if (k == 1) {
        printf("1");
        return 0;
    }

    a = cnt;
    if (link_hor) {
        b = hor;
        c = link_hor;
    } else {
        b = ver;
        c = link_ver;
    }

    ini.data[0][0] = a; ini.data[0][1] = -b;
    ini.data[1][0] = 0; ini.data[1][1] = c;

    ini = poww(ini, k - 1);

    ll sol = (mod + ini.data[0][0] + ini.data[0][1]);
    printf("%lld", sol % mod);


    return 0;
}

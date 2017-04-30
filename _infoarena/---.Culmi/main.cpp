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

#define maxN 111

const ll base = 1000000000000000LL;

struct bignum {
    ll data[4];

    void init() {
        memset(data, 0, sizeof(data));
    }

    void operator+=(bignum who) {
        for (int i = 0; i < 4; i++) data[i] += who.data[i];
        for (int i = 0; i < 3; i++) {
            data[i + 1] += data[i] / base;
            data[i] %= base;
        }
    }

    void print() {
        vector<ll> aux;
        int pos = 3;
        int tm;

        while (pos > 0 && data[pos] == 0) pos--;
        printf("%lld", data[pos]);

        for (pos--; pos >= 0; pos--) {
            aux.clear();
            for (tm = 1; tm <= 15; tm++) aux.pb(data[pos] % 10), data[pos] /= 10;
            reverse(aux.begin(), aux.end());
            for (auto e : aux) printf("%lld", e);
        }
    }
};

int n, m, ss, dd, i, j, k;
bignum dp[2][maxN][maxN][2];

void clr(int id) {
    int i, j;

    for (i = 0; i <= n; i++)
        for (j = 0; j <= n; j++)
            dp[id][i][j][0].init(), dp[id][i][j][1].init();
}

int main()
{
    freopen("culmi.in","r",stdin);
    freopen("culmi.out","w",stdout);

    scanf("%d%d", &n, &m);

    ss = 0; dd = 1;
    clr(0); clr(1);
    dp[ss][0][0][0].data[0] = 1;
    for (i = 1; i <= n; i++) {
        //clr(dd);

        for (j = 0; j <= i; j++) {
            for (k = 0; k <= j && k <= m; k++) {
                dp[dd][j][k][0].init();
                dp[dd][j][k][1].init();;

                dp[dd][j][k][0] += dp[ss][j][k][0];
                dp[dd][j][k][0] += dp[ss][j][k][1];

                if (j + 1 > i) continue;
                dp[ss][j + 1][k + 1][1] += dp[ss][j][k][0];
                dp[ss][j + 1][k][1] += dp[ss][j][k][1];
            }
        }

        swap(ss, dd);
    }

    dp[dd][n][m][1].print();



    return 0;
}

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

#define maxLimit 111
#define mod 666013

ll aux[maxLimit][maxLimit];

struct matrix {
    int i, j, k, n;
    ll data[maxLimit][maxLimit];

    void init(int _n) {
        n = _n;
        memset(data, 0, sizeof(data));
    }

    void operator*=(matrix who) {
        memcpy(aux, data, sizeof(data));
        memset(data, 0, sizeof(data));

        for (i = 0; i <= n; i++) {
            for (j = 0; j <= n; j++) {

                for (k = 0; k <= n; k++)
                    data[i][j] += aux[i][k] * who.data[k][j];
                data[i][j] %= mod;
            }
        }
    }

};

int cnt;
int p, t, limit;
matrix base;

inline int get_state(int dif, int pos) {
    return min(dif, p) * 5 + pos;
}

matrix poww(matrix a, int b) {
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
    freopen("ikebana.in","r",stdin);
    freopen("ikebana.out","w",stdout);

    scanf("%d%d%d", &cnt, &p, &t);
    limit = get_state(p, 4);
    base.init(limit);

    for (int st = 0; st <= limit; st++) {
        int dif = st / 5;
        int wh = st % 5;

        //! 1-2-3
        //! 3-1-2
        //! 4-...-4

        //! flower 1
        if (wh == 0)
            base.data[st][get_state(dif + 1, 1)]++;
        if (wh == 1)
            base.data[st][get_state(dif + 1, 1)]++;
        //if (wh == 2)
        //    base.data[st][get_state(dif + 1, 1)]++;
        if (wh == 3)
            base.data[st][get_state(dif + 1, 1)]++;
        if (wh == 4)
            base.data[st][get_state(dif + 1, 1)]++;

        //! flower 2
        //if (wh == 0)
        //    base.data[st][get_state(dif + 1, 1)]++;
        if (wh == 1)
            base.data[st][get_state(dif + 1, 2)]++;
        //if (wh == 2)
        //    base.data[st][get_state(dif + 1, 1)]++;
        if (wh == 3)
            base.data[st][get_state(dif + 1, 4)]++;
        //if (wh == 4)
        //    base.data[st][get_state(dif + 1, 1)]++;

        //! flower 3
        if (wh == 0)
            base.data[st][get_state(dif + 1, 3)]++;
        if (wh == 1)
            base.data[st][get_state(dif + 1, 3)]++;
        if (wh == 2)
            base.data[st][get_state(dif + 1, 3)]++;
        if (wh == 3)
            base.data[st][get_state(dif + 1, 3)]++;
        //if (wh == 4)
        //    base.data[st][get_state(dif + 1, 1)]++;

        //! flower 4
        if (dif >= p)
            if (wh != 2 && wh != 4)
                base.data[st][get_state(0, 0)]++;

        //! flower 5
        if (wh != 2 && wh != 4)
            base.data[st][get_state(dif + 1, 0)] += t - 4;
    }

    matrix sol = poww(base, cnt);
    ll ans = 0;

    for (int st = 0; st <= limit; st++) {
        int dif = st / 5;
        int wh = st % 5;

        if (wh == 2 || wh == 4) continue;
        if (sol.data[ get_state(p, 0) ][st] == 0) continue;
        ans += sol.data[ get_state(p, 0) ][st];
    }

    ans %= mod;
    printf("%lld", ans);
    cerr << ans;




    return 0;
}

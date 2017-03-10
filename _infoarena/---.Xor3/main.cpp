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

#define mate

ll Q, qq, i, j, a, b, m;

ll check(ll x, ll y) {
    int cad;
    ll aux;

    if (x < 0 || y < 0) return 0;
    if (y == 0) return 0;

    #ifdef mate
        x++; y--;
        if (x & y)
            return 0;
        return 1;
    #else


    for (int bit = 29; bit >= 0; bit--) {
        cad = 0;
        aux = 1LL << bit;

        if (x >= aux) cad += 2;
        if (y >= aux) cad++;

        if (cad == 2) {
            x -= aux;
        }

        if (cad == 1) {
            if (x == aux - 1) {
                if (y == aux)
                    return 1;
                return 0;
            }
            y -= aux;
        }

        if (cad == 3) {
            if (x == 2 * aux - 1)
                return 1;
            return 0;
        }

        if (x == 0 && y == 0) return 0;
    }

    #endif
}

ll solve(ll x, ll y) {
    ll ans = 0;

    for (int bit = 0; bit <= 30; bit++)
        if (check(x + (1LL << bit) - 1, y - (1LL << bit) + 1))
            ans += 1LL << bit;

    return ans;
}

int main()
{
    freopen("xor3.in","r",stdin);
    freopen("xor3.out","w",stdout);

    /*int mat[1024][1024];
    int bit = 3;
    int dim = 16;
    int i, j;

    for (i = 0; i < dim; i++) mat[0][i] = (i >> bit) & 1;
    for (i = 1; i < dim; i++) mat[i][0] = 0;
    for (i = 1; i < dim; i++)
        for (j = 1; j < dim; j++)
            mat[i][j] = mat[i - 1][j] ^ mat[i][j - 1];

    for (i = 0; i < dim; i++) {
        for (j = 0; j < dim; j++)
            printf("%c", (mat[i][j] ? '#' : '.'));
        printf("\n");
    }*/

    scanf("%lld%lld%lld%lld%lld%lld", &Q, &i, &j, &a, &b, &m);
    for (qq = 1; qq <= Q; qq++) {
        printf("%lld\n", solve(i, j));
        i = (i * a + b) % m;
        j = (j * a + b) % m;
    }



    return 0;
}

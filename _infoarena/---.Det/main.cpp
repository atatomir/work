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

#define maxN 51
#define mod 9901
#define maxLog 31

struct matrix {
    int data[maxN][maxN];

    void init() {
        memset(data, 0, sizeof(data));
        for (int i = 1; i < maxN; i++) data[i][i] = 1;
    }
};

int n, k, i, j;
ll aux[maxN][maxN];
matrix mat, ans, ini;

int gauss[maxN][maxN];
int sol;

int sg = 1;

matrix pre_sum[maxLog];
matrix pre_prod[maxLog];



matrix sum(const matrix& a, const matrix& b) {
    static matrix ans;
    static int i, j;

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            ans.data[i][j] = a.data[i][j] + b.data[i][j];
            if (ans.data[i][j] >= mod) ans.data[i][j] -= mod;
        }
    }

    return ans;
}

matrix prod(const matrix& a, const matrix& b) {
    static int i, j, k;
    static matrix ans;

    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            aux[i][j] = 0;

    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            for (k = 1; k <= n; k++)
                aux[i][j] += 1LL * a.data[i][k] *  b.data[k][j];

    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            ans.data[i][j] = aux[i][j] % mod;

    return ans;
}

matrix poww(matrix base, int up) {
    matrix ans;
    ans.init();

    while (up) {
        if (up & 1) ans = prod(ans, base);
        up >>= 1;
        base = prod(base, base);
    }

    return ans;
}

matrix solve(int k) {
    pre_prod[0] = mat;

    for (i = 1; i < maxLog; i++)
        pre_prod[i] = prod(pre_prod[i - 1], pre_prod[i - 1]);

    pre_sum[0] = ini;

    for (i = 1; i < maxLog; i++)
        pre_sum[i] = sum(prod(pre_sum[i - 1] , pre_prod[i - 1]), pre_sum[i - 1]);

    matrix ans;
    memset(ans.data, 0, sizeof(ans.data));


    for (i = 0; k > 0; i++, k >>= 1) {
        if (k % 2 == 0) continue;

        ans = sum(prod(ans, pre_prod[i]), pre_sum[i]);
    }

    return ans;
}

int nr_pow(int a, int b) {
    int ans = 1;

    while (b) {
        if (b & 1) ans = (ans * a) % mod;
        b >>= 1;
        a = (a * a) % mod;
    }

    return ans;
}

void rm_gauss() {
    int i, j, k, l;

    i = j = 1;
    while (i <= n && j <= n) {
        bool found = false;

        for (k = i; k <= n; k++) {
            if (gauss[k][j] == 0) continue;
            found = true;
            for (l = 1; l <= n; l++) swap(gauss[i][l], gauss[k][l]);

            if (k != i) sg *= -1;
            break;
        }

        if (!found) { j++; continue; }

        for (k = i + 1; k <= n; k++) {
            if (gauss[k][j] == 0) continue;

            int val = (gauss[k][j] * nr_pow(gauss[i][j], mod - 2)) % mod;
            for (l = j; l <= n; l++) {
                gauss[k][l] = mod + gauss[k][l] - ((gauss[i][l] * val) % mod);
                if (gauss[k][l] >= mod)
                    gauss[k][l] -= mod;
            }
        }


        i++; j++;
    }
}





int main()
{
    freopen("det.in","r",stdin);
    freopen("det.out","w",stdout);

    scanf("%d%d", &n, &k);
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            scanf("%d", &mat.data[i][j]), mat.data[i][j] %= mod;

    ini.init();
    ans = solve(k + 1);

    /*for (i = 1; i <= n; i++, printf("\n"))
        for (j = 1; j <= n; j++)
            printf("%d ", ans.data[i][j]);
    */

    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            gauss[i][j] = ans.data[i][j];

    rm_gauss();

    sol = 1;
    for (i = 1; i <= n; i++) sol = (sol * gauss[i][i]) % mod;

    printf("%d", (mod + sol * sg) % mod);

    return 0;
}

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

#define maxN 211
#define moddo 666013

int n, m, i, j, k, c, rez;
int aux[maxN][maxN];
int work[maxN][maxN];
int mod;
int ans = 1;



int poww(int x, int how, int mod) {
    int ans = 1;

    while (how) {
        if (how & 1) ans = (1LL * ans * x) % mod;
        how >>= 1;
        x = (1LL * x * x) % mod;
    }

    return ans;
}

int invmod(int x) {
    return poww(x, mod - 2, mod);
}

void swap_lines(int a, int b) {
    for (int i = 1; i <= rez; i++)
        swap(work[a][i], work[b][i]);
}

int process() {
    int i, j, k, t;
    bool found;
    int ans = 0;

    i = j = 1;
    while (i <= n && j < rez) {
        //!find a suitable ecuation
        found = false;
        for (k = i; k <= n; k++) {
            if (work[k][j] == 0) continue;
            found = true;
            swap_lines(i, k);
            break;
        }

        if (!found) {
            ans++;
            j++;
            continue;
        }

        for (k = i + 1; k <= n; k++) {
            if (work[k][j] == 0) continue;

            int aux = (1LL * work[i][j] * invmod(work[k][j])) % mod;
            for (t = j; t <= rez; t++) {
                work[k][t] = (1LL * work[k][t] * aux) % mod;
                work[k][t] = (mod + work[k][t] - work[i][t]) % mod;
            }
        }

        i++; j++;
    }

    return ans;
}

int solve(int _mod) {
    int i, j;

    mod = _mod;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= rez; j++)
            work[i][j] = aux[i][j] % mod;

    return poww(mod, process(), moddo);
}





int main()
{
    freopen("color3.in","r",stdin);
    freopen("color3.out","w",stdout);

    scanf("%d%d%d%d", &n, &m, &k, &c); rez = m + 1;
    for (i = 1; i <= n; i++) {
        scanf("%d", &aux[i][rez]);
        aux[i][rez] = (k + c - aux[i][rez]) % k;
    }

    for (i = 1; i <= m; i++) {
        for (j = 1; j <= n; j++) {
            scanf("%d", &aux[j][i]);
            aux[j][i] %= k;
        }
    }

    for (int div = 2; div * div <= k; div++) {
        if (k % div) continue;

        k /= div;
        ans = (1LL * ans * solve(div)) % moddo;
    }
    if (k != 1)
        ans = (1LL * ans * solve(k)) % moddo;

    printf("%d", ans);
    cerr << ans;

    return 0;
}

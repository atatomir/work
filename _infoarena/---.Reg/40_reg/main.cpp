#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <bitset>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

#define maxVal 500011

int t, ti;
int n, k, A, B, C, i;

int def = 0;
int last[maxVal];
int alrdn[maxVal];

bool check(int N) {
    int i, X;
    int used;

    def += n;
    for (i = X = 1; i <= N; X = (1LL * X * A + 1LL* (++i) * B) % C)
        last[X] = def + i;

    used = 0;
    for (i = X = 1; i <= N; X = (1LL * X * A + 1LL * (++i) * B) % C) {
        if (alrdn[X] != def) {
            alrdn[X] = def;
            if(++used > k) return false;
        }

        if (last[X] == def + i) used--;
    }

    return true;
}

int main()
{
    freopen("reg.in","r",stdin);
    freopen("reg.ok","w",stdout);

    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++) {
        scanf("%d%d%d%d%d", &A, &B, &C, &n, &k);

        int ans = 0;
        for (int step = (1 << 18); step > 0; step >>= 1)
            if (ans + step <= n)
                if (check(ans + step))
                    ans += step;

        printf("%d\n", ans);
    }


    return 0;
}

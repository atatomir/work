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

int n, i, k, bit, team;
int R, aux;

vector<int> now;

int main()
{
    freopen("copii2.in","r",stdin);
    freopen("copii2.out","w",stdout);

    scanf("%d%d", &n, &k);
    n--;

    aux = n;
    while (aux) {
        R++;
        aux /= k;
    }

    printf("%d\n", R);

    bit = 1;
    for (i = 1; i <= R; i++, bit *= k) {
        int how = k - 1;
        while (1LL * how * bit > 1LL * n) how--;

        printf("%d\n", how + 1);

        for (team = 0; team <= how; team++) {
            now.clear();

            for (ll mask = 0; ; mask++) {
                ll mod = ((mask / bit) * k + team) * bit + (mask % bit);
                if (mod > n) break;

                now.pb(1 * mod + 1);
            }

            printf("%d ", now.size());
            for (auto v : now)
                printf("%d ", v);
            printf("\n");
        }
    }


    return 0;
}

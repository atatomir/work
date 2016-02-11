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

#define maxN 30011
#define maxK 1024

int t, n, i, k, m;
int ans;
int limit[maxN];
int pay[maxK];
int rez;

int main()
{
    freopen("ab.in","r",stdin);
    freopen("ab.out","w",stdout);

    scanf("%d", &t);
    for (; t > 0; t--) {
        scanf("%d%d%d", &n, &m, &k);
        for (i = 1; i <= k; i++) scanf("%d", &pay[i]);
        sort(pay + 1, pay + k + 1);
        for (i = 1; i <= n; i++) {
            scanf("%d", &limit[i]);
            limit[i] += limit[i - 1];
        }

        rez = pay[1] * (m - limit[n]);
        m = limit[n];

        ans = pay[1] * max(n, m) + pay[2] * min(n, m);
        limit[n + 1] = -1;

        if (k > 2) {
            for (i = 1; i <= n; i++) {
                if (limit[i] == limit[i + 1]) continue;

                int aux = i * pay[1]; //! first i in #1
                aux += pay[1] * (m - limit[i]); //! from limit[i] + 1...m in #1

                int h1 = limit[i]; //! in the left
                int h2 = n - i; //! int the right

                aux += pay[2] * max(h1, h2) + pay[3] * min(h1, h2);

                ans = min(ans, aux);
            }
        }

        printf("%d\n", ans + rez);
    }


    return 0;
}

#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

#define pb push_back
#define mp make_pair
#define ll long long

#define maxN 10011

int t, n, m, k, i, x;
bool bad[maxN];
int last_l[maxN], last_r[maxN];

int changes, delay;

int main()
{
    freopen("cutie.in", "r", stdin);
    freopen("cutie.out", "w", stdout);

    scanf("%d", &t);
    for (; t > 0; t--) {
        memset(bad, 0, sizeof(bad));
        changes = delay = 0;

        scanf("%d%d%d", &n, &k, &m);
        for (i = 1; i <= k; i++) {
            scanf("%d", &x);
            bad[x] = true;
        }
        bad[0] = bad[n + 1] = true;
        bad[1] = bad[n] = true;

        last_l[0] = 0;
        for (i = 1; i <= n; i++) {
            last_l[i] = last_l[i - 1];
            if (bad[i]) last_l[i] = i;
        }

        last_r[n + 1] = n + 1;
        for (i = n; i > 0; i--) {
            last_r[i] = last_r[i + 1];
            if (bad[i]) last_r[i] = i;
        }


        for (i = 1; i <= m; i++) {
            scanf("%d", &x);

            int on_l = x - last_l[x];
            int on_r = last_r[x] - x;

            if ( (on_l ^ on_r) & 1 ) {
                //! differ
                changes ^= 1;
            } else {
                delay ^= on_l & 1;
            }
        }

        printf("%d", changes | delay);
    }
    return 0;
}

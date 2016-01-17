#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 1000000
#define ll long long

int t, test;
ll n, m, L, D, i;
ll W[maxN];

ll free_w[maxN];
ll free_d[maxN];

ll solve() {
    int i, j;

    sort(W + 1, W + n + 1);

    m = min(m, L);
    memset(free_w, 0, sizeof(free_w));
    memset(free_d, 0, sizeof(free_d));

    ll prep = L;
    ll washed = 0;
    ll solved = 0;

    ll time = -1;
    while (solved != L) {
        time++;

        for (i = 1; i <= m; i++) {
            if (free_d[i] <= time && free_d[i] != 0) {
                solved++;
                free_d[i] = 0;
            }
        }

        for (i = 1; i <= n; i++) {
            if (free_w[i] <= time && free_w[i] != 0) {
                washed++;
                free_w[i] = 0;
            }
        }

        for (i = 1; i <= m && washed > 0; i++) {
            if (free_d[i] == 0) {
                washed--;
                free_d[i] = time + D;
            }
        }

        for (i = 1; i <= n && prep > 0; i++) {
            if (free_w[i] == 0) {
                prep--;
                free_w[i] = time + W[i];
            }
        }

    }

    return time;
}

int main()
{
    freopen("input.in","r",stdin);
    freopen("output.ok","w",stdout);

    scanf("%d", &t);
    for (test = 1; test <= t; test++) {
        scanf("%lld %lld %lld %lld", &L, &n , &m, &D);
        for (i = 1; i <= n; i++)
            scanf("%lld", &W[i]);

        printf("%lld\n", solve());
    }


    return 0;
}

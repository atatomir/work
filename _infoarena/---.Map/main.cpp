#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 2016

int n, m, i, lim;
char s[maxN];

int q, pr[maxN];
int good[maxN];

void kmp_pr() {
    int i;

    q = 0;
    pr[1] = 0;

    for (i = 2; i <= m; i++) {
        while (q > 0 && s[q + 1] != s[i])
            q = pr[q];

        if (s[q + 1] == s[i]) q++;
        pr[i] = q;
    }
}

int main()
{
    freopen("map.in","r",stdin);
    freopen("map.out","w",stdout);

    scanf("%d%d\n", &n, &m);

    if (m & 1)
        lim = (m + 1) >> 1;
    else
        lim = (m >> 1) + 1;

    for (i = 1; i <= n; i++) {
        scanf("%s\n", s + 1);

        kmp_pr();
        q = m;

        while (q >= lim) {
            good[q]++;
            q = pr[q];
        }
    }

    for (i = 1; i <= m; i++) {
        if (good[i] == n) {
            printf("%d", i);
            return 0;
        }
    }

    return 0;
}

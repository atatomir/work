#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 1000011

int n, i;
int v[maxN];

int evil, down_val;
int best, wh;

int main()
{
    freopen("munte4.in","r",stdin);
    freopen("munte4.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d", &v[i]);
        v[i] += i - 1;

        best = max(best, v[i]);
    }

    wh = 1;

    evil = best;
    down_val = 0;

    for (i = 2; i <= n; i++) {
        down_val++;

        v[i - 1] += n;
        if (v[i - 1] > evil) evil = v[i - 1];

        if (best > evil - down_val) {
            best = evil - down_val;
            wh = i;
        }
    }

    printf("%d %d", wh, best);


    return 0;
}

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

#define maxN 1024
#define def 10000
#define maxDim def + 11

/*
 *  from 0 to x - 1
 *  from 0 to y - 1
 */

int t, ti;
int n, xmax, ymax, i, j;
pair<int, int> P[maxN];
int H[maxDim];

int l[maxDim], r[maxDim];
int S[maxDim], dim;

int ans;



bool cmp(const pair<int, int>& a, const pair<int, int>& b) {
    return mp(a.second, a.first) > mp(b.second, b.first);
}

void compute(int base) {
    int i;

    dim = 0;
    for (i = 0; i < xmax; i++) {
        r[i] = xmax;

        while (dim != 0 && H[S[dim]] >= H[i]) r[S[dim--]] = i;
        l[i] = (dim == 0 ? 0 : S[dim]);
        S[++dim] = i;
    }

    for (i = 0; i < xmax; i++) {
        ans = max(ans, (H[i] - base) * (r[i] - l[i]) );
    }
}

int main()
{
    freopen("dr.in","r",stdin);
    freopen("dr.out","w",stdout);

    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++) {
        scanf("%d%d%d", &n, &xmax, &ymax);
        for (i = 1; i <= n; i++) scanf("%d%d", &P[i].first, &P[i].second);

        sort(P + 1, P + n + 1, cmp);
        for (i = 0; i <= xmax; i++) H[i] = ymax;

        ans = 0;
        for (i = 1; i <= n; i = j) {
            compute(P[i].second);

            for (j = i; j <= n && P[i].second == P[j].second; j++)
                H[P[j].first] = P[j].second;
        }

        compute(0);

        printf("%d\n", ans);
    }


    return 0;
}

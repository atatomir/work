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

const int maxN = 18;
const int maxDim = 1 << maxN;
const int inf = 1000000000;

int n, i, j, limit;
pair<int, int> best[maxDim];
int ans[maxN];

pair<int, int> combine(pair<int, int> A, pair<int, int> B) {
    if (A.first < B.first) swap(A, B);
    return mp(A.first, max(A.second, B.first));
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d", &n);
    limit = 1 << n;

    for (i = 0; i < limit; i++) {
        scanf("%d", &best[i].first);
        best[i].second = -inf;
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < limit; j++) {
            if ((j >> i) & 1) 
                best[j] = combine(best[j], best[j ^ (1 << i)]);
        }
    }

    for (i = 1; i < limit; i++) {
        ans[i] = max(ans[i - 1], best[i].first + best[i].second);
        printf("%d\n", ans[i]);
    }


    return 0;
}

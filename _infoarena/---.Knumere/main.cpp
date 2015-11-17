#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 1000011

int n, k, i, dim;
int v[maxN];
deque< pair<int, int> > DQ;
int ans = 2000000000;

int main()
{
    freopen("knumere.in","r",stdin);
    freopen("knumere.out","w",stdout);

    scanf("%d%d", &n, &k);
    for (i = 1; i <= n; i++) scanf("%d", &v[i]);
    for (i = 1; i < n; i++) v[i] = v[i + 1] - v[i];
    n--;
    dim = n - k;

    while (!DQ.empty()) DQ.pop_back();
    for (i = 1; i <= n; i++) {
        while (!DQ.empty()) {
            auto last = DQ.back();
            if (last.second > v[i]) break;
            DQ.pop_back();
        }
        DQ.push_back(mp(i, v[i]));

        if (DQ.front().first <= i - dim) DQ.pop_front();

        if (i >= dim) ans = min(ans, DQ.front().second);
    }

    printf("%d", ans);

    return 0;
}

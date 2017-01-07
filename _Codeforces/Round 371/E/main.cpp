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

#define maxN 100011
#define inf 1000000001

int n, m, i;
int a[maxN];
int dif1[maxN], dif2[maxN];
int go[maxN];

void rot() {
    pair<int, int> best = {-1, 0};
    for (i = 1; i < n; i++)
        best = max(best, mp(a[i + 1] - a[i] - 1, i));
    best = max(best, mp(m - a[n], n));

    for (i = 1; i < best.second; i++)
        a[i] += m;

    sort(a + 1, a + n + 1);
    for (i = n; i >= 1; i--) a[i] -= a[1] - 1;
}

bool check(int x, int* v, int bg) {
    int i;
    int pos = 1;

    for (i = 1; i <= n; i++) go[i] = -inf;
    go[1] = (bg == 1 ? pos + x : pos);
    pos += v[1] + 1;

    for (i = 2; i <= n; i++) {
        go[i] = max(go[i], go[i - 1]);

        if (go[i - 1] >= pos - 1)
            go[i] = max(go[i], pos + x);

        if (go[i - 1] + 1 >= pos - x)
            go[i] = max(go[i], pos);

        if (i < n && go[i - 1] + 1 >= pos + v[i] + 1 - x)
            go[i + 1] = max(go[i + 1], pos + x);

        int to = pos + x;
        if (to > m) {
            to -= m;
            go[i] = max(go[i], to);
        }


        pos += v[i] + 1;
    }

    return go[n] + x * (bg == 2 ? 1 : 0) >= m;
}

int solve() {
    int ans = -1;

    for (int step = (1 << 29); step > 0; step >>= 1) {
        if (ans + step > m) continue;

        if (check(ans + step, dif1, 1) == true)
            continue;
        if (check(ans + step, dif1, 2) == true)
            continue;

        if (check(ans + step, dif2, 1) == true)
            continue;
        if (check(ans + step, dif2, 2) == true)
            continue;

        ans += step;
    }

    return ans + 1;
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d%d", &m, &n);
    for (i = 1; i <= n; i++) scanf("%d", &a[i]);

    sort(a + 1, a + n + 1);
    for (i = n; i >= 1; i--) a[i] -= a[1] - 1;

    rot();

    for (i = 2; i <= n; i++) dif1[i - 1] = a[i] - a[i - 1] - 1;
    dif1[n] = m - a[n];

    memcpy(dif2, dif1, sizeof(dif1));
    reverse(dif2 + 1, dif2 + n + 1);
    dif2[0] = dif2[n];
    for (i = n; i > 0; i--)
        dif2[i] = dif2[i - 1];

    printf("%d", solve());


    return 0;
}

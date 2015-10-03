#include <cstdio>
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 1000011

int n, i;
pair<int, int> Point[maxN];
int ans[maxN];

bool cmp_x(int a, int b) {
    return Point[a] < Point[b];
}
bool cmp_y(int a, int b) {
    return Point[a].second < Point[b].second;
}

void Merge(int l, int r, int pas) {
    if (l >= r) return;
    if (pas >= 5) {
        random_shuffle(ans + l, ans + r + 1);
        return;
    }

    sort(ans + l, ans + r + 1, cmp_x);
    int mid_line = (l+r) >> 1;

    sort(ans + l, ans + mid_line + 1, cmp_y);
    int mid_column = (l + mid_line) >> 1;
    Merge(l, mid_column, pas + 1);
    Merge(mid_column + 1, mid_line, pas + 1);

    sort(ans + mid_line + 1, ans + r + 1, cmp_y);
    /**/ mid_column = (mid_line + 1 + r) >> 1;
    Merge(mid_line + 1, mid_column, pas + 1);
    Merge(mid_column + 1, r, pas + 1);
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d%d", &Point[i].first, &Point[i].second);
        ans[i] = i;
    }

    Merge(1, n, 1);
    for (int i = 1; i <= n; i++) printf("%d ", ans[i]);

    return 0;
}

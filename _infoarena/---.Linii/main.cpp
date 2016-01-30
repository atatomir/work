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

#define maxN 300011

int n, i, x, y;
pair<int, int> Point[maxN];

int dim;
int S[maxN];

int cb(int val) {
    int ans = 0;

    for (int step = 1 << 19; step; step >>= 1)
        if (ans + step <= dim)
            if (S[ans + step] < val)
                ans += step;

    return ans + 1;
}

bool cmp(const pair<int, int>& a, const pair<int, int>& b) {
    if (a.first == b.first)
        return a.second > b.second;
    return a.first < b.first;
}

int main()
{
    freopen("linii.in","r",stdin);
    freopen("linii.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d%d", &x, &y);
        Point[i] = mp(x - y, x + y);
    }

    sort(Point + 1, Point + n + 1, cmp);
    dim = 0;
    for (i = 1; i <= n; i++) {
        int pos = cb(Point[i].second);
        S[pos] = Point[i].second;
        dim = max(dim , pos);
    }

    printf("%d", dim);

    return 0;
}

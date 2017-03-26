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

int n, c, k, i, j, ans;
int t[maxN];

bool check(int a, int b) {
    if (b > n) return false;
    if (b - a + 1 > c) return false;
    if (t[b] - t[a] > k) return false;
    return true;
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d%d", &n, &c, &k);
    for (i = 1; i <= n; i++) scanf("%d", &t[i]);
    sort(t + 1, t + n + 1);

    for (i = 1; i <= n; i = j) {
        for (j = i; check(i, j); j++);
        ans++;
    }

    printf("%d", ans);


    return 0;
}

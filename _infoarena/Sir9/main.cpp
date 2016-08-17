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

#define maxN 30011

int n, i, ans;
char s[maxN];

int solve(int l, int r) {
    if (l == r) return l;

    int mid = (l + r) >> 1;
    int c1 = solve(l, mid);
    int c2 = solve(mid + 1, r);

    for (int i = 0; c1 + i < c2; i++) {
        if (s[c1 + i] < s[ (c2 + i) % n ]) return c1;
        if (s[c1 + i] > s[ (c2 + i) % n ]) return c2;
    }

    return c1;
}

int main()
{
    freopen("sir9.in","r",stdin);
    freopen("sir9.out","w",stdout);

    scanf("%d\n", &n);
    for (i = 0; i < n; i++)
        scanf("%s\n", &s[i]);

    for (i = 1; s[i] == s[1] && i <= n; i++);
    if (i == n + 1) {
        printf("1");
        return 0;
    }

    ans = solve(0, n - 1);
    ans += n;

    printf("%d", ans);


    return 0;
}

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

#define maxN 111

int n, i, best, sum;
int v[maxN];

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) scanf("%d", &v[i]);
    sort(v + 1, v + n + 1);

    best = n - 1;
    sum = 0;

    for (i = 1; i < n; i++) {
        sum += v[i];
        best = min(best, max(n - i - 1, sum));
    }

    printf("%d", best);

    return 0;
}

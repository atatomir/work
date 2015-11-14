#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 1024

int n, i, j, ans;
int v[maxN];

int main()
{
    freopen("input.in","r",stdin);
    freopen("output.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d", &v[i]);
        v[i] += v[i - 1];
    }

    ans = v[1];
    for (i = 1; i <= n; i++)
        for(j = 1; j <= n; j++)
            ans = max(ans, v[j] - v[i - 1]);

    printf("%d", ans);


    return 0;
}

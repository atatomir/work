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

int n, i, j, ans;

int main()
{
    freopen("regine.in","r",stdin);
    freopen("regine.out","w",stdout);

    scanf("%d", &n);
    ans = (2 * n + 1) / 3;
    printf("%d\n", ans);

    i = n - ans + 1; j = 1;
    while (i <= n) {
        printf("%d %d\n", i, j);
        i += 2; j++;
    }

    i = n - ans + 2; j = n - ans + 2;
    while (i <= n) {
        printf("%d %d\n", i, j);
        i += 2; j++;
    }



    return 0;
}

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

int n, i;
int ant, ans, x;

int main()
{
    freopen("input.in","r",stdin);
    freopen("output.out","w",stdout);

    scanf("%d%d", &n, &ant);
    ans = ant;

    for (i = 2; i <= n; i++) {
        scanf("%d", &x);
        ant = max(ant + x, x);
        ans = max(ans, ant);
    }

    printf("%d", ans);


    return 0;
}

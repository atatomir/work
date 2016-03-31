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

int n, k;

void no_sol() {
    printf("-1");
    exit(0);
}

void is_ok() {
    for (int i = 2; i <= n; i++) printf("%d %d\n", i - 1, i);
    printf("GR");
    for (int i = 3; i <= n; i++) printf("B");
}

int main()
{
    freopen("pscarb.in","r",stdin);
    freopen("pscarb.out","w",stdout);

    scanf("%d%d", &n, &k);
    if (k != 2) no_sol();
    if (n == 2) no_sol();
    if (n % 2 == 0) no_sol();
    is_ok();

    return 0;
}

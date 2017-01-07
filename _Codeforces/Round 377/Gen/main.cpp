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

int n, i;

int main()
{
    freopen("test.in","w",stdout);

    n = 200000;
    printf("%d %d\n", n, n);
    for (i = 1; i <= n; i++) printf("%d ", 1);
    printf("\n");
    for (i = 1; i <= n; i++) printf("%d ", 1000000000);
    printf("\n");


    return 0;
}

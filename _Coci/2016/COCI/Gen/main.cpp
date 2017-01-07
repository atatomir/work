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

int n = 10000;
int i;

int main()
{
    freopen("test.in","w",stdout);

    printf("%d\n", n);
    for (i = 2; i < n; i++) printf("%d %d\n", i - 1, i);
    printf("%d %d\n", n - 2, n);
    for (i = 1; i <= n; i++) printf("1\n");


    return 0;
}

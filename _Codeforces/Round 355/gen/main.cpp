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



int main()
{
    freopen("test.in","w",stdout);

    int n = 300;
    int m = 300;
    int p = 3;
    int i, j;

    printf("%d %d %d\n", n, m, p);

    for (i = 1; i <= 150; i++, printf("\n"))
        for (j = 1; j <= 300; j++)
            printf("%d ", 1);

    for (i = 1; i <= 150; i++, printf("\n"))
        for (j = 1; j <= 300; j++)
            printf("%d ", ((i == 150 && j == 300) ? 3 : 2));



    return 0;
}

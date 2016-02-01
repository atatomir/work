#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

int n = 10000;

int main()
{
    freopen("mesaj3.in","w",stdout);

    srand(time(NULL));

    int i, j;

    printf("%d\n", n);
    for (i = 2; i <= n; i++)
        printf("%d %d\n", rand() % (i - 1) + 1, i);
    printf("%d\n", 9 * n);
    for (i = 1; i <= n; i++)
        for (j = 1; j <= 9; j++)
            printf("%d %d 10\n", i, i);


    return 0;
}

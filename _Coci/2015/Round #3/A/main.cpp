#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

int n, i, x, sum, p;

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d", &x);
        p = x % 10;
        x /= 10;

        int act = 1;
        for (int j = 1; j <= p; j++)
            act *= x;
        sum += act;
    }

    printf("%d", sum);

    return 0;
}

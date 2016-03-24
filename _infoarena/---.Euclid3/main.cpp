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

int t, ti;
int a, b, c, d, x, y;

int euclid(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    int xx, yy;
    int d = euclid(b, a % b, xx, yy);
    x = yy;
    y = (1LL * d - 1LL * a * x) / b;
    return d;
}

int main()
{
    freopen("euclid3.in","r",stdin);
    freopen("euclid3.out","w",stdout);

    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++) {
        scanf("%d%d%d", &a, &b, &c);

        d = euclid(a, b, x, y);
        if (c % d)
            printf("0 0\n");
        else
            printf("%d %d\n", x * (c / d), y * (c / d));
    }


    return 0;
}

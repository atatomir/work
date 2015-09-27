#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

long long n, i, k;
long long last;
bool win;

int main()
{
    freopen("pp.in","r",stdin);
    freopen("pp.out","w",stdout);

    scanf("%lld%lld", &n, &k);

    if (n == 0) {
        printf("0\n");
        return 0;
    }

    last = 0; win = false;
    while (last < n) {
        win ^= true;

        if (win)
            last = (last + 1) * k - 1;
        else
            last = (last + 1) * 2 - 1;
    }

    printf("%d\n", (win?1:0));

    return 0;
}

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

ll x, cnt;

int main()
{
    freopen("test.in","r",stdin);

    scanf("%lld", &x);
    cnt = (x / 11);
    x -= cnt * 11;

    if (x == 0) {
        printf("%lld", 2LL * cnt);
        return 0;
    }

    if (x <= 6)
        printf("%lld", 2LL * cnt + 1);
    else
        printf("%lld", 2LL * cnt + 2);



    return 0;
}

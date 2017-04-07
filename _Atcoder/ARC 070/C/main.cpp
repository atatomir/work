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

ll x, a;

int main()
{
    freopen("test.in","r",stdin);

    scanf("%lld", &x);
    a = sqrt(2 * x);

    while ( (a * (a + 1)) / 2 < x) a++;
    printf("%lld", a);


    return 0;
}

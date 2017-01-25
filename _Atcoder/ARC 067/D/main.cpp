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

#define maxN 100011

ll n, a, b, i;
ll x[maxN];
ll dist = 0;

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%lld%lld%lld", &n, &a, &b);
    for (i = 1; i <= n; i++) scanf("%lld", &x[i]);
    for (i = 2; i <= n; i++) {
        dist += min(b, a * (x[i] - x[i - 1]));
    }

    printf("%lld", dist);


    return 0;
}

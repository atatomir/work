#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

const int maxN = 200011;

int n, i;
ll x, s;
map<ll, int> M;
ll ans;

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d", &n);
    M[0]++;
    for (i = 1; i <= n; i++) {
        scanf("%lld", &x);
        s += x;
        ans += M[s];
        M[s]++;
    }

    printf("%lld", ans);


    return 0;
}

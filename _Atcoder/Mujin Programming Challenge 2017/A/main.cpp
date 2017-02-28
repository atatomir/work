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
#define mod 1000000007

int n, i;
ll x[maxN], dead, pos;
ll ans = 1;

bool check(ll pos) {
    ll maxi = (x[pos] + 2) / 2;
    return pos - dead <= maxi;
}

bool check2(ll pos) {
    ll maxi = (x[pos] + 1) / 2;
    return pos - dead <= maxi;
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) scanf("%lld", &x[i]);

    dead = 0; pos = 1;
    for (i = 1; i <= n; i++) {
        while (pos <= n && check2(pos))
            pos++;

        if (check(pos)) pos++;

        ans = (ans * (pos - dead - 1)) % mod;
        dead++;
    }

    printf("%lld", ans);


    return 0;
}

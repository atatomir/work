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

ll x, y, ans;

ll gcd(ll a, ll b) {
    if (a < b) swap(a, b);

    while (b > 0) {
        a %= b;
        swap(a, b);
    }

    return a;
}

int main()
{
    freopen("test.in","r",stdin);

    cin >> x >> y;
    if (x % y == 0) {
        cout << -1;
        return 0;
    }

    ans = (x * y) / gcd(x, y);
    ans -= x;

    cout << ans;


    return 0;
}

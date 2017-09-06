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

ll n, a, b, c, d;

bool check(ll l, ll r) {
    ll dist, act, i;

    for (i = 0; i <= n; i++) {
        act = a + 1LL * i * c;
        act -= 1LL * (n - i) * c;

        if (l <= act && act <= r) return true;
        if (act < l) {
            dist = l - act;
            if (dist <= (d - c) * i) return true;
        } else {
            dist = act - r;
            if (dist <= (d - c) * (n - i)) return true;
        }
    }


    return false;

}

int main()
{
    freopen("test.in","r",stdin);

    cin >> n >> a >> b >> c >> d; n -= 2;
    if (a > b) swap(a, b);
    if (c > d) swap(c, d);

    if (check(b - d, b - c)) {
        cout << "YES";
        return 0;
    }

    if (check(b + c, b + d)) {
        cout << "YES";
        return 0;
    }

    cout << "NO";


    return 0;
}

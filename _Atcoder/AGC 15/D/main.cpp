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

ll A, B;
ll ans, step;

ll both(ll l1, ll r1, ll l2, ll r2) {
    l2 = max(l2, r1 + 1);
    return r1 - l1 + 1 + max(0LL, r2 - l2 + 1);
}

ll ones(ll x) {
    for (ll step = 1; step <= x; step <<= 1)
        x |= step;
    return x;
}

int main()
{
    freopen("test.in","r",stdin);

    cin >> A >> B;
    if (A == B) {
        cout << 1;
        return 0;
    }

    for (step = 1LL << 60; step > 0; step >>= 1) {
        if ((A & step) != (B & step)) break;
        A &= step - 1;
        B &= step - 1;
    }

    B -= step;
    ans = step - A;

    ans += both(step, step + ones(B), step + A, step + step - 1);
    cout << ans;

    return 0;
}

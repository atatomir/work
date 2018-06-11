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

#define maxN 300011

ll n, A, B, i, j;

bool check(ll n, ll A, ll B) {
    ll l, r;

    l = A + B - 1;
    r = A * B;

    if (n < l || n > r) return false;
    return true;
}

bool check2(ll n, ll A, ll B) {
    ll l, r;

    l = B;
    r = A * B;

    if (n < l || n > r) return false;
    return true;
}

int main()
{
    //freopen("test.in","r",stdin);

    cin >> n >> A >> B;
    if (!check(n, A, B)) {
        cout << -1;
        return 0;
    }

    while (B > 0) {
        for (i = 1; !check2(n - i, A, B - 1); i++);
        for (; check2(n - i, A, B - 1) && i <= A; i++);
        i--;

        for (j = i; j > 0; j--)
            cout << n - j + 1 << ' ';

        n -= i;
        B--;
    }


    return 0;
}

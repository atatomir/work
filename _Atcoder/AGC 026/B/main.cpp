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

ll t, ti, A, B, C, D;

ll gcd(ll a, ll b) {
    if (a < b) swap(a, b);
    while (b > 0) {
        a %= b;
        swap(a, b);
    }
    return a;
}

bool check() {
    if (B > D) return false;
    if (B > A) return false;
    if (B <= C) return true;

    if (A > C) {
        ll dif = A - C;
        A = C + (dif % B);
    }

    while (A > C) {
        if (A < B) return false;
        A -= B;
    }

    A += D;
    if (A < B) return false;


    ll dif = D - B;
    if (dif == 0) return true;

    dif = gcd(dif, B);
    A %= B;

    A += max(0LL, dif * ((C - A) / dif));
    A += dif;
    if (A < B) return false;
    return true;
}

int main()
{
    freopen("test.in","r",stdin);

    cin >> t;
    for (ti = 1; ti <= t; ti++) {
        cin >> A >> B >> C >> D;
        if (check())
            cout << "Yes\n";
        else
            cout << "No\n";
    }


    return 0;
}

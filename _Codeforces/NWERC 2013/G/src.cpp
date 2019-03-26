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

//#define debug(x) ;
#define debug(x) cerr << #x << " = " << x << "\n";

ostream& operator<<(ostream& cerr, vector<ll> aux) {
    cerr << "[";
    for (auto e : aux) cerr << e << ' ';
    cerr << "]";
    return cerr;
}

ll AB, AC, BD;
ll up, down;

ll gcd(ll x, ll y) {
    if (x < y) swap(x, y);
    while (y > 0) {
        x %= y;
        swap(x, y);
    }
    return x;
}

int main()
{
    //freopen("test.in","r",stdin);

    while (true) {
        if (scanf("%lld%lld%lld", &AB, &AC, &BD) != 3)
            break;

        up = AC * AB;
        down = BD - AC;
        ll d = gcd(up, down);
        up /= d;
        down /= d;

        printf("%lld/%lld\n", up, down);
    }


    return 0;
}

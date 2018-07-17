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

ll k, i, j, act, base, nxt;

ll sum(ll x) {
    ll ans = 0;
    while (x > 0) {
        ans += x % 10;
        x /= 10;
    }
    return ans;
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%lld", &k);

    base = 1;
    act = 1;


    while (k > 0) {
        while (true) {
            nxt = act + base;
            if (act * sum(nxt) > nxt * sum(act)) {
                act -= base;
                break;
            }

            printf("%lld\n", act);
            if (--k == 0) return 0;
            act = nxt;
        }

        base *= 10LL;
        act += base;
    }


    return 0;
}

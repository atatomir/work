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

ll n, i, l, r, auxl, auxr;
ll a[maxN], d;

int main()
{
    //freopen("test.in","r",stdin);

    cin >> n;
    for (i = 1; i <= n; i++) cin >> a[i];

    l = r = 2;
    for (i = n; i > 0; i--) {
        d = a[i];

        auxl = (l + d - 1) / d;
        auxr = r / d;

        if (auxl > auxr) {
            cout << -1;
            return 0;
        }

        l = auxl * d;
        r = auxr * d + d - 1;
    }

    cout << l << ' ' << r;


    return 0;
}

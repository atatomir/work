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

ll x, n, q, i;
ll r[maxN];
ll tm, ini, a, b, c;

ll act_tm, nxt, dif;

void decrease_with(ll dif) {
    ll aux = min(c, dif);

    c -= aux;
    dif -= aux;
    if (dif == 0) return;

    if (b - a <= dif) {
        a = b = 0;
        return;
    }

    a += dif;
}

void increase_with(ll dif) {
    ll aux = min(x - (c + b - a), dif);

    c += aux;
    dif -= aux;
    if (dif == 0) return;

    if (b - a <= dif) {
        a = b = 0;
        c = x;
        return;
    }

    b -= dif;
    c += dif;
}

int main()
{
    freopen("test.in","r",stdin);

    cin >> x >> n;
    for (i = 1; i <= n; i++) cin >> r[i];
    r[n + 1] = 1000000001;

    a = 0; b = x; c = 0;
    act_tm = 0; nxt = 1;

    cin >> q;
    for (i = 1; i <= q; i++) {
        cin >> tm >> ini;

        while (act_tm != tm) {
            if (tm < r[nxt]) {
                dif = tm - act_tm;
                if (nxt % 2 == 1)
                    decrease_with(dif);
                else
                    increase_with(dif);

                act_tm = tm;
            } else {
                dif = r[nxt] - act_tm;
                if (nxt % 2 == 1)
                    decrease_with(dif);
                else
                    increase_with(dif);

                act_tm = r[nxt];
                nxt++;
            }
        }

        if (ini <= a) {
            cout << c << '\n';
            continue;
        }

        if (ini >= b) {
            cout << c + b - a << '\n';
            continue;
        }

        cout << c + ini - a << '\n';
    }


    return 0;
}

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

#define maxN 500011
#define inf 1000000011

struct piece {
    char c;
    ll x, y;
};

ll n, i;
ll x, y, X, Y;
piece v[maxN];
ll d1, d2, d3, d4, dd1, dd2, dd3, dd4;
char c;

ll up, down, le, ri, ul, ur, dl, dr;


void yes() {
    printf("YES");
    exit(0);
}

void add_rel() {
    if (x == X) {
        if (y < Y) down = max(down, y);
        if (y > Y) up = min(up, y);
    }

    if (y == Y) {
        if (x < X) le = max(le, x);
        if (x > X) ri = min(ri, x);
    }

    if (x - X == y - Y) {
        if (x < X) dl = max(dl, x);
        if (x > X) ur = min(ur, x);
    }

    if (x - X == Y - y) {
        if (x < X) ul = max(ul, x);
        if (x > X) dr = min(dr, x);
    }
}

bool check() {
    if (x == X) {
        if (y < Y) if (y < down) return false;
        if (y > Y) if (y > up) return false;
    }

    if (y == Y) {
        if (x < X) if (x < le) return false;
        if (x > X) if (x > ri) return false;
    }

    if (x - X == y - Y) {
        if (x < X) if (x < dl) return false;
        if (x > X) if (x > ur) return false;
    }

    if (x - X == Y - y) {
        if (x < X) if (x < ul) return false;
        if (x > X) if (x > dr) return false;
    }

    return true;
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%lld", &n);
    scanf("%lld%lld\n", &x, &y); X = x; Y = y;
    d1 = x;
    d2 = y;
    d3 = x + y;
    d4 = x - y;

    up = ur = ri = dl = inf;
    down = dl = le = ul = -inf;

    for (i = 1; i <= n; i++) {
        scanf("%c %lld %lld\n", &c, &x, &y);
        v[i] = {c, x, y};

        add_rel();
    }

    for (i = 1; i <= n; i++) {
        c = v[i].c;
        x = v[i].x;
        y = v[i].y;

        if (!check()) continue;

        dd1 = x;
        dd2 = y;
        dd3 = x + y;
        dd4 = x - y;

        if (c == 'B' || c == 'Q') { // d3 , d4
            if (d3 == dd3) yes();
            if (d4 == dd4) yes();
        }

        if (c == 'R' || c == 'Q') { // d1, d2
            if (d1 == dd2) yes();
            if (d2 == dd2) yes();
        }
    }

    printf("NO");


    return 0;
}

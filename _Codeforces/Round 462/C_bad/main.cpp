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

#define maxN 11
#define eps 1e-7

bool is_equal(double a, double b) {
    a -= b;
    if (a < 0) a = -a;
    return a <= eps;
}

struct circle {
    ll x, y, R;
};

int n, i, j, cnt;
circle C[maxN];

bool intr(circle A, circle B) {
    ll dist = (A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y);
    ll d1 = A.R;
    ll d2 = B.R;

    if (d1 > d2) swap(d1, d2);

    if ((d1 + d2) * (d1 + d2) <= dist) return false;
    if (dist <= (d2 - d1) * (d2 - d1)) return false;
    return true;
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d", &n);
    for (i = 1; i <= n; i++)
        scanf("%lld%lld%lld", &C[i].x, &C[i].y, &C[i].R);

    for (i = 1; i <= n; i++)
        for (j = i + 1; j <= n; j++)
            if (intr(C[i], C[j]))
                cnt++;

    if (n == 3) {
        if (cnt == 0) cout << 4;
        if (cnt == 1) cout << 5;
        if (cnt == 2) cout << 6;
        if (cnt == 3) cout << 8;
    }

    if (n == 1) {
        cout << 2;
    }

    if (n == 2) {
        if (cnt == 0) cout << 3;
        if (cnt == 1) cout << 4;
    }


    return 0;
}

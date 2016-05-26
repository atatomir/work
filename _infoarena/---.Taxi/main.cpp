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

#define x1 ax1
#define y1 ay1
#define x2 ax2
#define y2 ay2

int t, ti;
ll A, B, x1, y1, x2, y2;
ll dx, dy;

void flip() {
    y1 = B - y1 + 1;
    y2 = B - y2 + 1;
}

ll give(ll x) {
    printf("%lld\n", x);
}

int main()
{
    freopen("taxi.in","r",stdin);
    freopen("taxi.out","w",stdout);

    for (scanf("%d", &t), ti = 1; ti <= t; ti++) {
        scanf("%lld%lld%lld%lld%lld%lld", &A, &B, &x1, &y1, &x2, &y2);
        A++; B++;
        x1++; y1++;
        x2++; y2++;

        //! no point
        if ((max(x1, x2) - min(x1, x2) + max(y1, y2) - min(y1, y2)) % 2 == 1) {
            give(0);
            continue;
        }

        //! same position
        if (x1 == x2 && y1 == y2) {
            give(A * B);
            continue;
        }

        //! y1 == y2
        if (y1 == y2) {
            give(B);
            continue;
        }

        //! x1 == x2
        if (x1 == x2) {
            give(A);
            continue;
        }

        if (x1 > x2) {
            swap(x1, x2);
            swap(y1, y2);
        }

        if (y1 < y2) flip();

        dx = x2 - x1;
        dy = y1 - y2;

        if (dx == dy) {
            give(x1 * y2 + (A - x2 + 1) * (B - y1 + 1) + dx - 1);
        } else {
            if (dx > dy)
                give(B);
            else
                give(A);
        }

    }


    return 0;
}

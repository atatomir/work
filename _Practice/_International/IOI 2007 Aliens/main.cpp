#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include "1341_aliens.h"
//#include "lib1341.h"

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

int n, x, y, i, j, m;
int le, ri, up, down;
int cnt;

bool ask(int x, int y) {
    if (x <= 0 || x > n || y <= 0 || y > n) return false;

    cnt++;
    return Examine(x, y);
}

int bin_search(int x, int y, int dx, int dy) {
    int ans = 1;

    while (true) {
        bool now = ask(x + ans * dx, y + ans * dy);
        if (now == 0) break;
        ans *= 2;
    }

    int limit = ans;
    ans = 0;

    for (int step = 1 << 30; step; step >>= 1) {
        if (ans + step <= limit) {
            int aux = ans + step;

            if (ask(x + aux * dx, y + aux * dy))
                ans += step;
        }
    }

    return ans + 1;
}


int main()
{
    Init(&n, &x, &y);

    ri = bin_search(x, y, +1, 0);
    le = bin_search(x, y, -1, 0);
    m = ri + le - 1;

    up = bin_search(x, y, 0, +1);
    down = m - up + 1;


    int mid = (m + 1) / 2;
    x += mid - le;
    y += mid - down;

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if ( (i ^ j) & 1 ) continue;

            int lx = x - i * m - (m / 2);
            int ly = y - j * m - (m / 2);

            int rx = lx + 5 * m - 1;
            int ry = ly + 5 * m - 1;

            if (ask(lx, ly)) {
                if (ask(rx, ry)) {
                    //! found solution
                    Solution( (0LL + lx + rx) / 2, (0LL + ly + ry) / 2 );


                    cerr << "Good";
                    return 0;
                }
            }
        }
    }

    cerr << "False";


    return 0;
}

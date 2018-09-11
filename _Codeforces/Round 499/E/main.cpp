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

const int maxN = 100011;

int xmin, xmax, ymin, ymax, zmin, zmax;
int xx1, xx2, yy1, yy2, zz1, zz2;

void err() {
    printf("INCORRECT");
    exit(0);
}

bool in(int x, int a, int b) {
    return a <= x && x <= b;
}

struct point {
    int x, y, z;

    void read() {
        scanf("%d%d%d", &x, &y, &z);
    }

    void run() {
        xmax = max(xmax, x);
        ymax = max(ymax, y);
        zmax = max(zmax, z);

        xmin = min(xmin, x);
        ymin = min(ymin, y);
        zmin = min(zmin, z);
    }

    void check() {
        int cx, cy, cz;
        cx = in(x, xmin, xmax);
        cy = in(y, ymin, ymax);
        cz = in(z, zmin, zmax);

        if (cx == true && cy == true && cz == true) err();

        if (cx == true && cy == true) {
            if (z < zmin)
                zz1 = max(zz1, z + 1);
            else
                zz2 = min(zz2, z - 1);
        }

        if (cx == true && cz == true) {
            if (y < ymin)
                yy1 = max(yy1, y + 1);
            else
                yy2 = min(yy2, y - 1);
        }

        if (cy == true && cz == true) {
            if (x < xmin)
                xx1 = max(xx1, x + 1);
            else
                xx2 = min(xx2, x - 1);
        }
    }

    void solve() {
        int cx, cy, cz;
        cx = in(x, xmin, xmax);
        cy = in(y, ymin, ymax);
        cz = in(z, zmin, zmax);

        if (cx == true && cy == true && cz == true) {
            printf("OPEN\n");
            return;
        }

        if (x < xx1 || x > xx2 || y < yy1 || y > yy2 || z < zz1 || z > zz2) {
            printf("CLOSED\n");
            return;
        }

        printf("UNKNOWN\n");
    }
};

int xx, yy, zz, n, m, k, i;
point Acc[maxN], Den[maxN], Q[maxN];


int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d%d%d%d%d", &xx, &yy, &zz, &n, &m, &k);
    xmin = ymin = zmin = maxN;
    xx1 = yy1 = zz1 = 1;
    xx2 = xx;
    yy2 = yy;
    zz2 = zz;

    for (i = 1; i <= n; i++) Acc[i].read(), Acc[i].run();
    for (i = 1; i <= m; i++) Den[i].read(), Den[i].check();

    printf("CORRECT\n");
    for (i = 1; i <= k; i++) {
        Q[i].read();

        Q[i].solve();
    }


    return 0;
}

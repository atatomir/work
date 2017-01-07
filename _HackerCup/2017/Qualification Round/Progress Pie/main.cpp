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

#define eps 1e-7

const double PI = acos(-1.00);

int t, ti;
int P, X, Y;

int dist(int X, int Y) {
    return (X - 50) * (X - 50) + (Y - 50) * (Y - 50) ;
}

bool black() {

    if (P == 0) {
        return false;
    }
    if (dist(X, Y) > 50 * 50) return false;
    if (X == 50 && Y == 50) {
        return true;
    }

    double ang2 = atan2(1, 0);
    double ang1 = atan2(Y - 50, X - 50);

    if (ang1 > ang2) ang2 += 2.00 * PI;
    double delta = ang2 - ang1;
    double proc = ( delta / (2 * PI) ) * 100.00;

    if (proc <= 1.00 * P + eps)
        return true;
    else
        return false;
}

int main()
{
    freopen("input.in","r",stdin);
    freopen("output.out","w",stdout);

    scanf("%d", &t);
    cerr << "Start solving " << t << " tests.\n";
    for (ti = 1; ti <= t; ti++) {
        scanf("%d%d%d", &P, &X, &Y);
        cerr << "#" << ti << "\n";
        if (black())
            printf("Case #%d: black\n", ti);
        else
            printf("Case #%d: white\n", ti);
    }

    return 0;
}

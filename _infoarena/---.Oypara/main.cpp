#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
 
using namespace std;
 
#define ll long long
#define mp make_pair
 
#define maxN 100011
 
struct Line {
    int x, y1, y2;
 
    bool operator<(const Line& who)const {
        return x < who.x;
    }
};
 
int n, i;
Line L[maxN];
double fy, ly;
 
double check(double y) {
    int i;
    double down = -1e180;
    double up = 1e180;
 
    for (i = 2; i <= n; i++){
        down = max(down, (1.00 * L[i].y1 - y) / (1.00 * L[i].x - L[1].x));
        up = min(up, (1.00 * L[i].y2 - y) / (1.00 * L[i].x - L[1].x));
    }
 
    ly = (up + down) /2.00;
    return up - down;
}
 
double aprox(double x) {
    if (x - floor(x) <= 0.50)
        x = floor(x);
    else
        x = ceil(x);
 
    return x;
}
 
int main()
{
    freopen("oypara.in", "r", stdin);
    freopen("oypara.out", "w", stdout);
 
    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d%d%d", &L[i].x, &L[i].y1, &L[i].y2);
        if (L[i].y1 > L[i].y2) swap(L[i].y1, L[i].y2);
    }
 
    sort(L + 1, L + n + 1);
 
    double l = L[1].y1;
    double r = L[1].y2;
    double m1, m2;
    int step = 25;
 
    while (step--) {
        m1 = (2 * l + r) / 3.00;
        m2 = (l + 2 * r) / 3.00;
 
        if (check(m1) < check(m2))
            l = m1;
        else
            r = m2;
    }
 
    fy = (l + r) / 2.00;
    fy = aprox(fy);
 
    ly = fy + ly * (L[n].x - L[1].x);
    ly = aprox(ly);
 
 
 
    printf("%d %d %d %d", L[1].x, (int)fy, L[n].x, (int)ly);
 
    return 0;
}

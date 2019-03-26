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

//#define debug(x) ;
#define debug(x) cerr << #x << " = " << x << "\n";

ostream& operator<<(ostream& cerr, vector<ll> aux) {
    cerr << "[";
    for (auto e : aux) cerr << e << ' ';
    cerr << "]";
    return cerr;
}

const double sq2 = sqrt(2.00);

double n, p, s, v;


double check(double c) {
    double up = log(n) / log(2);
    up = n * pow(up, c * sq2);
    double down = p * 1000000000.00;
    double t1 = up / down;

    double up2 = s * (1.00 + (1.00 / c));
    double t2 = up2 / v;

    return t1 + t2;
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%lf%lf%lf%lf", &n, &p, &s, &v);

    double lo = 1e-9;
    double hi = 1;

    double aux = check(lo);
    while (check(2.00 * hi) <= aux) 
        hi *= 2.00;
    hi *= 2.00;

    int steps = 250;
    while (steps--) {
        double m1 = (2.00 * lo + hi) / 3.00;
        double m2 = (2.00 * hi + lo) / 3.00;
    
        debug(m1);
        debug(check(m1));

        debug(m2);
        debug(check(m2));

        if (check(m1) < check(m2))
            hi = m2;
        else
            lo = m1;
    }

    double ans = (lo + hi) / 2.00;
    printf("%.10f %.10f", check(ans), ans);


    return 0;
}

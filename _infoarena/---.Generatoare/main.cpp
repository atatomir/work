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

#define maxN 50011

int n, i;
int v[maxN];
double ans;

double ch_zero, ch_one;

int main()
{
    freopen("generatoare.in","r",stdin);
    freopen("generatoare.out","w",stdout);

    scanf("%d", &n);
    for (i = 1; i <= n; i++) scanf("%d", &v[i]);

    for (int bit = 0; bit <= 30; bit++) {
        int aux = 1 << bit;
        ch_zero = 1.00;
        ch_one = 0.00;

        for (i = 1; i <= n; i++) {
            int gr = v[i] >> bit;
            if (gr & 1) gr ^= 1;

            int how = (gr / 2) * aux;
            int work = v[i] - gr * aux;
            if (work > aux)
                how += work - aux;

            double now_one = (1.00 * how) / (1.00 * v[i]);
            double now_zero = 1.00 - now_one;

            ch_zero = ch_zero * now_zero + ch_one * now_one;
            ch_one = 1 - ch_zero;
        }

        ans += ch_one * aux;
    }

    printf("%.3lf", ans);

    return 0;
}

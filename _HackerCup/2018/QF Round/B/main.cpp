#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

const int maxN = 111;

int t, ti;
int n, i, P[maxN], base, up;


int main()
{
    freopen("input.in","r",stdin);
    freopen("output.out", "w", stdout);

    scanf("%d", &t);
    cerr << "Solve " << t << " tests\n";

    for (ti = 1; ti <= t; ti++) {
        cerr << "#" << ti << '\n';

        scanf("%d", &n);
        for (i = 0; i <= n; i++) scanf("%d", &P[i]);

        /*base = 0;
        for (i = 1; i <= n; i++) {
            up = base;
            base = ((i + P[i - 1]) == 0 ? 0 : 1);

            if (up == 0)
                base = 1;
        }*/

        base = n % 2;

        if (base == 0)
            printf("Case #%d: 0\n", ti);
        else
            printf("Case #%d: 1\n0.0\n", ti);

    }


    return 0;
}

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 100011

int n, i, t, test;
int A, B;
int v[maxN];
double ans;

void add_ans(int l, int r) {
    int bg = (A - l + v[n] - 1) / v[n];
    int en = (B - r) / v[n];

    double how = en - bg + 1.00;

    ans += (1.00 * how * (r - l) * (r - l)) / (2.00 * (B - A));
}

bool solve_first() {
    int i;

    int gr_a = A / v[n];
    int gr_b = B / v[n];
    int pos_a = A % v[n];
    int pos_b = B % v[n];

    if (gr_a == gr_b) {
        for (i = 1; i <= n; i++) {
            if (pos_a >= v[i - 1] && pos_b <= v[i]) {
                ans = (1.00 * (pos_b - pos_a) * (pos_b + pos_a - 2 * v[i - 1])) / (2.00 * (B - A));
                return false;
            }
        }
    }

    for (i = 0; i <= n; i++) {
        if (pos_a == v[i]) break;

        if (pos_a < v[i]) {
            ans += (1.00 * (v[i] - pos_a) * (v[i] + pos_a - 2 * v[i - 1])) / (2.00 * (B - A));
            break;
        }
    }

    for (i = 0; i <= n; i++) {
        if (pos_b == v[i]) break;

        if (pos_b < v[i]) {
            ans += (1.00 * (pos_b - v[i - 1]) * (pos_b - v[i - 1])) / (2.00 * (B - A));
            break;
        }
    }


    return true;
}

int main()
{
    freopen("input.in","r",stdin);
    freopen("output.out","w",stdout);

    for (scanf("%d", &t), test = 1; test <= t; test++) {
        cerr << "Solving " << test << '\n';

        scanf("%d %d %d", &n, &A, &B);
        for (i = 1; i <= n; i++) {
            scanf("%d", &v[i]);
            v[i] += v[i - 1];
        }

        ans = 0;

        if(solve_first())
            for (i = 1; i <= n; i++)
                add_ans(v[i - 1], v[i]);

        printf("Case #%d: %.9lf\n", test, ans);
    }


    return 0;
}

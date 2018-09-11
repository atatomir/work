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


int t, ti;
int n, k, i, j;

int sum(int a, int b) {
    return ((a + b) * (b - a + 1)) / 2;
}

void solve() {
    int i, j, cnt, sol;

    if (n <= 2 || k <= 2) {
        printf("0\n1\n1 %d 1\n", n);
        return;
    }

    cnt = min(k, n);
    sol = sum(k - cnt + 1, k - 1) - k;
    sol = max(sol, 0);

    printf("%d\n%d\n", sol, cnt);
    printf("1 %d %d\n", n, k);
    for (i = 1; i < cnt - 1; i++) printf("%d %d %d\n", i, i + 1, k - i);
    printf("%d %d %d\n", cnt - 1, n, k - cnt + 1);
}

int main()
{
    freopen("input.in","r",stdin);
    freopen("output.out", "w", stdout);

    scanf("%d", &t);
    cerr << "Solve " << t << " tests\n";

    for (ti = 1; ti <= t; ti++) {
        cerr << "#" << ti << '\n';

        scanf("%d%d", &n, &k);
        printf("Case #%d: ", ti);
        solve();
    }


    return 0;
}

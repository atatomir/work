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

const int maxN = 2018;

int t, ti;
int n, i;
char s[maxN];

int pr[maxN], u;

void solve() {
    int i, j;

    u = pr[1] = 0;
    for (i = 2; i <= n; i++) {
        while (u > 0 && s[u + 1] != s[i]) u = pr[u];
        if (s[u + 1] == s[i]) u++;
        pr[i] = u;
    }

    for (i = 1; i < n; i++) {
        if (pr[i] > 0 && pr[i] >= pr[i + 1]) {

            for (j = 1; j <= i; j++) printf("%c", s[j]);
            for (j = pr[i] + 1; j <= n; j++) printf("%c", s[j]);

            return;
        }
    }

    printf("Impossible");
}

int main()
{
    freopen("input.in","r",stdin);
    freopen("output.out", "w", stdout);

    scanf("%d\n", &t);
    cerr << "Solve " << t << " tests\n";

    for (ti = 1; ti <= t; ti++) {
        cerr << "#" << ti << '\n';

        memset(s, 0, sizeof(s));
        scanf("%s\n", s + 1);
        n = strlen(s + 1);

        printf("Case #%d: ", ti);
        solve();
        printf("\n");

    }


    return 0;
}

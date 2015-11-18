#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 2115
#define maxM 50011
#define inf 100000000

int n, i, j, m;
int t[maxM], c[maxM], b[maxM];
int aux, ans;

void test(int fr, int to) {
    int c1 = c[fr];
    int c2 = c[to];
    if (c1 > c2) swap(c1, c2);

    int dist = min(c2 - c1, n - c2 + c1);
    if (t[fr] + dist > t[to]) return;

    aux = max(aux, b[fr]);
}

int main()
{
    freopen("bcrc.in","r",stdin);
    freopen("bcrc.ok","w",stdout);

    ans = -inf;

    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; i++) {
        scanf("%d%d%d", &t[i], &c[i], &b[i]);
        cerr << i << '\n';

        aux = -inf;
        for (j = 0; j < i; j++)
            test(j, i);

        b[i] += aux;
        ans = max(ans, b[i]);
    }

    printf("%d", ans);

    return 0;
}

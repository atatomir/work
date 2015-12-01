#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

int n, m, i, j;
int hx, hy;
vector< vector<int> > work;

void expand_line() {
    int i, j;
    int bit = hx * hy;

    for (i = 0; i < hx; i++)
        for (j = 0; j < hy; j++)
            work[hx + (hx - i) - 1][j] = work[i][j] + bit;

    hx *= 2;
}

void expand_column() {
    int i, j;

    int bit = hx * hy;

    for (i = 0; i < hx; i++)
        for (j = 0; j < hy; j++)
            work[i][hy + (hy - j) - 1] = work[i][j] + bit;

    hy *= 2;
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d%d", &n, &m);
    work = vector< vector<int> >(1 << n, vector<int>(1 << m, 0));

    hx = 1; hy = 1;

    for (i = 1; i <= n; i++)
        expand_line();

    for (i = 1; i <= m; i++)
        expand_column();

    for (i = 0; i < hx; i++) {
        for (j = 0; j < hy; j++)
            printf("%d ", work[i][j]);
        printf("\n");
    }

    return 0;
}

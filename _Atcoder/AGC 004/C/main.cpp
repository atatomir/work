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

#define maxN 555

int n, m, i, j;
char s[maxN][maxN];

bool red(int x, int y) {
    if (y == 1) return true;
    if (y == m) return false;
    return (x & 1);
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%d%d\n", &n, &m);
    for (i = 1; i <= n; i++) scanf("%s\n", s[i] + 1);

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            if (red(i, j) || s[i][j] == '#')
                printf("#");
            else
                printf(".");
        }
        printf("\n");
    }

    printf("\n");

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            if (!red(i, j) || s[i][j] == '#')
                printf("#");
            else
                printf(".");
        }
        printf("\n");
    }

    return 0;
}

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

#define maxN 500011
#define sigma 26
#define maxLog 21

int n, i, q, l, r;
char s[maxN];
int nxt[sigma][maxN];
int dad[maxLog][maxN];

void pre() {
    int i, j;

    for (i = 0; i < sigma; i++) nxt[i][n + 1] = n + 2;
    for (i = 0; i < sigma; i++) nxt[i][n + 2] = n + 2;

    for (i = n; i > 0; i--) {
        nxt[s[i] - 'a'][i] = i + 1;
        for (j = s[i] - 'a' + 1; j < sigma; j++)
            nxt[j][i] = nxt[j - 1][ nxt[j - 1][i] ];

        dad[0][i] = nxt[25][ nxt[25][i] ];

        for (j = 0; j < s[i] - 'a'; j++)
            nxt[j][i] = nxt[j][ dad[0][i] ];
    }

    for (i = 0; i < maxLog; i++) dad[i][n + 1] = n + 2;
    for (i = 0; i < maxLog; i++) dad[i][n + 2] = n + 2;

    for (i = 1; i < maxLog; i++)
        for (j = 1; j <= n; j++)
            dad[i][j] = dad[i - 1][ dad[i - 1][j] ];
}

int main()
{
    freopen("test.in","r",stdin);

    scanf("%s\n%d", s + 1, &q); n = strlen(s + 1);
    pre();

    for (i = 1; i <= q; i++) {
        scanf("%d%d", &l, &r);

        for (int step = maxLog - 1; step >= 0; step--)
            if (dad[step][l] <= r + 1)
                l = dad[step][l];

        if (l == r + 1)
            printf("Yes\n");
        else
            printf("No\n");
    }



    return 0;
}

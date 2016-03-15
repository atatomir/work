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

#define maxN 155

int n, m, i, j;
int cnt;
int ans[maxN][maxN];
bool swapped;

void draw_i_hor(int x, int y) {
    cnt++;
    ans[x][y] = ans[x][y + 1] = cnt;
}

void draw_i_ver(int x, int y) {
    cnt++;
    ans[x][y] = ans[x + 1][y] = cnt;
}

//! 4 x 3
void drawA(int x, int y) {
    cnt++;
    ans[x][y] = ans[x][y + 1] = ans[x + 1][y] = ans[x + 2][y] = ans[x + 2][y + 1] = ans[x + 3][y] = cnt;

    cnt++;
    ans[x][y + 2] = ans[x + 1][y + 1] = ans[x + 1][y + 2] = ans[x + 2][y + 2] = ans[x + 3][y + 1] = ans[x + 3][y + 2] = cnt;
}


void afis() {
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++)
            printf("%d ", ans[i][j]);
        printf("\n");
    }

    printf("\n\n");
}

int main()
{
    freopen("pavare3.in","r",stdin);
    freopen("pavare3.out","w",stdout);

    scanf("%d%d", &n, &m);

    if (n < m) {
        swapped = true;
        swap(n, m);
    }


    int how = (n * m) / 24;
    for (i = 1; i + 3 <= n; i += 4)
        for (j = 1; j + 2 <= m; j += 3)
            if (how)
                drawA(i, j), how--;


    for (i = 1; i <= n; i++)
        for (j = 1; j < m; j++)
            if (ans[i][j] == 0)
                draw_i_hor(i, j);

    for (i = 1; i < n; i++)
        for (j = 1; j <= m; j++)
            if (ans[i][j] == 0)
                draw_i_ver(i, j);



    if (swapped) {
        for (i = 1; i <= m; i++) {
            for (j = 1; j <= n; j++)
                printf("%d ", ans[j][i]);
            printf("\n");
        }
    } else {
        for (i = 1; i <= n; i++) {
            for (j = 1; j <= m; j++)
                printf("%d ", ans[i][j]);
            printf("\n");
        }
    }



    return 0;
}

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

//! 8 x 3
void drawA(int x, int y) {

    cnt++;
    ans[x][y] = ans[x][y + 1] = ans[x + 1][y] = ans[x + 2][y] = ans[x + 2][y + 1] = ans[x + 3][y] = cnt;

    cnt++;
    ans[x][y + 2] = ans[x + 1][y + 1] = ans[x + 1][y + 2] = ans[x + 2][y + 2] = ans[x + 3][y + 1] = ans[x + 3][y + 2] = cnt;

    draw_i_hor(x + 4, y);
    draw_i_hor(x + 5, y);
    draw_i_hor(x + 6, y);
    draw_i_hor(x + 7, y);

    draw_i_ver(x + 4, y + 2);
    draw_i_ver(x + 6, y + 2);
}

//! 6 x 4
void drawB(int x, int y) {
    cnt++;
    ans[x][y] = ans[x][y + 1] = ans[x + 1][y] = ans[x + 2][y] = ans[x + 2][y + 1] = ans[x + 3][y] = cnt;

    cnt++;
    ans[x][y + 2] = ans[x][y + 3] = ans[x + 1][y + 3] = ans[x + 2][y + 2] = ans[x + 2][y + 3] = ans[x + 3][y + 3] = cnt;

    draw_i_hor(x + 1, y + 1);
    draw_i_hor(x + 3, y + 1);

    draw_i_hor(x + 4, y);
    draw_i_hor(x + 4, y + 2);
    draw_i_hor(x + 5, y);
    draw_i_hor(x + 5, y + 2);
}

//! 4 x 6
void drawC(int x, int y) {
    cnt++;
    ans[x][y + 2] = ans[x][y + 3] = ans[x + 1][y + 3] = ans[x][y + 4] = ans[x][y + 5] = ans[x + 1][y + 5] = cnt;

    cnt++;
    ans[x + 3][y + 2] = ans[x + 2][y + 3] = ans[x + 3][y + 3] = ans[x + 3][y + 4] = ans[x + 2][y + 5] = ans[x + 3][y + 5] = cnt;

    draw_i_ver(x, y);
    draw_i_ver(x, y + 1);
    draw_i_ver(x + 2, y);
    draw_i_ver(x + 2, y + 1);

    draw_i_ver(x + 1, y + 2);
    draw_i_ver(x + 1, y + 4);
}

//! 3 x 8
void drawD(int x, int y) {
    cnt++;
    ans[x][y] = ans[x][y + 1] = ans[x + 1][y + 1] = ans[x][y + 2] = ans[x][y + 3] = ans[x + 1][y + 3] = cnt;

    cnt++;
    ans[x + 1][y] = ans[x + 2][y] = ans[x + 2][y + 1] = ans[x + 1][y + 2] = ans[x + 2][y + 2] = ans[x + 2][y + 3] = cnt;

    draw_i_ver(x + 1, y + 4);
    draw_i_ver(x + 1, y + 5);
    draw_i_ver(x + 1, y + 6);
    draw_i_ver(x + 1, y + 7);

    draw_i_hor(x, y + 4);
    draw_i_hor(x, y + 6);
}



void solve_three() {
    int i, j;

    for (i = 1; i <= n; i += 8)
        for (j = 1; j <= m; j += 3)
            drawA(i, j);
}

void solve_six() {
    int i, j;

    for (i = 1; i <= n; i += 4)
        for (j = 1; j <= m; j += 6)
            drawC(i, j);
}

void solve_div_four() {
    solve_six();
}

void solve_div_four_plus_two() {
    for (j = 1; j <= m; j += 4)
        drawB(1, j);

    for (i = 7; i <= n; i++)
        for (j = 1; j <= m; j += 6)
            drawC(i, j);
}

void solve_last_three() {
    int i, j;

    for (j = 1; j <= m; j += 8)
        drawD(n - 3 + 1, j);
}

int main()
{
    freopen("pavare3.in","r",stdin);
    freopen("pavare3.out","w",stdout);

    scanf("%d%d", &n, &m);


    if (m % 3 != 0) {
        swapped = true;
        swap(n, m);
    }

    if (m % 24 == 0) {

        if (n % 2 == 0) {
            if (n % 4 == 0)
                solve_div_four();
            else
                solve_div_four_plus_two();
        } else {
            n -= 3;

            if (n % 4 == 0)
                solve_div_four();
            else
                solve_div_four_plus_two();

            n += 3;
            solve_last_three();
        }
    } else {
        if (m % 12 == 0) {
            if (n % 4 == 0)
                solve_div_four();
            else
                solve_div_four_plus_two();
        } else {
            if (m % 6 != 0)
                solve_three();
            else
                solve_six();
        }
    }




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

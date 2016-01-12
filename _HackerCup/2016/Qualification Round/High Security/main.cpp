#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxN 1024

int n, i, t, test;
char mat[2][maxN];
int ans;

void add_guard(int x, int y) {
    ans++;

    mat[0][y] = mat[1][y] = 'X';
    for (int i = y + 1; mat[x][i] != 'X'; i++)
        mat[x][i] = 'X';
    for (int i = y - 1; mat[x][i] != 'X'; i--)
        mat[x][i] = 'X';

    //cerr << mat[0] << '\n' << mat[1] << '\n' << '\n';
}

void add_guard_line(int x, int y) {
    ans++;

    //mat[0][y] = mat[1][y] = 'X';
    for (int i = y + 1; mat[x][i] != 'X'; i++)
        mat[x][i] = 'X';
    for (int i = y - 1; mat[x][i] != 'X'; i--)
        mat[x][i] = 'X';

    //cerr << mat[0] << '\n' << mat[1] << '\n' << '\n';
}

void solve_combo() {
    //! X.X
    //! ...
    int i;

    for (i = 1; i <= n; i++)
        if (mat[0][i - 1] == 'X' && mat[0][i + 1] == 'X')
            if (mat[0][i] == '.' && mat[1][i] == '.')
                add_guard(1, i);

    for (i = 1; i <= n; i++)
        if (mat[1][i - 1] == 'X' && mat[1][i + 1] == 'X')
            if (mat[0][i] == '.' && mat[1][i] == '.')
                add_guard(0, i);
}

void solve_other() {
    int i;

    for (i = 1; i <= n; i++)
        if (mat[0][i] == '.')
            add_guard_line(0, i);
    for (i = 1; i <= n; i++)
        if (mat[1][i] == '.')
            add_guard_line(1, i);
}

int main()
{
    freopen("input.in","r",stdin);
    freopen("output.out","w",stdout);

    scanf("%d\n", &t);
    for (test = 1; test <= t; test++) {
        cerr << "Solving " << test << '\n';

        scanf("%d\n%s\n%s\n", &n, mat[0] + 1, mat[1] + 1);
        ans = 0;

        mat[0][0] = mat[1][0] = mat[0][n + 1] = mat[1][n + 1] = 'X';

        solve_combo();
        solve_other();

        printf("Case #%d: %d\n", test, ans);
    }


    return 0;
}

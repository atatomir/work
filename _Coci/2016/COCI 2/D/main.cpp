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

#define maxN 111

int n, i, j, pos;
int mat[maxN][maxN];

void print4() {
    printf("5 11 12 16\n");
    printf("15 9 10 2\n");
    printf("1 3 14 6\n");
    printf("7 13 4 8\n");
}

void try_it() {
    int i, j, pos;
    int sum;

    pos = 0;

    for (i = 1; i < n; i++) {
        sum = 0;
        for (j = 1; j <= n; j++)
            mat[i][j] = ++pos, sum += mat[i][j];

        mat[i][n] += (n - (sum % n)) % n;
        pos = mat[i][n];
    }

    for (i = 1; i <= n; i++) {
        sum = (n - 1) * mat[n - 1][i];
        for (j = 1; j < n - 1; j++)
            sum -= mat[j][i];
        mat[n][i] = sum;
    }

    for (i = 1; i <= n; i++) {
        sum = 0;
        for (j = 1; j <= n; j++)
            sum += mat[i][j];

        if (sum % n != 0) return;

        bool found = false;
        for (j = 1; j <= n; j++)
            if (mat[i][j] == sum / n)
                found = true;

        if (!found) return;
    }

    for (i = 1; i <= n; i++) {
        sum = 0;
        for (j = 1; j <= n; j++)
            sum += mat[j][i];

        if (sum % n != 0) return;

        bool found = false;
        for (j = 1; j <= n; j++)
            if (mat[j][i] == sum / n)
                found = true;

        if (!found) return;
    }

    for (i = 1; i <= n; i++, printf("\n"))
        for (j = 1; j <= n; j++)
            printf("%d ", mat[i][j]);

    exit(0);
}

int main()
{
    //freopen("test.in","r",stdin);

    scanf("%d", &n);
    if (n % 2 == 1) {
        for (i = 1; i <= n; i++, printf("\n"))
            for (j = 1; j <= n; j++)
                printf("%d ", ++pos);
        return 0;
    }

    if (n == 4) {
        print4();
        return 0;
    }

    if (n == 2) {
        printf("-1");
        return 0;
    }

    try_it();
    printf("-1");

    return 0;
}

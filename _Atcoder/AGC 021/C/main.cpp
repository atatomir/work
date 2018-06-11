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

#define maxN 1024

int n, m, A, B, i, j, aux;
char mat[maxN][maxN];

int main()
{
    freopen("test.in","r",stdin);

    cin >> n >> m >> A >> B;

    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            mat[i][j] = '.';

    if (n % 2 == 1) {
        aux = min(m / 2, A);
        for (i = 1; i <= aux; i++) {
            mat[n][2 * i - 1] = '<';
            mat[n][2 * i] = '>';
            A--;
        }
    }

    if (m % 2 == 1) {
        aux = min(n / 2, B);
        for (i = 1; i <= aux; i++) {
            mat[2 * i - 1][m] = '^';
            mat[2 * i][m] = 'v';
            B--;
        }
    }

    for (i = 1; i + 1 <= n; i += 2) {
        for (j = 1; j + 1 <= m; j += 2) {
            if (A >= 2) {
                mat[i][j] = '<';
                mat[i][j + 1] = '>';
                mat[i + 1][j] = '<';
                mat[i + 1][j + 1] = '>';
                A -= 2;
                continue;
            }

            if (B >= 2) {
                mat[i][j] = '^';
                mat[i + 1][j] = 'v';
                mat[i][j + 1] = '^';
                mat[i + 1][j + 1] = 'v';
                B -= 2;
                continue;
            }

            if (A == 1 && B == 1) {
                if (n % 2 == 1 && m % 2 == 1) {
                    if (i + 2 == n && j + 2 == m) {
                        mat[n][m] = mat[n - 1][m];
                        mat[n - 1][m] = mat[n - 2][m];
                        mat[i][j] = '^';
                        mat[i + 1][j] = 'v';
                        mat[i][j + 1] = '<';
                        mat[i][j + 2] = '>';
                        A--; B--;
                        continue;
                    }
                }
            }

            if (A == 1) {
                mat[i][j] = '<';
                mat[i][j + 1] = '>';
                A--;
                continue;
            }

            if (B == 1) {
                mat[i][j] = '^';
                mat[i + 1][j] = 'v';
                B--;
                continue;
            }
        }
    }

    if (A > 0 || B > 0) {
        cout << "NO";
        return 0;
    }

    cout << "YES\n";
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) cout << mat[i][j];
        cout << '\n';
    }




    return 0;
}
